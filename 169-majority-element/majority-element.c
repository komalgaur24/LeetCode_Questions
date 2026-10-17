int majorityElement(int* nums, int numsSize){
    int sol = nums[0],
    cnt = 0;
    for (int i = 0; i < numsSize; i++) {
        if (cnt == 0) {
            sol = nums[i];
        }
        if (nums[i] == sol) {
            cnt++;
        } else {
            cnt--;
        } 
    }        
    return sol;
}