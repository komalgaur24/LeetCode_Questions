#define MOD 1000000007

long long** createMatrix(int size) {
    long long** matrix = malloc(size * sizeof(long long*));

    for (int i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(long long));
    }
    return matrix;
}

void freeMatrix(long long** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

long long** multiplyMatrices(long long** matrixA, long long** matrixB, int size) {
    long long** result = createMatrix(size);
    for (int row = 0; row < size; row++) {
        for (int mid = 0; mid < size; mid++) {
            if (matrixA[row][mid] == 0) 
                continue;

            for (int col = 0; col < size; col++) {
                result[row][col] = (
                    result[row][col] + matrixA[row][mid] * matrixB[mid][col]
                ) % MOD;
            }
        }
    }

    return result;
}

long long** matrixPower(long long** matrix, int power, int size) {
    long long** result = createMatrix(size);

    for (int row = 0; row < size; row++) {
        result[row][row] = 1;
    }

    while (power > 0) {
        if (power & 1) {
            long long** temp = multiplyMatrices(result, matrix, size);
            freeMatrix(result, size);
            result = temp;
        }

        long long** temp = multiplyMatrices(matrix, matrix, size);
        freeMatrix(matrix, size);
        matrix = temp;
        power >>= 1;
    }

    freeMatrix(matrix, size);
    return result;
}

int zigZagArrays(int n, int l, int r) {
    int valueCount = r - l + 1;
    long long* initialDp = malloc(valueCount * sizeof(long long));
    for (int i = 0; i < valueCount; i++) {
        initialDp[i] = i;
    }
    long long** transitionMatrix = createMatrix(valueCount);
    for (int row = 1; row < valueCount; row++) {
        for (int col = valueCount - row; col < valueCount; col++) {
            transitionMatrix[row][col] = 1;
        }
    }
    long long** poweredTransition = matrixPower(transitionMatrix, n - 2, valueCount);
    long long answer = 0;
    for (int row = 0; row < valueCount; row++) {
        for (int col = 0; col < valueCount; col++) {
            answer = (answer + poweredTransition[row][col] * initialDp[col]) % MOD;
        }
    }
    free(initialDp);
    freeMatrix(poweredTransition, valueCount);
    return answer * 2 % MOD;
}