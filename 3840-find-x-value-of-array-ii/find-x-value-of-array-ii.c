/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultArray(int* nums, int numsSize, int k, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int n = numsSize;

    int size = 1;
    while (size < n) size <<= 1;

    long long* H = calloc(2 * size * k, sizeof(long long));
    int* prod = malloc(2 * size * sizeof(int));

    for (int i = 0; i < 2 * size; i++) {
        prod[i] = 1 % k;
    }

    for (int i = 0; i < n; i++) {
        int v = nums[i] % k;
        int nd = size + i;

        H[nd * k + v] = 1;
        prod[nd] = v;
    }

    for (int i = size - 1; i >= 1; i--) {
        int lc = 2 * i;
        int rc = lc + 1;
        int lp = prod[lc];

        int bi = i * k;
        int bl = lc * k;
        int br = rc * k;

        for (int q = 0; q < k; q++) {
            H[bi + q] = H[bl + q];
        }

        for (int q = 0; q < k; q++) {
            long long c = H[br + q];

            if (c) {
                H[bi + (lp * q) % k] += c;
            }
        }

        prod[i] = lp * prod[rc] % k;
    }

    int* ans = malloc(queriesSize * sizeof(int));
    long long* res = malloc(k * sizeof(long long));

    int* ln = malloc(2 * size * sizeof(int));
    int* rn = malloc(2 * size * sizeof(int));

    for (int qi = 0; qi < queriesSize; qi++) {
        int idx = queries[qi][0];
        int val = queries[qi][1];
        int start = queries[qi][2];
        int x = queries[qi][3];

        int nd = size + idx;
        int base = nd * k;

        memset(H + base, 0, k * sizeof(long long));

        int v = val % k;
        H[base + v] = 1;
        prod[nd] = v;

        int cur = nd >> 1;

        while (cur) {
            int lc = 2 * cur;
            int rc = lc + 1;
            int lp = prod[lc];

            int bi = cur * k;
            int bl = lc * k;
            int br = rc * k;

            for (int q = 0; q < k; q++) {
                H[bi + q] = H[bl + q];
            }

            for (int q = 0; q < k; q++) {
                long long c = H[br + q];

                if (c) {
                    H[bi + (lp * q) % k] += c;
                }
            }

            prod[cur] = lp * prod[rc] % k;
            cur >>= 1;
        }

        int l = start + size;
        int r = n + size;

        int lnSize = 0;
        int rnSize = 0;

        while (l < r) {
            if (l & 1) {
                ln[lnSize++] = l++;
            }

            if (r & 1) {
                rn[rnSize++] = --r;
            }

            l >>= 1;
            r >>= 1;
        }

        memset(res, 0, k * sizeof(long long));
        int p = 1 % k;
        for (int i = 0; i < lnSize; i++) {
            int node = ln[i];
            int baseNode = node * k;
            for (int q = 0; q < k; q++) {
                long long c = H[baseNode + q];
                if (c) {
                    res[(p * q) % k] += c;
                }
            }
            p = p * prod[node] % k;
        }
        for (int i = rnSize - 1; i >= 0; i--) {
            int node = rn[i];
            int baseNode = node * k;
            for (int q = 0; q < k; q++) {
                long long c = H[baseNode + q];
                if (c) {
                    res[(p * q) % k] += c;
                }
            }
            p = p * prod[node] % k;
        }
        ans[qi] = (int)res[x];
    }
    free(H);
    free(prod);
    free(res);
    free(ln);
    free(rn);
    *returnSize = queriesSize;
    return ans;
}