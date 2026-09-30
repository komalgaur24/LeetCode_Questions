int* maxDepthAfterSplit(char* seq, int* returnSize) {
    int n = strlen(seq);
    int* level = (int*)malloc(n * sizeof(int));
    int depth = 0;
    for (int i = 0; i < n; i++) {
        if (seq[i] == '(') {
            depth = 1 - depth;
            level[i] = depth;
        }
        else if (seq[i] == ')') {
            level[i] = depth;
            depth = 1 - depth;
        }
        else {
            level[i] = depth;
        }
    }
    *returnSize = n;
    return level;
}