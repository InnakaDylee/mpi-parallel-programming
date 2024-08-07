#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    MPI_Init(&argc, &argv); 
    
    // Memulai MPI
    
    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Comm_size (MPI_COMM_WORLD, &size);

 

    unsigned int m, n, p, q, i, j, k;

    double start_time, end_time, total_time;

 

    if (rank == 0){

    printf(" --- Implementasi Perkalian Matriks menggunakan Message Passing Interface pada HPC --- \n");
    printf(" ---------------------------------------------\n");
    printf(" Jumlah baris matriks A = jumlah kolom matriks B \n");
    printf("--------------------------------------------- \n");

    // Input panjang baris dan kolom pada matriks A dan B
    cin >> m;
    cin >> n;
    cin >> p;
    cin >> q;

     if (n != p || m != q){ {
        printf("Error: jumlah baris matriks A tidak sama dengan jumlah kolom matriks B. ");

        return 1;
    }
    
    }

    start_time = MPI_Wtime(); // mulai merekam waktu

    // processor 0 melakukan broadcast variable m, n, p dan q
   MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

   MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

   MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);

   MPI_Bcast(&q, 1, MPI_INT, 0, MPI_COMM_WORLD);

   }else{

    // processor 1, 2 dan 3 menerima broadcast

    // variable m, n, p dan q
    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Bcast(&q, 1, MPI_INT, 0, MPI_COMM_WORLD);

    }   

 

    // membagi baris matriks A untuk diproses lebih lanjut
    // oleh semua processor
    int baris_per_proses = m / size;
    //proses 1
    //1 2 3 4
    //proses 2
    //5 6 7 8
    int A[m][n], B[p][q], C[m][q],
    A_lokal[baris_per_proses][n],
    B_lokal[baris_per_proses][q],
    C_lokal[baris_per_proses][q];

 

    if (rank == 0){

        srand(time(NULL));

        for (i=0; i<m; i++) {   // membuat random elemen matriks A

            for (j = 0; j < n; j++) {

                A[i][j] = rand()% 10;

            }

        }

        for (i = 0; i < p; i++) {  // membuat random elemen matrik B

        for (j=0;j<q; j++) { 
            
            B[i][j] = rand()% 10;

        }

        }

    }

    // processor 0 membagi ratakan baris matriks A kepada semua processor
    MPI_Scatter (A, baris_per_proses*n, MPI_INT, A_lokal, baris_per_proses*n, MPI_INT, 0, MPI_COMM_WORLD);


    // processor 0 melakukan broadcast matriks B kesemua processor
    MPI_Bcast(&B, p*q, MPI_INT, 0, MPI_COMM_WORLD);

 

    // melakukan operasi perkalian matriks pada masing-masing processor
    for (i = 0; i < baris_per_proses; i++) {

        for (j=0; j<q; j++) {

            C_lokal[i][j] = 0;

        for (k = 0; k < n; k++) {

            C_lokal[i][j] += A_lokal[i][k] * B[k][j];

            }

        }

    }

     // processor 0 mengumpulkan semua matriks dari pekerjaan processor lain dan menjadikannya matriks C

    MPI_Gather(C_lokal, baris_per_proses*q, MPI_INT, C, baris_per_proses*q, MPI_INT, 0, MPI_COMM_WORLD);

 

    if (rank == 0){

        end_time = MPI_Wtime(); //berhenti merekam waktu

        total_time = end_time - start_time;

 
        //menampilkan matriks A, B dan C
        cout<<"Matriks A:" << endl;
            for (i=0; i<m; i++) {

                for (j = 0; j < n; j++) {

                printf("%d ", A[i][j]);

        }

        cout<<"" << endl;

        }

    

        cout<<" Matriks B: \n" << endl;
        for (i = 0; i < p; i++) {

            for (j = 0; j<q; j++) {

                printf("%d ", B[i][j]);

        }

        cout<< "" << endl;

        }

    

        cout<< " Matriks C = A*B: \n" << endl;
        for (i=0; i<m; i++) {

            for (j=0;j<q; j++) { 

                printf("%d ", C[i][j]);

        }

        cout<<"" << endl;
        }

    }
    //720/8 = 90
    
    if (rank==0){

        // menampilkan total waktu eksekusi program
        printf(" Total waktu komputasi: %fdetik ", total_time);

    }

    MPI_Finalize(); //MPI berakhir

    return 0;

    }
 