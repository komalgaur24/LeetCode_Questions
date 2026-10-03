int longestValidParentheses(char* s) {
    int n = strlen(s);
    int* dp = (int*)calloc(n, sizeof(int));
    int maxLen = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') {
            int prevIndex = i - 1;
            if (i > 0 && dp[i - 1] > 0) {
                prevIndex -= dp[i - 1];
            }
            if (prevIndex >= 0 && s[prevIndex] == '(') {
                dp[i] = i - prevIndex + 1;
            }
            if (prevIndex > 0 && dp[i] > 0 && dp[prevIndex - 1] > 0) {
                dp[i] += dp[prevIndex - 1];
            }
            if (dp[i] > maxLen) {
                maxLen = dp[i];
            }
        }
    }
    free(dp);
    return maxLen;
}