#include <stdlib.h>
#include <string.h>

int minCost(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    const int V = 1024;

    // Allocate 2D array for dp: size n x V
    char** dp = (char**)malloc(n * sizeof(char*));
    for (int j = 0; j < n; j++) {
        dp[j] = (char*)calloc(V, sizeof(char));
    }

    // Allocate temporary array for 'next'
    char* next = (char*)malloc(V * sizeof(char));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int g = grid[i][j];
            memset(next, 0, V * sizeof(char));

            if (i == 0 && j == 0) {
                next[g] = 1;
            } else {
                for (int x = 0; x < V; x++) {
                    if (dp[j][x] || (j > 0 && dp[j - 1][x])) {
                        next[x ^ g] = 1;
                    }
                }
            }
            // Emulate dp[j] = move(next) by copying content
            memcpy(dp[j], next, V * sizeof(char));
        }
    }

    int result = -1;
    for (int x = 0; x < V; x++) {
        if (dp[n - 1][x]) {
            result = x;
            break;
        }
    }

    // Free dynamically allocated memory
    free(next);
    for (int j = 0; j < n; j++) {
        free(dp[j]);
    }
    free(dp);

    return result;
}
