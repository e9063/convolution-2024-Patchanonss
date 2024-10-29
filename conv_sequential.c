#include <stdio.h>
#include <stdlib.h>
// #include <omp.h>

// Function prototypes
void read_input(int *NA, int *NF, int **A, int **F);
void convolve_sequential(int *A, int *F, int NA, int NF, long long int *R);

int main() {
    // Read input
    int NA, NF;
    int *A, *F;
    long long int *R;
    read_input(&NA, &NF, &A, &F);

    // Allocate memory for result
    R = (long long int*)malloc(sizeof(long long int) * (NA - NF + 1));

    // Sequential convolution
    // double start_time = omp_get_wtime();
    convolve_sequential(A, F, NA, NF, R);
    // double end_time = omp_get_wtime();
    // printf("Sequential time: %f seconds\n", end_time - start_time);

    for (int i = 0; i <= NA - NF; i++) {
        printf("%lld\n", R[i]);  // Print the result
    }
    // Free allocated memory
    free(A);
    free(F);
    free(R);

    return 0;
}

void read_input(int *NA, int *NF, int **A, int **F) {
    // Read the sizes of A and F
    scanf("%d %d", NA, NF);

    // Allocate memory for A and F
    *A = (int*)malloc(*NA * sizeof(int));
    *F = (int*)malloc(*NF * sizeof(int));

    // Read elements of A
    for (int i = 0; i < *NA; i++) {
        scanf("%d", &(*A)[i]);
    }

    // Read elements of F
    for (int i = 0; i < *NF; i++) {
        scanf("%d", &(*F)[i]);
    }
}

void convolve_sequential(int *A, int *F, int NA, int NF, long long int *R) {
    long long int *FF = (long long int*) malloc(NF * sizeof(long long int));

    // Reverse the filter F into FF
    for (int i = 0; i < NF; i++) {
        FF[i] = F[NF - 1 - i];
    }

    // Perform the convolution
    for (int i = 0; i <= NA - NF; i++) {
        long long int sum = 0;
        for (int j = 0; j < NF; j++) {
            sum += (long long int)A[i + j] * FF[j];
        }
        R[i] = sum;  // Store as int if output array R should be int
        // printf("Output is %lld\n", sum);
    }

    free(FF);
}

