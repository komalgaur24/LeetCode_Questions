#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 50005
#define LOG 17

// Adjacency list variables
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt++;
}

int tin[MAXN], tout[MAXN], dep[MAXN];
int up[LOG][MAXN];
int bit[MAXN + 2];
int timer;
int n_nodes;

// DFS to compute Euler tour timings, depths, and binary lifting ancestors
void dfs(int u, int p) {
    timer++;
    tin[u] = timer;
    up[0][u] = p;

    for (int j = 1; j < LOG; j++) {
        up[j][u] = up[j - 1][up[j - 1][u]];
    }

    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
    }
    tout[u] = timer;
}

// Fenwick Tree operations
void bit_add(int i, int x) {
    while (i <= n_nodes) {
        bit[i] ^= x;
        i += i & -i;
    }
}

// Range update on subtree [tin[u], tout[u]]
void update_range(int u, int x) {
    bit_add(tin[u], x);
    bit_add(tout[u] + 1, x);
}

int summ(int i) {
    int x = 0;
    while (i > 0) {
        x ^= bit[i];
        i -= i & -i;
    }
    return x;
}

// LCA using binary lifting
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int temp = u; u = v; v = temp;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (dep[u] - (1 << j) >= dep[v]) {
            u = up[j][u];
        }
    }

    if (u == v) return u;

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }
    return up[0][u];
}

/**
 * Corrected signature matching LeetCode's driver call order.
 */
bool* palindromePath(int n, int** edges, int edgesSize, int* edgesColSize, char* s, char** queries, int queriesSize, int* returnSize) {
    n_nodes = n;
    timer = 0;
    edge_cnt = 0;

    for (int i = 0; i < n; i++) {
        head[i] = -1;
    }
    for (int i = 0; i <= n + 1; i++) {
        bit[i] = 0;
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        add_edge(u, v);
        add_edge(v, u);
    }

    dep[0] = 0;
    dfs(0, 0);

    // Initialize Fenwick tree with character masks
    for (int i = 0; i < n; i++) {
        update_range(i, 1 << (s[i] - 'a'));
    }

    bool* ans = (bool*)malloc(queriesSize * sizeof(bool));
    *returnSize = 0;

    for (int q_idx = 0; q_idx < queriesSize; q_idx++) {
        char* q = queries[q_idx];
        if (q[0] == 'u') { // "update u c"
            int u;
            char c;
            sscanf(q, "update %d %c", &u, &c);
            int old_mask = 1 << (s[u] - 'a');
            int new_mask = 1 << (c - 'a');
            update_range(u, old_mask ^ new_mask);
            s[u] = c;
        } else { // "query u v"
            int u, v;
            sscanf(q, "query %d %d", &u, &v);
            int w = lca(u, v);
            int m = summ(tin[u]) ^ summ(tin[v]) ^ (1 << (s[w] - 'a'));
            ans[(*returnSize)++] = (m & (m - 1)) == 0;
        }
    }

    return ans;
}