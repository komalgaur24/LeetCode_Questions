typedef struct {
    int price;
    int idx;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
} MinHeap;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(MinHeap* h, int price, int idx) {
    int i = h->size++;
    h->data[i].price = price;
    h->data[i].idx = idx;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent].price > h->data[i].price) {
            swap(&h->data[parent], &h->data[i]);
            i = parent;
        } else {
            break;
        }
    }
}

HeapNode pop(MinHeap* h) {
    HeapNode root = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (h->data[left].price < h->data[smallest].price) {
            smallest = left;
        }
        if (right < h->size && h->data[right].price < h->data[smallest].price) {
            smallest = right;
        }

        if (smallest != i) {
            swap(&h->data[i], &h->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

int maximumSaleItems(int** items, int itemsSize, int* itemsColSize, int budget) {
    int n = itemsSize;
    int mn = INT_MAX;
    int mx = 0;

    for (int i = 0; i < n; i++) {
        if (items[i][0] > mx) {
            mx = items[i][0];
        }
        if (items[i][1] < mn) {
            mn = items[i][1];
        }
    }

    int* cn = (int*)calloc(mx + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        cn[items[i][0]]++;
    }

    int* arr = (int*)calloc(n, sizeof(int));
    int* factors = (int*)malloc((mx + 1) * sizeof(int));
    for (int i = 0; i <= mx; i++) {
        factors[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int f = items[i][0];
        if (items[i][1] >= mn * 2) {
            continue;
        }
        if (factors[f] == -1) {
            int cnt = 1;
            int count_val = 0;
            while ((long long)f * cnt <= mx) {
                count_val += cn[f * cnt];
                cnt++;
            }
            count_val--;
            arr[i] = count_val;
            factors[f] = count_val;
        } else {
            arr[i] = factors[f];
        }
    }

    MinHeap heap;
    heap.data = (HeapNode*)malloc(n * sizeof(HeapNode));
    heap.size = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            push(&heap, items[i][1], i);
        }
    }

    long long sm = 0;
    while (heap.size > 0) {
        HeapNode node = pop(&heap);
        int pr = node.price;
        int i = node.idx;

        long long q = arr[i];
        if (budget / pr < q) {
            q = budget / pr;
        }
        budget -= (int)(q * pr);
        sm += (q * 2);
    }

    long long ans = sm + (long long)budget / mn;

    free(cn);
    free(arr);
    free(factors);
    free(heap.data);

    return (int)ans;
}