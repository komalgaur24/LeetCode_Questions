int minimumDeletions(int* nums, int numsSize) {
    int minIndex = 0;
    int maxIndex = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[minIndex]) {
            minIndex = i;
        }

        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    int left = minIndex < maxIndex ? minIndex : maxIndex;
    int right = minIndex > maxIndex ? minIndex : maxIndex;

    int option1 = right + 1;
    int option2 = numsSize - left;
    int option3 = left + 1 + numsSize - right;

    int ans = option1;

    if (option2 < ans) {
        ans = option2;
    }

    if (option3 < ans) {
        ans = option3;
    }

    return ans;
}