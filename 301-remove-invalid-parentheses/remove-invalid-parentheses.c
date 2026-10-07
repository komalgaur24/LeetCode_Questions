#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fixOpening(const char *s, char ***res, int *returnSize, int scanFrom, int removeFrom);

// Pass 1: left -> right, get rid of extra ')'
void fixClosing(const char *s, char ***res, int *returnSize, int scanFrom, int removeFrom) {
    int balance = 0;
    int len = strlen(s);

    for (int i = scanFrom; i < len; i++) {
        if (s[i] == '(') balance++;
        if (s[i] == ')') balance--;

        if (balance >= 0) continue; // party is fine so far

        // too many ')' in s[0..i], so try removing each one
        for (int j = removeFrom; j <= i; j++) {
            if (s[j] == ')' && (j == removeFrom || s[j - 1] != ')')) {
                // Construct string s without char at index j
                char *nextStr = (char *)malloc(len);
                strncpy(nextStr, s, j);
                strcpy(nextStr + j, s + j + 1);

                fixClosing(nextStr, res, returnSize, i, j);
                free(nextStr);
            }
        }
        return; // this branch is handled by the recursion above
    }

    // no extra ')' left, now hunt for extra '('
    fixOpening(s, res, returnSize, len - 1, len - 1);
}

// Pass 2: right -> left, same story but mirrored
void fixOpening(const char *s, char ***res, int *returnSize, int scanFrom, int removeFrom) {
    int balance = 0;
    int len = strlen(s);
    for (int i = scanFrom; i >= 0; i--) {
        if (s[i] == ')') balance++;
        if (s[i] == '(') balance--;
        if (balance >= 0) continue;
        for (int j = removeFrom; j >= i; j--) {
            if (s[j] == '(' && (j == removeFrom || s[j + 1] != '(')) {
                // Construct string s without char at index j
                char *nextStr = (char *)malloc(len);
                strncpy(nextStr, s, j);
                strcpy(nextStr + j, s + j + 1);

                fixOpening(nextStr, res, returnSize, i - 1, j - 1);
                free(nextStr);
            }
        }
        return;
    }
    *res = (char **)realloc(*res, sizeof(char *) * (*returnSize + 1));
    (*res)[*returnSize] = strdup(s);
    (*returnSize)++;
}
char **removeInvalidParentheses(char *s, int *returnSize) {
    *returnSize = 0;
    char **res = NULL;
    fixClosing(s, &res, returnSize, 0, 0);
    return res;
}