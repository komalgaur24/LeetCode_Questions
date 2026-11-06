typedef struct {
    int time;
    int index;
} Query;

static int compareLogs(const void* a, const void* b) {
    const int* x = *(const int* const*)a;
    const int* y = *(const int* const*)b;
    return (x[1] > y[1]) - (x[1] < y[1]);
}

static int compareQueries(const void* a, const void* b) {
    const Query* x = (const Query*)a;
    const Query* y = (const Query*)b;
    return (x->time > y->time) - (x->time < y->time);
}

/**
 * Note: The returned array must be malloced.
 * Caller assumes ownership of the returned array.
 */
int* countServers(int n, int** logs, int logsSize, int* logsColSize,
                  int x, int* queries, int queriesSize, int* returnSize) {
    (void)logsColSize;

    *returnSize = queriesSize;

    qsort(logs, logsSize, sizeof(int*), compareLogs);

    Query* ordered = malloc(queriesSize * sizeof(Query));
    for (int i = 0; i < queriesSize; i++) {
        ordered[i].time = queries[i];
        ordered[i].index = i;
    }
    qsort(ordered, queriesSize, sizeof(Query), compareQueries);

    int* frequency = calloc(n + 1, sizeof(int));
    int* answer = malloc(queriesSize * sizeof(int));

    int active = 0, left = 0, right = 0;

    for (int i = 0; i < queriesSize; i++) {
        int q = ordered[i].time;
        int original_index = ordered[i].index;
        int lower = q - x;

        while (right < logsSize && logs[right][1] <= q) {
            int server = logs[right][0];
            if (frequency[server] == 0) {
                active++;
            }
            frequency[server]++;
            right++;
        }

        while (left < right && logs[left][1] < lower) {
            int server = logs[left][0];
            frequency[server]--;
            if (frequency[server] == 0) {
                active--;
            }
            left++;
        }

        answer[original_index] = n - active;
    }

    free(ordered);
    free(frequency);

    return answer;
}