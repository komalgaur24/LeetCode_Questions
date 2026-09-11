int totalNumbers(int* digits, int digitsSize) {
    int freq[10] = {0};
    int uniqEven[10] = {0};
    int count = 0;

    for (int i = 0; i < digitsSize; i++) {
        int d = digits[i];

        if (d % 2 == 0) {
            uniqEven[d] = 1;
        }

        freq[d]++;
    }

    for (int e = 0; e <= 9; e++) {
        if (!uniqEven[e]) {
            continue;
        }

        freq[e]--;

        int keys[10];
        int keyCount = 0;

        for (int d = 0; d <= 9; d++) {
            if (freq[d] > 0) {
                keys[keyCount++] = d;
            }
        }

        for (int i = 0; i < keyCount; i++) {
            for (int j = i + 1; j < keyCount; j++) {
                int a = keys[i];
                int b = keys[j];

                if (a != 0) {
                    count++;
                }

                if (b != 0) {
                    count++;
                }
            }
        }

        for (int i = 0; i < keyCount; i++) {
            int num = keys[i];

            if (freq[num] >= 2 && num != 0) {
                count++;
            }
        }

        freq[e]++;
    }

    return count;
}