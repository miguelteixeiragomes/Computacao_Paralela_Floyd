#include "matrix_floyd.h"
#define INF 1000000000
#define N 6


int min(int a, int b)
{
	/*if (a == 0)
		return b;
	if (b == 0)
		return a;*/
	if (b < a)
		return b;
	return a;
}


void floyd_algorithm(int* A, int* B, int* C, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				//printf("i,j,k=(%d,%d,%d) -> C=%d, %d+%d=%d => %d\n", i, j, k, C[n*i + j], A[n*i + k], B[n*k + j], A[n*i + k] + B[n*k + j], min(C[n*i + j], A[n*i + k] + B[n*k + j]));
				C[n*i + j] = min(C[n*i + j], A[n*i + k] + B[n*k + j]);
}


void min_matrix_floyd(int* A, int* B, int* C, int n)
{
	for (int i = 0; i < (n*n); i++)
		//for (int j = 0; j < n; j++)
			C[i] = min(A[i], B[i]);
}


void set_zero(int* a, int n)
{
	for (int i = 0; i < (n*n); i++)
		a[i] = 0;
}


void set_inf(int* a, int n)
{
	for (int i = 0; i < (n*n); i++)
		a[i] = INF;
}


void print_matrix(int* a, int n)
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			if (a[i*n + j] == INF)
				printf("%d ", 0);
			else
				printf("%d ", a[i*n + j]);
		}
		printf("\n");
	}
	printf("\n");
}


int main(void)
{
	int m[N*N] = {0, 2, 0, 5, 0, 0,
				  0, 0, 0, 0, 0, 0,
				  0, 2, 0, 0, 0, 5,
				  0, 0, 0, 0, 1, 0,
				  3, 9, 3, 0, 0, 0,
				  0, 0, 0, 0, 1, 0};

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if ((i != j) && (m[N*i + j] == 0))
				m[N*i + j] = INF;

	int *m00 = malloc(N*N/4*sizeof(int));
	int *m01 = malloc(N*N/4*sizeof(int));
	int *m10 = malloc(N*N/4*sizeof(int));
	int *m11 = malloc(N*N/4*sizeof(int));
	int *ax1 = malloc(N*N/4*sizeof(int));
	int *ax2 = malloc(N*N/4*sizeof(int));
	int *ax3 = malloc(N*N/4*sizeof(int));
	int *ax4 = malloc(N*N/4*sizeof(int));
	int *ax5 = malloc(N*N/4*sizeof(int));
	int *ax6 = malloc(N*N/4*sizeof(int));
	int *ax7 = malloc(N*N/4*sizeof(int));
	int *ax8 = malloc(N*N/4*sizeof(int));


	for (int i = 0; i < N/2; i++){
		for (int j = 0; j < N/2; j++){
			m00[i*N/2 + j] = m[i*N + j];
			m01[i*N/2 + j] = m[i*N + j + N/2];
			m10[i*N/2 + j] = m[(i + N/2)*N + j];
			m11[i*N/2 + j] = m[(i + N/2)*N + j + N/2];
		}
	}

	for (int step = 0; step < 10; step++) {
		set_inf(ax1, N / 2);
		set_inf(ax2, N / 2);
		set_inf(ax3, N / 2);
		set_inf(ax4, N / 2);
		set_inf(ax5, N / 2);
		set_inf(ax6, N / 2);
		set_inf(ax7, N / 2);
		set_inf(ax8, N / 2);

		floyd_algorithm(m00, m00, ax1, N / 2);
		floyd_algorithm(m01, m10, ax2, N / 2);
		//min_matrix_floyd(ax1, ax2, m00, N / 2);

		floyd_algorithm(m00, m01, ax3, N / 2);
		floyd_algorithm(m01, m11, ax4, N / 2);
		//min_matrix_floyd(ax1, ax2, m00, N / 2);

		floyd_algorithm(m10, m00, ax5, N / 2);
		floyd_algorithm(m11, m10, ax6, N / 2);
		//min_matrix_floyd(ax1, ax2, m10, N / 2);

		floyd_algorithm(m10, m01, ax7, N / 2);
		floyd_algorithm(m11, m11, ax8, N / 2);
		//min_matrix_floyd(ax1, ax2, m11, N / 2);


		min_matrix_floyd(ax1, ax2, m00, N / 2);
		min_matrix_floyd(ax3, ax4, m00, N / 2);
		min_matrix_floyd(ax5, ax6, m10, N / 2);
		min_matrix_floyd(ax7, ax8, m11, N / 2);


		floyd_algorithm(m, m, m, N);
	}

	print_matrix(m, N);


	for (int i = 0; i < N/2; i++){
		for (int j = 0; j < N/2; j++){
			m[i*N + j]               = m00[i*N/2 + j];
			m[i*N + j + N/2]         = m01[i*N/2 + j];
			m[(i + N/2)*N + j]       = m10[i*N/2 + j];
			m[(i + N/2)*N + j + N/2] = m11[i*N/2 + j];
		}
	}

	print_matrix(m, N);

	free(m00);
	free(m01);
	free(m10);
	free(m11);
	return 0;
}
