/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **res;
int resIdx;
int strSize;
void help(int l, int r, char* str, int strIdx) {
    if(!(l||r)) {
        res[resIdx] = (char*)calloc(strSize, sizeof(char));
        strcpy(res[resIdx++], str);
        return;
    }
    if(l) {
        str[strIdx] = '(';
        help(l-1, r, str, strIdx+1);
    }
    if(r-l) {
        str[strIdx] = ')';
        help(l, r-1, str, strIdx+1);
    }
}
char** generateParenthesis(int n, int* returnSize) {
    resIdx = 0;
    strSize = n*2+1;
    res = (char**)calloc(1<<(n*2), sizeof(char*));
    char* str = (char*)calloc(strSize, sizeof(char));
    help(n, n, str, 0);
    *returnSize = resIdx;
    return res;
}