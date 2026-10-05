int scoreOfParentheses(char* s) {
    int stack[50];
    int top = -1;

    stack[++top] = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            stack[++top] = 0;
        } else {
            int x = stack[top--];

            if (x == 0)
                x = 1;
            else
                x = 2 * x;

            stack[top] += x;
        }
    }

    return stack[0];
}