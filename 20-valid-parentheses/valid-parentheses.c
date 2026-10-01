#include <stdbool.h>
#include <string.h>
#define MAX 10000
bool isValid(char *s) {
    char stack[MAX];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            stack[++top] = s[i];
        }
        else {
            if (top == -1)
                return false;
            char tc = stack[top--];
            if ((s[i] == ')' && tc != '(') ||
                (s[i] == '}' && tc != '{') ||
                (s[i] == ']' && tc != '[')) {
                return false;
            }
        }
    }
    return top == -1;
}