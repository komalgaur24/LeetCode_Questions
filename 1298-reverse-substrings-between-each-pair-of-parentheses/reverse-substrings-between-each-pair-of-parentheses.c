void reverseSegment(char* str, int start, int end) {
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* reverseParentheses(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int* stack = (int*)malloc(len * sizeof(int));
    int stackTop = -1;
    int resultPos = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            stack[++stackTop] = resultPos;
        } else if (s[i] == ')') {
            int start = stack[stackTop--];
            reverseSegment(result, start, resultPos - 1);
        } else {
            result[resultPos++] = s[i];
        }
    }
    result[resultPos] = '\0';
    free(stack);
    return result;
}