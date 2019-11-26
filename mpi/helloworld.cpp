#include <mpi.h>
#include <iostream>
using namespace std;
 
int main(int argc, char* argv[]) {
    int rank, tam;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);
    cout << "Olá Mundo, sou o processo " << rank << " de " << tam << endl;
    MPI_Finalize();
    return 0;
}