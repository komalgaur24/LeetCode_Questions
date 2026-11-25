void* malloc(unsigned long);
void free(void*);

typedef struct {
    long long h1;
    long long h2;
    int count;
    int state;
} Entry;

static int next_pow2(int x) {
    int p = 1;
    while (p < x) {
        p <<= 1;
    }
    return p;
}

static int check_hash(const long long* pref1, const long long* pref2,
                      const long long* pow1, const long long* pow2,
                      int n, int m) {
    long long mod1 = 1000000007LL;
    long long mod2 = 1000000009LL;
    int total = n - m + 1;
    int cap = next_pow2(total * 2);
    if (cap < 16) {
        cap = 16;
    }
    int mask = cap - 1;

    Entry* table = (Entry*)malloc((unsigned long)cap * sizeof(Entry));
    for (int i = 0; i < cap; i++) {
        table[i].state = 0;
    }

    long long p1 = pow1[m];
    long long p2 = pow2[m];

    for (int l = 0; l <= n - m; l++) {
        int r = l + m;
        long long h1 = (pref1[r] - (pref1[l] * p1) % mod1) % mod1;
        if (h1 < 0) {
            h1 += mod1;
        }
        long long h2 = (pref2[r] - (pref2[l] * p2) % mod2) % mod2;
        if (h2 < 0) {
            h2 += mod2;
        }

        unsigned long long mix = ((unsigned long long)h1 * 11400714819323198485ULL) ^
                                 ((unsigned long long)h2 * 14029467366897019727ULL);
        int slot = (int)(mix >> (64 - 31)) & mask;

        while (1) {
            if (table[slot].state == 0) {
                table[slot].state = 1;
                table[slot].h1 = h1;
                table[slot].h2 = h2;
                table[slot].count = 1;
                break;
            }
            if (table[slot].h1 == h1 && table[slot].h2 == h2) {
                table[slot].count++;
                break;
            }
            slot = (slot + 1) & mask;
        }
    }

    int found = 0;
    for (int i = 0; i < cap; i++) {
        if (table[i].state == 1 && table[i].count == 1) {
            found = 1;
            break;
        }
    }

    free(table);
    return found;
}

int smallestUniqueSubarray(int* nums, int numsSize) {
    long long mod1 = 1000000007LL;
    long long mod2 = 1000000009LL;
    long long base1 = 1000003LL;
    long long base2 = 1000033LL;

    long long* pref1 = (long long*)malloc((unsigned long)(numsSize + 1) * sizeof(long long));
    long long* pref2 = (long long*)malloc((unsigned long)(numsSize + 1) * sizeof(long long));
    long long* pow1 = (long long*)malloc((unsigned long)(numsSize + 1) * sizeof(long long));
    long long* pow2 = (long long*)malloc((unsigned long)(numsSize + 1) * sizeof(long long));

    pref1[0] = 0LL;
    pref2[0] = 0LL;
    pow1[0] = 1LL;
    pow2[0] = 1LL;

    for (int i = 0; i < numsSize; i++) {
        long long val = (long long)(nums[i] + 1);
        pref1[i + 1] = (pref1[i] * base1 + val) % mod1;
        pref2[i + 1] = (pref2[i] * base2 + val) % mod2;
        pow1[i + 1] = (pow1[i] * base1) % mod1;
        pow2[i + 1] = (pow2[i] * base2) % mod2;
    }

    int low = 1, high = numsSize, ans = numsSize;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check_hash(pref1, pref2, pow1, pow2, numsSize, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    free(pref1);
    free(pref2);
    free(pow1);
    free(pow2);
    return ans;
}