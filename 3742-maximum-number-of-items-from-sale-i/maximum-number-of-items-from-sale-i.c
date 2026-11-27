int maximumSaleItems(int** items, int itemsSize, int* itemsColSize, int budget) {
    (void)itemsColSize;
    int n = itemsSize;
    int* bonus = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && items[j][0] % items[i][0] == 0) {
                cnt++;
            }
        }
        bonus[i] = cnt;
    }

    int* dp = (int*)calloc(budget + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        int cost = items[i][1];
        int free_copies = bonus[i];
        if (cost <= budget) {
            for (int b = budget; b >= cost; b--) {
                int cand = dp[b - cost] + 1 + free_copies;
                if (cand > dp[b]) {
                    dp[b] = cand;
                }
            }
            for (int b = cost; b <= budget; b++) {
                int cand = dp[b - cost] + 1;
                if (cand > dp[b]) {
                    dp[b] = cand;
                }
            }
        }
    }

    int ans = 0;
    for (int b = 0; b <= budget; b++) {
        if (dp[b] > ans) {
            ans = dp[b];
        }
    }

    free(bonus);
    free(dp);
    return ans;
}