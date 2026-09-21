long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    int n = numsSize;
    *returnSize = k;
    long long* ans = calloc(k, sizeof(long long));
    if (k == 1) {
        ans[0] = (long long)n * (n + 1) / 2;
        return ans;
    }
    long long* freq = calloc(k, sizeof(long long));
    long long* freq2 = calloc(k, sizeof(long long));
    for (int i = 0; i < n; i++) {
        int r = nums[i] % k;
        memset(freq2, 0, k * sizeof(long long));
        ans[r]++;
        for (int j = 0; j < k; j++) {
            int prod = (j * r) % k;
            freq2[prod] += freq[j];
            ans[prod] += freq[j];
        }
        freq2[r]++;
        long long* temp = freq;
        freq = freq2;
        freq2 = temp;
    }
    free(freq);
    free(freq2);
    return ans;
}