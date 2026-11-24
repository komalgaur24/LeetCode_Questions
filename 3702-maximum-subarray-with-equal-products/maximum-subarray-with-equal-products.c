int maxLength(int* nums, int numsSize) {
    const unsigned char bits[11] = {
        0,
        0,
        1 << 0,
        1 << 1,
        1 << 0,
        1 << 2,
        (1 << 0) | (1 << 1),
        1 << 3,
        1 << 0,
        1 << 1,
        (1 << 0) | (1 << 2),
    };
    unsigned char flag = 0;
    
    int length = 0; 
    for (int i = 0; i < numsSize; i++) {
        if ((flag & bits[nums[i]]) != 0) {
            break;
        }
        flag |= bits[nums[i]];
        length++;
    }
    
    int maxLength = length;
    for (int sIndex = 0, eIndex = length; eIndex < numsSize; sIndex++) {
        flag &= ~bits[nums[sIndex]];
        length--;
        while ((eIndex < numsSize) && (flag & bits[nums[eIndex]]) == 0) {
            flag |= bits[nums[eIndex++]];
            length++;
        }
        
        if (length > maxLength) {
            maxLength = length;
        }
    }
    
    return maxLength < 2 ? 2 : maxLength;
}