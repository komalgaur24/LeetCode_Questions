#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumCounts(int* nums, int numsSize) {
    const long long MOD = 1000000007LL;
    int n = numsSize;

    long long* cnt = (long long*)calloc(n + 1, sizeof(long long));
    long long* tot = (long long*)calloc(n + 1, sizeof(long long));

    // Find max value to size the last-occurrence lookup array
    int max_val = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }

    int* last = (int*)malloc((max_val + 1) * sizeof(int));
    for (int i = 0; i <= max_val; i++) {
        last[i] = -1;
    }

    long long ans = 0;

    for (int r = 0; r < n; r++) {
        int val = nums[r];
        int p = last[val];

        long long c = 0, s = 0;

        // Fenwick prefix query
        for (int i = n - p - 1; i > 0; i -= i & -i) {
            c += cnt[i];
            s += tot[i];
        }

        long long gain = 1LL * (r - p) * (r - p)
                         - 2LL * (s - 1LL * p * c);

        ans = (ans + (n - r) * gain) % MOD;

        // Insert previous occurrence p
        for (int i = n - p; i <= n; i += i & -i) {
            cnt[i]++;
            tot[i] += p;
        }

        last[val] = r;
    }

    free(cnt);
    free(tot);
    free(last);

    return (int)((ans % MOD + MOD) % MOD);
}