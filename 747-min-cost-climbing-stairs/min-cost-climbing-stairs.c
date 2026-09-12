int solve(int* cost, int n, int i, int* dp) {
    if (i >= n)
        return 0;
    if (dp[i] != -1)
        return dp[i];

    int one = solve(cost, n, i + 1, dp);
    int two = solve(cost, n, i + 2, dp);
    return dp[i] = cost[i] + (one < two ? one : two);
}

int minCostClimbingStairs(int* cost, int costSize) {
    int dp[costSize];

    for (int i = 0; i < costSize; i++)
        dp[i] = -1;

    int start0 = solve(cost, costSize, 0, dp);
    int start1 = solve(cost, costSize, 1, dp);

    return start0 < start1 ? start0 : start1;
}