typedef long long ll;

static int cmpInt(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static int lowerBound(int* a, int n, int v) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < v) l = mid + 1;
        else r = mid;
    }
    return l;
}

static void add(ll* cnt, ll* sum, int n,
                int p, int delta, int value) {
    for (; p <= n; p += p & -p) {
        cnt[p] += delta;
        sum[p] += (ll)delta * value;
    }
}

static void prefix(ll* cnt, ll* sum, int p,
                   ll* c, ll* s) {
    *c = *s = 0;
    for (; p > 0; p -= p & -p) {
        *c += cnt[p];
        *s += sum[p];
    }
}

static int kth(ll* cnt, int n, int rank) {
    int p = 0, step = 1;
    while (step <= n / 2) step <<= 1;

    for (; step; step >>= 1) {
        int np = p + step;
        if (np <= n && cnt[np] < rank) {
            rank -= (int)cnt[np];
            p = np;
        }
    }
    return p + 1;
}

long long minOperations(int* nums, int numsSize, int x, int k) {
    int n = numsSize;
    if ((ll)x * k > n) return -1;

    int* vals = malloc(n * sizeof(int));
    memcpy(vals, nums, n * sizeof(int));
    qsort(vals, n, sizeof(int), cmpInt);

    int m = 0;
    for (int i = 0; i < n; i++) {
        if (m == 0 || vals[i] != vals[m - 1])
            vals[m++] = vals[i];
    }

    ll* cnt = calloc(m + 1, sizeof(ll));
    ll* sum = calloc(m + 1, sizeof(ll));
    ll* ops = calloc(n, sizeof(ll));

    ll total = 0;

    for (int i = 0; i < n; i++) {
        int p = lowerBound(vals, m, nums[i]) + 1;
        add(cnt, sum, m, p, 1, nums[i]);
        total += nums[i];

        if (i >= x) {
            int old = lowerBound(vals, m, nums[i - x]) + 1;
            add(cnt, sum, m, old, -1, nums[i - x]);
            total -= nums[i - x];
        }

        if (i >= x - 1) {
            int midPos = kth(cnt, m, (x + 1) / 2);
            ll mid = vals[midPos - 1];

            ll lc, ls;
            prefix(cnt, sum, midPos, &lc, &ls);

            ll rc = x - lc;
            ll rs = total - ls;

            ops[i] = mid * lc - ls + rs - mid * rc;
        }
    }

    const ll INF = LLONG_MAX / 4;
    ll* pre = calloc(n + 1, sizeof(ll));
    ll* cur = malloc((n + 1) * sizeof(ll));

    for (int j = 1; j <= k; j++) {
        for (int i = 0; i <= n; i++) cur[i] = INF;

        for (int i = j * x; i <= n; i++) {
            ll take = pre[i - x] + ops[i - 1];
            cur[i] = cur[i - 1] < take ? cur[i - 1] : take;
        }

        ll* tmp = pre;
        pre = cur;
        cur = tmp;
    }

    ll ans = pre[n];

    free(vals);
    free(cnt);
    free(sum);
    free(ops);
    free(pre);
    free(cur);

    return ans;
}