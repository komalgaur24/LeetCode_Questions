/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* targetIndices(int* nums, int numsSize, int target, int* returnSize) {
    int less = 0, equal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < target) less++;
        else if (nums[i] == target) equal++;
    }
    int* ans = (int*)malloc(sizeof(int) * numsSize);  // answer has at most numsSize items
    for (int i = 0; i < equal; i++) ans[i] = less + i;
    *returnSize = equal;
    return ans;
}