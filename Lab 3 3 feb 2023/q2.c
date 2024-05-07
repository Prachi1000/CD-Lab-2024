#include <stdio.h>

void min_max(int m, int n, int mat[][n]) {
    int i, j, k, r = 0, c = 0, min, count = 0;

    while (count != m) {
        min = mat[0][0];
        for (i = 1; i < m; i++) {
            if (mat[i][0] < min) {
                min = mat[i][0];
                r = i;
            }
        }

        for (i = 0; i < n; i++) {
            if (mat[r][i] > mat[r][c]) {
                c = i;
            }
        }

        printf("Task %d assigned to Machine %d\n", r + 1, c + 1);
        mat[r][c] = -1;  // Mark as assigned

        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                if (mat[i][j] != -1) {
                    mat[i][j] -= min;  // Update completion times
                }
            }
        }

        count++;
    }
}

// Example usage:
int main() {
    int m = 3, n = 3;  // 3 tasks, 3 machines
    int mat[][3] = {{4, 5, 2}, {1, 6, 3}, {7, 2, 4}};
    min_max(m, n, mat);
    return 0;
}