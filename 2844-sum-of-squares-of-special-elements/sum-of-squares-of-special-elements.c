int sumOfSquares(int* nums, int n) {
    int sum = 0;
    for (int i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            sum += nums[i - 1] * nums[i - 1];
            int j = n / i;
            if (i != j) {
                sum += nums[j - 1] * nums[j - 1];
            }
        }
    }

    return sum;
}