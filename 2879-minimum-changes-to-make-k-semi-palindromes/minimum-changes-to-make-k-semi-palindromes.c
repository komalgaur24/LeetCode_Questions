#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INF 1000000000

int n;
int **cost;
int **memo;

int min(int a, int b) {
    return a < b ? a : b;
}

int getCost(char *s, int l, int r) {
    int len = r - l + 1;
    int best = INF;

    for (int d = 1; d < len; d++) {
        if (len % d != 0) continue;

        int changes = 0;

        for (int offset = 0; offset < d; offset++) {
            int left = l + offset;
            int right = r - d + 1 + offset;

            while (left < right) {
                if (s[left] != s[right])
                    changes++;

                left += d;
                right -= d;
            }
        }

        best = min(best, changes);
    }

    return best;
}

int dfs(int start, int k) {
    if (k == 0)
        return start == n ? 0 : INF;

    if (n - start < 2 * k)
        return INF;

    if (memo[start][k] != -1)
        return memo[start][k];

    int ans = INF;

    for (int end = start + 2; end <= n - 2 * (k - 1); end++) {
        ans = min(ans, cost[start][end - 1] + dfs(end, k - 1));
    }

    return memo[start][k] = ans;
}

int minimumChanges(char *s, int k) {
    n = strlen(s);

    cost = malloc(n * sizeof(int *));
    memo = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        cost[i] = calloc(n, sizeof(int));
        memo[i] = malloc((k + 1) * sizeof(int));

        for (int j = 0; j <= k; j++)
            memo[i][j] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cost[i][j] = getCost(s, i, j);
        }
    }

    int ans = dfs(0, k);

    for (int i = 0; i < n; i++) {
        free(cost[i]);
        free(memo[i]);
    }

    free(cost);
    free(memo);

    return ans;
}