int numOfSubarrays(int* arr, int arrSize) {
    const int MOD = 1000000007;
    long long prefix_sum = 0;
    long long odd_count = 0;
    for (int i = 0; i < arrSize; i++) {
        prefix_sum += arr[i];
        odd_count += prefix_sum % 2;
    }
    odd_count += ((long long)arrSize - odd_count) * odd_count;
    return odd_count % MOD;
}