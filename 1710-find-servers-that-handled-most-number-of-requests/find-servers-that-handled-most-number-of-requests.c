#include <stdio.h>
#include <stdlib.h>

// Structure to represent a busy server in the Min-Heap
typedef struct {
    long long free_time;
    int id;
} Server;

// Min-Heap operations for busy servers
void heap_push(Server* heap, int* heap_size, long long free_time, int id) {
    int i = (*heap_size)++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].free_time <= free_time) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i].free_time = free_time;
    heap[i].id = id;
}

Server heap_pop(Server* heap, int* heap_size) {
    Server top = heap[0];
    Server last = heap[--(*heap_size)];
    int i = 0;
    while (i * 2 + 1 < *heap_size) {
        int left = i * 2 + 1;
        int right = left + 1;
        int child = left;
        if (right < *heap_size && heap[right].free_time < heap[left].free_time) {
            child = right;
        }
        if (last.free_time <= heap[child].free_time) break;
        heap[i] = heap[child];
        i = child;
    }
    if (*heap_size > 0) heap[i] = last;
    return top;
}

// Segment Tree operations to manage free servers
// tree[node] = 1 if there is at least one free server in its range, else 0
void update_tree(int* tree, int node, int start, int end, int idx, int val) {
    if (start == end) {
        tree[node] = val;
        return;
    }
    int mid = start + (end - start) / 2;
    if (idx <= mid) update_tree(tree, node * 2, start, mid, idx, val);
    else update_tree(tree, node * 2 + 1, mid + 1, end, idx, val);
    tree[node] = tree[node * 2] | tree[node * 2 + 1];
}

// Find the first free server in range [L, R]
int query_tree(int* tree, int node, int start, int end, int L, int R) {
    if (start > R || end < L || tree[node] == 0) return -1;
    if (start == end) return start;
    
    int mid = start + (end - start) / 2;
    int left_res = query_tree(tree, node * 2, start, mid, L, R);
    if (left_res != -1) return left_res;
    return query_tree(tree, node * 2 + 1, mid + 1, end, L, R);
}

// Main logic function
int* busiestServers(int k, int* arrival, int arrivalSize, int* load, int loadSize, int* returnSize) {
    int* count = (int*)calloc(k, sizeof(int));
    
    // Allocate Segment Tree (size 4 * k is a safe boundary)
    int* tree = (int*)calloc(4 * k, sizeof(int));
    for (int i = 0; i < k; i++) {
        update_tree(tree, 1, 0, k - 1, i, 1);
    }
    
    // Allocate Min-Heap for busy servers
    Server* busy_heap = (Server*)malloc(k * sizeof(Server));
    int heap_size = 0;
    
    for (int i = 0; i < arrivalSize; i++) {
        long long current_time = arrival[i];
        
        // 1. Release servers that finished their tasks by current_time
        while (heap_size > 0 && busy_heap[0].free_time <= current_time) {
            Server freed = heap_pop(busy_heap, &heap_size);
            update_tree(tree, 1, 0, k - 1, freed.id, 1);
        }
        
        // 2. Find the target server starting from i % k
        int target = i % k;
        int chosen_server = query_tree(tree, 1, 0, k - 1, target, k - 1);
        
        // If not found in [target, k-1], wrap around and check [0, target-1]
        if (chosen_server == -1 && target > 0) {
            chosen_server = query_tree(tree, 1, 0, k - 1, 0, target - 1);
        }
        
        // 3. Assign the request if a free server was found
        if (chosen_server != -1) {
            count[chosen_server]++;
            long long free_at = current_time + load[i];
            heap_push(busy_heap, &heap_size, free_at, chosen_server);
            update_tree(tree, 1, 0, k - 1, chosen_server, 0); // Mark as busy
        }
    }
    
    // Find the maximum number of requests handled by any server
    int max_requests = 0;
    for (int i = 0; i < k; i++) {
        if (count[i] > max_requests) max_requests = count[i];
    }
    
    // Collect all servers that hit the maximum count
    int max_count = 0;
    for (int i = 0; i < k; i++) {
        if (count[i] == max_requests) max_count++;
    }
    
    int* result = (int*)malloc(max_count * sizeof(int));
    int res_idx = 0;
    for (int i = 0; i < k; i++) {
        if (count[i] == max_requests) {
            result[res_idx++] = i;
        }
    }
    
    // Clean up dynamic memory
    free(count);
    free(tree);
    free(busy_heap);
    
    *returnSize = max_count;
    return result;
}
