#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

//#define MAT_SIZE 4
//#define NUM_THREADS 3

/* FUNCTION DECLARATION */
double **malloc_matrix(int n);
void print_matrix (int n, double **a);
void free_matrix (int n, double **a);


int main(int argc, char const *argv[]) {
	int tid, nthreads, nthrds, i, j, k;
	int MAT_SIZE, NUM_THREADS;
	double myC;
	double start_time, total_time;
	double **A, **B, **C;		// Matrix A and B to be multiply; result matrix C

	/* Get matrix size and threads number from command line */
	MAT_SIZE = atoi(argv[1]);
	NUM_THREADS = atoi(argv[2]);

	A = malloc_matrix(MAT_SIZE);
	B = malloc_matrix(MAT_SIZE);
	C = malloc_matrix(MAT_SIZE);

	/* INITIALIZE MATRICES */
	// initialize matrix A and B with numbers in the interval [0.0, 1.0]
	srand((unsigned int)time(0));
	for (i = 0; i < MAT_SIZE; ++i) {
		for (j = 0; j < MAT_SIZE; ++j) {
			A[i][j] = (double)(rand()%11) / 10.0;
			B[i][j] = (double)(rand()%11) / 10.0;
			C[i][j] = 0.0;
		}
	}

	/* PRINT MATRICES */
	//print_matrix(MAT_SIZE, A);
	//printf("**************************************\n");
	//print_matrix(MAT_SIZE, B);

	/* PARALLEL CALCULATING */
	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
	#pragma omp parallel shared(nthreads, A, B, C) private(tid, nthrds, i, j, k, myC)
	{
		// i: row iterator of A
		// j: col iterator of A equals to row iterator of B
		// k: col iterator of B
		tid = omp_get_thread_num();
		nthrds = omp_get_num_threads();
		myC = 0.0;
		#pragma omp master
		{
			nthreads = nthrds;
			printf("Starting parallel computing matrix multiplycation with %d threads...\n", nthreads);
		}

		printf("Thread %d is starting mat mul...\n", tid);
		for (i = tid; i < MAT_SIZE; i+=nthrds) {
			//printf("Thread %d calculated row%d\n", tid, i);
			for (k = 0; k < MAT_SIZE; ++k) {
				for (j = 0; j < MAT_SIZE; ++j) { myC += A[i][j] * B[j][k]; }
				// store result to matrix C
				C[i][k] = myC;
				myC = 0.0;
			}
		}
	}  /* End of parallel region */

	total_time = omp_get_wtime() - start_time;

	//printf("**************************************\n");
	//print_matrix(MAT_SIZE, C);

	printf("\ntotal parallel time: %f sec\n", total_time);
	free_matrix(MAT_SIZE, A);
	free_matrix(MAT_SIZE, B);
	free_matrix(MAT_SIZE, C);

	return 0;
}


/* FUNCTION IMPLEMENTATION */

// function to allocate memory for matrix with size n * n
double **malloc_matrix (int n) {
    double **mat = (double **) malloc(n * sizeof(double*));
    if (mat == NULL) {
        printf("\nMemory allocation for **mat failed. Abort.\n");
        return mat;
    }
    for (int i = 0; i < n; ++i) {
        mat[i] = (double *) malloc(n * sizeof(double));
        if (mat[i] == NULL) {
            printf("\nMemory allocation for *mat[%d] failed. Abort.\n", i);
            return mat;
        }
    }
    return mat;
}

// function to print matrix with size n * n
void print_matrix (int n, double **a) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf(" %4.2f ", a[i][j]);
        printf("\n");
    }
}

// free memory allocated for matrix of size n * n
void free_matrix (int n, double **a) {
    for (int i = 0; i < n; ++i)  free(a[i]);
    free(a);
    return;
}