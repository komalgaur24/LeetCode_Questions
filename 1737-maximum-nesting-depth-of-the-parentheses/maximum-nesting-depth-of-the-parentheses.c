int maxDepth(char* s) {
    int maxDepth = 0;
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            count++;
            if (count > maxDepth) {
                maxDepth = count;
            }
        } else if (s[i] == ')') {
            count--;
        }
    }
    return maxDepth;
}