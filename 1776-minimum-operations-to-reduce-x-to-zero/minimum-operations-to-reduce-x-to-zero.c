int minOperations(int* nums, int numsSize, int x) {
    int minOperation = INT_MAX;
    int curSum = 0;
    int left = -1;
    int right = numsSize;
    while(left < numsSize - 1 && curSum < x) {
        curSum += nums[++left];
    }
    if(curSum == x) {
        minOperation = minOperation < (left + 1) ? minOperation : (left + 1);
    }
    while(left >= 0) {
        curSum -= nums[left--];
        while(right > left + 1 && curSum < x) {
            curSum += nums[--right];
        }
        if(curSum == x) {
            int operations = (left + 1)+(numsSize - right);
            minOperation =  minOperation < operations ? minOperation : operations;
        }
    }
    return minOperation == INT_MAX ? -1 : minOperation;
}