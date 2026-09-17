
int minSumOfLengths(int* arr, int arrSize, int target) {

    int windowStart = 0;
    int minLength = INT_MAX;
    int currentSum = 0;
    int result = INT_MAX;

    int* minLengthEndingAt = (int*)malloc(arrSize * sizeof(int));
    if (!minLengthEndingAt) {
        return -1;
    }

    for (int i = 0; i < arrSize; i++) {
        minLengthEndingAt[i] = INT_MAX;
    }

    for (int windowEnd = 0; windowEnd < arrSize; windowEnd++) {
        currentSum += arr[windowEnd];

        while (currentSum > target) {
            currentSum -= arr[windowStart];
            windowStart++;
        }

        if (currentSum == target) {
            int currentWindowLength = windowEnd - windowStart + 1;

            if (windowStart > 0 && minLengthEndingAt[windowStart - 1] != INT_MAX) {
                int totalLength = currentWindowLength + minLengthEndingAt           [windowStart - 1];
                if (totalLength < result) {
                    result = totalLength;
                }
            }

            if (currentWindowLength < minLength) {
                minLength = currentWindowLength;
            }
        }

        minLengthEndingAt[windowEnd] = minLength;
    }

    free(minLengthEndingAt);

    if (result == INT_MAX) {
        return -1;
    }

    return result;
}