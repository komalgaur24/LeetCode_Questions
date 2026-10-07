void reverse(int* nums, int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void nextPermutation(int* nums, int numsSize) {
    int idx = -1;

    for (int i = numsSize - 2; i >= 0; i--) {
        if (nums[i] < nums[i + 1]) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        reverse(nums, 0, numsSize - 1);
        return;
    }

    reverse(nums, idx + 1, numsSize - 1);

    int newj = -1;
    for (int j = idx + 1; j < numsSize; j++) {
        if (nums[idx] < nums[j]) {
            newj = j;
            break;
        }
    }

    int temp = nums[idx];
    nums[idx] = nums[newj];
    nums[newj] = temp;
}