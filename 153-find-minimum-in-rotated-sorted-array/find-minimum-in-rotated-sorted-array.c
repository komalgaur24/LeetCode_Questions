int findMin(int* num, int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (num[mid] < num[right]) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return num[left];
}