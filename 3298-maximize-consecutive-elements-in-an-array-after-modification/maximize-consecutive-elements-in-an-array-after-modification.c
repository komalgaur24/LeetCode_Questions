int compare(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}
int maxSelectedElements(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    int d0 = 1, d1 = 1, ans = 1;
    for (int i = 1; i < numsSize; i++) {
        int diff = nums[i] - nums[i - 1];
        switch (diff) {
            case 0:
                d1 = d0 + 1;
                break;
            case 1:
                d0++;
                d1++;
                break;
            case 2:
                d0 = d1 + 1;
                d1 = 1;
                break;
            default:
                d0 = d1 = 1;
        }
        if (d0 > ans) ans = d0;
        if (d1 > ans) ans = d1;
    }
    return ans;
}