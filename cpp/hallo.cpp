#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv); // Memulai MPI

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); // Mengambil total jumlah proses

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); // Mengambil rank dari proses

    cout << "Hello World from process " << world_rank << " of " << world_size << endl;

    MPI_Finalize(); // Mengakhiri MPI
    return 0;

}