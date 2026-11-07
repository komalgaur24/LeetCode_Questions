#include <stdio.h>
#include <stdlib.h>

// Structure for busy servers heap: stores (free_time, server_index)
typedef struct {
    long long free_time;
    int index;
} BusyServer;

// Min-Heap for Free Servers (stores server indices)
typedef struct {
    int *data;
    int size;
    int capacity;
    const int *servers_weight;
} FreeHeap;

// Min-Heap for Busy Servers
typedef struct {
    BusyServer *data;
    int size;
    int capacity;
    const int *servers_weight;
} BusyHeap;

// --- Free Heap Functions ---
FreeHeap* create_free_heap(int capacity, const int *weights) {
    FreeHeap *h = (FreeHeap*)malloc(sizeof(FreeHeap));
    h->data = (int*)malloc(sizeof(int) * capacity);
    h->size = 0;
    h->capacity = capacity;
    h->servers_weight = weights;
    return h;
}

int compare_free(int a, int b, const int *w) {
    if (w[a] != w[b]) return w[a] < w[b];
    return a < b;
}

void free_heap_push(FreeHeap *h, int val) {
    int i = h->size++;
    h->data[i] = val;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare_free(h->data[i], h->data[parent], h->servers_weight)) {
            int temp = h->data[i];
            h->data[i] = h->data[parent];
            h->data[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

int free_heap_pop(FreeHeap *h) {
    int root = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (compare_free(h->data[left], h->data[smallest], h->servers_weight)) smallest = left;
        if (right < h->size && compare_free(h->data[right], h->data[smallest], h->servers_weight)) smallest = right;
        if (smallest != i) {
            int temp = h->data[i];
            h->data[i] = h->data[smallest];
            h->data[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

// --- Busy Heap Functions ---
BusyHeap* create_busy_heap(int capacity, const int *weights) {
    BusyHeap *h = (BusyHeap*)malloc(sizeof(BusyHeap));
    h->data = (BusyServer*)malloc(sizeof(BusyServer) * capacity);
    h->size = 0;
    h->capacity = capacity;
    h->servers_weight = weights;
    return h;
}

int compare_busy(BusyServer a, BusyServer b, const int *w) {
    if (a.free_time != b.free_time) return a.free_time < b.free_time;
    if (w[a.index] != w[b.index]) return w[a.index] < w[b.index];
    return a.index < b.index;
}

void busy_heap_push(BusyHeap *h, long long free_time, int index) {
    int i = h->size++;
    h->data[i] = (BusyServer){free_time, index};
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare_busy(h->data[i], h->data[parent], h->servers_weight)) {
            BusyServer temp = h->data[i];
            h->data[i] = h->data[parent];
            h->data[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

BusyServer busy_heap_pop(BusyHeap *h) {
    BusyServer root = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
        if (compare_busy(h->data[left], h->data[smallest], h->servers_weight)) smallest = left;
        if (right < h->size && compare_busy(h->data[right], h->data[smallest], h->servers_weight)) smallest = right;
        if (smallest != i) {
            BusyServer temp = h->data[i];
            h->data[i] = h->data[smallest];
            h->data[smallest] = temp;
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

// --- Main Solution Function ---
int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    *returnSize = tasksSize;
    int *ans = (int*)malloc(sizeof(int) * tasksSize);

    FreeHeap *free_heap = create_free_heap(serversSize, servers);
    BusyHeap *busy_heap = create_busy_heap(serversSize, servers);

    for (int i = 0; i < serversSize; i++) {
        free_heap_push(free_heap, i);
    }

    long long current_time = 0;

    for (int j = 0; j < tasksSize; j++) {
        if (free_heap->size == 0) {
            if (current_time < busy_heap->data[0].free_time) {
                current_time = busy_heap->data[0].free_time;
            }
        }

        // Release all servers that become free by current_time
        while (busy_heap->size > 0 && busy_heap->data[0].free_time <= current_time) {
            BusyServer b = busy_heap_pop(busy_heap);
            free_heap_push(free_heap, b.index);
        }

        // If current_time is less than task arrival time j, jump to j
        if (current_time < j && free_heap->size > 0) {
            current_time = j;
            while (busy_heap->size > 0 && busy_heap->data[0].free_time <= current_time) {
                BusyServer b = busy_heap_pop(busy_heap);
                free_heap_push(free_heap, b.index);
            }
        }

        // Assign task j to the best available server
        int server_idx = free_heap_pop(free_heap);
        ans[j] = server_idx;
        busy_heap_push(busy_heap, current_time + tasks[j], server_idx);
    }

    // Clean up memory
    free(free_heap->data);
    free(free_heap);
    free(busy_heap->data);
    free(busy_heap);

    return ans;
}