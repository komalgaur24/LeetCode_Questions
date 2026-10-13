#include <stdlib.h>

static int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;

    return (x > y) - (x < y);
}
long long maxAlternatingSum(int* nums, int numsSize) {
    for (int i = 0; i < numsSize; i++) {
        nums[i] *= nums[i];
    }
    qsort(nums, numsSize, sizeof(int), cmp);
    long long result = 0;
    int mid = numsSize / 2;
    for (int i = 0; i < mid; i++) {
        result -= nums[i];
    }
    for (int i = mid; i < numsSize; i++) {
        result += nums[i];
    }
    return result;
}