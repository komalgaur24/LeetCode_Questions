int reverseDegree(char* s) {
    int sum = 0;
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        sum += (i + 1) * ('z' - s[i] + 1);
    }
    return sum;
}