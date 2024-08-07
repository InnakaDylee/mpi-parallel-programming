#include <mpi.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Memulai MPI

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Mengambil rank dari proses

    if (world_rank == 0) {
         // Rank 0 as the sender
         printf("%d",world_rank);
        int size;
        MPI_Comm_size(MPI_COMM_WORLD, &size); // Mengambil total jumlah proses

        for (int i = 0; i < size; ++i) {    
            // Mengirim pesan ke proses dengan rank i
            MPI_Send(&i, 1, MPI_INT, i, 0, MPI_COMM_WORLD); 
        }

        for (int i = 0; i < size; ++i) {
            int message;
            // Mengambil pesan dari proses dengan rank i
            MPI_Recv(&message, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
            cout << "Received square from process " << i << ": " << message << endl;
        }
    } else { // Proses dengan rank selain 0 sebagai receiver
         printf("%d",world_rank);
        int number;
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); // Mengambil pesan dari proses dengan rank 0

        number *= number; 

        MPI_Send(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD); // Mengirim pesan ke proses dengan rank 0
    }

    MPI_Finalize(); // Mengakhiri MPI
    return 0;
}
