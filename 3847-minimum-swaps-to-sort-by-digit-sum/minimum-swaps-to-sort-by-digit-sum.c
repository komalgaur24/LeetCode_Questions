int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
typedef struct {
    int value;
    int sum;
    int originalIndex;
} Item;
void merge(Item arr[], Item temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i].sum < arr[j].sum ||
            (arr[i].sum == arr[j].sum &&
             arr[i].value < arr[j].value)) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}
void mergeSort(Item arr[], Item temp[], int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}
int minSwaps(int* nums, int numsSize) {
    Item arr[numsSize], temp[numsSize];
    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].sum = digitSum(nums[i]);
        arr[i].originalIndex = i;
    }
    mergeSort(arr, temp, 0, numsSize - 1);
    int visited[numsSize];
    for (int i = 0; i < numsSize; i++) {
        visited[i] = 0;
    }
    int swaps = 0;
    for (int i = 0; i < numsSize; i++) {
        if (visited[i] || arr[i].originalIndex == i) {
            continue;
        }
        int cycleSize = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = 1;
            j = arr[j].originalIndex;
            cycleSize++;
        }
        if (cycleSize > 1) {
            swaps += cycleSize - 1;
        }
    }
    return swaps;
}