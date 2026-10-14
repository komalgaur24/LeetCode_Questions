#include <stdlib.h>

char* maxSumOfSquares(int num, int sum) {
    if (sum > (long long)num * 9) {
        char* empty = (char*)malloc(sizeof(char));
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }
    char* res = (char*)malloc((size_t)(num + 1) * sizeof(char));
    if (res == NULL) {
        return NULL;
    }
    int nines = sum / 9;
    int rem = sum % 9;
    int idx = 0;
    while (idx < nines) {
        res[idx++] = '9';
    }
    if (rem > 0) {
        res[idx++] = (char)('0' + rem);
    }
    while (idx < num) {
        res[idx++] = '0';
    }
    res[idx] = '\0';
    return res;
}