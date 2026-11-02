#include <stdio.h>
#include <stdlib.h>

// Comparison function needed for qsort
int compare(const void *a, const void *b) {
    int num1 = *(const int *)a;
    int num2 = *(const int *)b;
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

int minMoves2(int* nums, int numsSize) {
    // Sort the array using the standard library's qsort
    qsort(nums, numsSize, sizeof(int), compare);
    
    // Find the median
    int mid = nums[numsSize / 2];
    int moves = 0;
    
    // Calculate the total absolute differences
    for (int i = 0; i < numsSize; i++) {
        moves += abs(mid - nums[i]);
    }
    
    return moves;
}
