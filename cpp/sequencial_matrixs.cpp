#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <iostream>

using namespace std;

int main(){ 

    int m, n, p, q, i, j, k; 

    clock_t start_time, end_time; 

    double cpu_time_used; 

    printf(" --- Perkalian Matriks --- \n"); 

    // Input matriks A dan B   
    cin >> m;
    cin >> n;
    cin >> p;
    cin >> q;

    

    if (n != p) { 

    printf("Error: jumlah baris matriks A tidak sama dengan jumlah kolom matriks. "); 

    return 1;

    }

 

    start_time = clock();

 

    int A[m][n], B[p][q], C[m][q];

 

    srand(time(NULL));

    printf("\nMatrix A: \n");

    for (i = 0; i < m; i++) {

        for (j = 0; j < n; j++) {

        A[i][j] = rand()% 10;

         printf("%d ", A[i][j]);

        }

        printf(" \n");

    }

    printf("\nMatrix B: \n");

    for (i = 0; i < p; i++) {

        for (j = 0; j < q; j++) {

            B[i][j] = rand()% 10;

            printf("%d ", B[i][j]);

        }

        printf(" \n");

    }

 
    printf(" \n");
    for (i=0; i<m; i++) {

        for (j=0; j<q; j++) {

            C[i][j] = 0;

            for (k = 0; k < n; k++) {

                C[i][j] += A[i][k] * B[k][j];

            }

        }

    }

 

    end_time = clock();

 

    // Display the resulting matrix C

    printf("Matrix C = A*B: \n"); 

    for (i=0; i<m; i++) {

        for (j=0;j<q; j++) {

            printf("%d ", C[i][j]);

        }

    printf("\n ");

    }

 

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Total waktu komputasi: %f detik ", cpu_time_used);

    return 0;
}