int maxDistance(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int i = 0;
    int res = 0;

    for (int j = 0; j < nums2Size; j++) {
        while (i < nums1Size && nums1[i] > nums2[j]) {
            i++;
        }
        if (i == nums1Size) 
            break;

        int dist = j - i;
        if (dist > res) res = dist;
    }

    return res;
}