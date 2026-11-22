long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int balance = 0;
    int shift = numsSize;
    int smallerBalances = 0;
    long long ans = 0;
    int* freq = calloc(numsSize * 2 + 1, sizeof(int));
    freq[shift] = 1;

    for (int i = 0; i < numsSize; i++) {
        if(nums[i] == target) {
            smallerBalances += freq[balance + shift];
            balance++;
        } else {
            balance--;
            smallerBalances -= freq[balance + shift];
        }
        ans += smallerBalances;
        freq[balance + shift]++;
    }
    free(freq);
    return ans;
}