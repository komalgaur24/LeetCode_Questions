#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int bs(int* nums, int numsSize, int target, bool firstIndex) {
    int ans = -1;
    int lo = 0, hi = numsSize - 1;
    
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        
        if (nums[mid] > target) {
            hi = mid - 1;
        } else if (nums[mid] < target) {
            lo = mid + 1;
        } else {
            ans = mid;
            if (firstIndex)
                hi = mid - 1;
            else
                lo = mid + 1;
        }
    }
    return ans;
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* ans = (int*)malloc(2 * sizeof(int));
    
    ans[0] = bs(nums, numsSize, target, true);
    ans[1] = bs(nums, numsSize, target, false);
    
    return ans;
}