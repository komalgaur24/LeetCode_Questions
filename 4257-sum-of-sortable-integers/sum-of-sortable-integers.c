int sortableIntegers(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    int N = numsSize;

    int* divisors = malloc(N * sizeof(int));
    int divisorCount = 0;

    for (int i = 1; i <= N / i; i++) {
        if (N % i == 0) {
            divisors[divisorCount++] = i;

            if (N / i != i) {
                divisors[divisorCount++] = N / i;
            }
        }
    }

    int answer = 0;

    for (int k = 0; k < divisorCount; k++) {
        int d = divisors[k];

        int r = 0;
        int l = 0;
        int valid = 1;

        int prev_max = INT_MIN;

        while (r < N) {
            int start = r;
            r += d;

            int drops = 0;
            int curr_max = INT_MIN;
            int curr_min = INT_MAX;

            while (l < r) {
                if (l + 1 < r && nums[l] > nums[l + 1]) {
                    if (drops < 1 && nums[start] >= nums[r - 1]) {
                        drops++;
                    } else {
                        valid = 0;
                        break;
                    }
                }

                if (nums[l] < curr_min) {
                    curr_min = nums[l];
                }

                if (nums[l] > curr_max) {
                    curr_max = nums[l];
                }

                l++;
            }

            if (!valid) {
                break;
            }

            if (curr_min < prev_max) {
                valid = 0;
                break;
            }

            prev_max = curr_max;
        }

        if (valid) {
            answer += d;
        }
    }

    free(divisors);

    return answer;
}