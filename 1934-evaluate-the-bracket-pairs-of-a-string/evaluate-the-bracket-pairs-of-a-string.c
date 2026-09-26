#include <stdlib.h>
#include <string.h>

#define SIZE 200003

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

unsigned long hash(char *s) {
    unsigned long h = 0;
    while (*s)
        h = (h * 31 + *s++) % SIZE;
    return h;
}

void insert(Node **table, char *key, char *value) {
    int h = hash(key);
    Node *node = malloc(sizeof(Node));

    node->key = key;
    node->value = value;
    node->next = table[h];
    table[h] = node;
}

char *find(Node **table, char *key) {
    int h = hash(key);
    Node *p = table[h];

    while (p) {
        if (strcmp(p->key, key) == 0)
            return p->value;
        p = p->next;
    }

    return NULL;
}

char* evaluate(char* s, char*** knowledge, int knowledgeSize,
               int* knowledgeColSize) {

    Node **table = calloc(SIZE, sizeof(Node*));

    for (int i = 0; i < knowledgeSize; i++)
        insert(table, knowledge[i][0], knowledge[i][1]);

    int n = strlen(s);
    char *ans = malloc(n * 11 + 1);
    int j = 0;

    for (int i = 0; i < n; i++) {

        if (s[i] != '(') {
            ans[j++] = s[i];
        } 
        else {
            int start = ++i;

            while (s[i] != ')')
                i++;

            int len = i - start;
            char key[11];

            strncpy(key, s + start, len);
            key[len] = '\0';

            char *value = find(table, key);

            if (value) {
                strcpy(ans + j, value);
                j += strlen(value);
            } 
            else {
                ans[j++] = '?';
            }
        }
    }

    ans[j] = '\0';
    return ans;
}