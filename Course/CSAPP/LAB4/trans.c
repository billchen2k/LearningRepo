/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */
#include "cachelab.h"
#include <stdio.h>

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
	// int i, j, k;
	// int i, j, tmp;
	// for (i = 0; i < N; i++) {
	// 	for (j = 0; j < M; j++) {
	// 		tmp = A[i][j];
	// 		B[j][i] = tmp;
	// 	}
	// }
	if (N == 32 && M == 32) {
		int i, j, k;
		int t1, t2, t3, t4, t5, t6, t7, t8;
		for (i = 0; i < 32; i += 8) {
			for (j = 0; j < 32; j += 8) {
				for (k = 0; k < 8; k++) {
					t1 = A[i + k][j];
					t2 = A[i + k][j + 1];
					t3 = A[i + k][j + 2];
					t4 = A[i + k][j + 3];
					t5 = A[i + k][j + 4];
					t6 = A[i + k][j + 5];
					t7 = A[i + k][j + 6];
					t8 = A[i + k][j + 7];
					B[j][i + k] = t1;
					B[j + 1][i + k] = t2;
					B[j + 2][i + k] = t3;
					B[j + 3][i + k] = t4;
					B[j + 4][i + k] = t5;
					B[j + 5][i + k] = t6;
					B[j + 6][i + k] = t7;
					B[j + 7][i + k] = t8;
				}
			}
		}
	}
	else if (N == 64 && M == 64) {
		int t0, t1, t2, t3, t4, t5, t6, t7;
		for (int i = 0; i < N; i += 8) {
			for (int j = 0; j < M; j += 8) {
				for (int k = i; k < i + 4; k++) {
					t0 = A[k][j];
					t1 = A[k][j + 1];
					t2 = A[k][j + 2];
					t3 = A[k][j + 3];
					t4 = A[k][j + 4];
					t5 = A[k][j + 5];
					t6 = A[k][j + 6];
					t7 = A[k][j + 7];
					B[j][k] = t0;
					B[j + 1][k] = t1;
					B[j + 2][k] = t2;
					B[j + 3][k] = t3;
					B[j + 0][k + 4] = t7;
					B[j + 1][k + 4] = t6;
					B[j + 2][k + 4] = t5;
					B[j + 3][k + 4] = t4;
				}
				for (int h = 0; h < 4; h++) {
					t0 = A[i + 4][j + 3 - h];
					t1 = A[i + 5][j + 3 - h];
					t2 = A[i + 6][j + 3 - h];
					t3 = A[i + 7][j + 3 - h];
					t4 = A[i + 4][j + 4 + h];
					t5 = A[i + 5][j + 4 + h];
					t6 = A[i + 6][j + 4 + h];
					t7 = A[i + 7][j + 4 + h];
					B[j + 4 + h][i + 0] = B[j + 3 - h][i + 4];
					B[j + 4 + h][i + 1] = B[j + 3 - h][i + 5];
					B[j + 4 + h][i + 2] = B[j + 3 - h][i + 6];
					B[j + 4 + h][i + 3] = B[j + 3 - h][i + 7];
					B[j + 3 - h][i + 4] = t0;
					B[j + 3 - h][i + 5] = t1;
					B[j + 3 - h][i + 6] = t2;
					B[j + 3 - h][i + 7] = t3;
					B[j + 4 + h][i + 4] = t4;
					B[j + 4 + h][i + 5] = t5;
					B[j + 4 + h][i + 6] = t6;
					B[j + 4 + h][i + 7] = t7;
				}
			}
        }
			// int i, j, k;
			// int t1, t2, t3, t4;
			// for (i = 0; i < 64; i += 8) {
			// 	for (j = 0; j < 64; j += 8) {
			// 		for (k = 0; k < 4; k++) {
			// 			B[j + 0][i + k] = A[i + k][j + 0];
			// 			B[j + 1][i + k] = A[i + k][j + 1];
			// 			B[j + 2][i + k] = A[i + k][j + 2];
			// 			B[j + 3][i + k] = A[i + k][j + 3];
			// 			B[j + 3][i + k + 4] = A[i + k][j + 4];
			// 			B[j + 2][i + k + 4] = A[i + k][j + 5];
			// 			B[j + 1][i + k + 4] = A[i + k][j + 6];
			// 			B[j + 0][i + k + 4] = A[i + k][j + 7];
			// 		}
			// 		for (k = 0; k < 4; k++) {
			// 			B[j + 4 + 3][i + k] = A[i + k + 4][j + 0];
			// 			B[j + 4 + 2][i + k] = A[i + k + 4][j + 1];
			// 			B[j + 4 + 1][i + k] = A[i + k + 4][j + 2];
			// 			B[j + 4 + 0][i + k] = A[i + k + 4][j + 3];
			// 			B[j + 4 + 0][i + k + 4] = A[i + k + 4][j + 4];
			// 			B[j + 4 + 1][i + k + 4] = A[i + k + 4][j + 5];
			// 			B[j + 4 + 2][i + k + 4] = A[i + k + 4][j + 6];
			// 			B[j + 4 + 3][i + k + 4] = A[i + k + 4][j + 7];
			// 		}
			// 		for (k = 0; k < 4; k++) {
			// 			t1 = B[j + k][i + 4 + 0];
			// 			t2 = B[j + k][i + 4 + 1];
			// 			t3 = B[j + k][i + 4 + 2];
			// 			t4 = B[j + k][i + 4 + 3];
			// 			B[j + k][i + 4 + 0] = B[j + 4 - k][i + 0];
			// 			B[j + k][i + 4 + 1] = B[j + 4 - k][i + 1];
			// 			B[j + k][i + 4 + 2] = B[j + 4 - k][i + 2];
			// 			B[j + k][i + 4 + 3] = B[j + 4 - k][i + 3];
			// 			B[j + 4 - k][i + 0] = t1;
			// 			B[j + 4 - k][i + 1] = t2;
			// 			B[j + 4 - k][i + 2] = t3;
			// 			B[j + 4 - k][i + 3] = t4;
			// 		}
			// 	}
			// }
	}
    else{
		int i, j, k, h;
		for (i = 0; i < N; i += 16) {
			for (j = 0; j < M; j += 16) {
				for (k = i; k < i + 16 && k < N; k++) {
					for (h = j; h < j + 16 && h < M; h++) {
						B[h][k] = A[k][h];
					}
				}
			}
		}
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N]) {
	int i, j, tmp;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			tmp = A[i][j];
			B[j][i] = tmp;
		}
	}
}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
	/* Register your solution function */
	registerTransFunction(transpose_submit, transpose_submit_desc);
	/* Register any additional transpose functions */
	//registerTransFunction(trans, trans_desc);
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N]) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < M; ++j) {
			if (A[i][j] != B[j][i]) {
				return 0;
			}
		}
	}
	return 1;
}
