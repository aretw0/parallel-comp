/*  EX2:
    Crie um programa, invocando rotinas do MPI que execute as seguintes tarefas:
    Cada processo será inicializado por vetores distintos de N inteiros, onde "N" é igual ao número de processos.
    Por exemplo: o processo 1 terá um vetor VetInt = {1, 2, 3, 4}; o processo 2, VetInt = {5, 6, 7, 8}, etc.
    O processo 0 (zero), executa, sequencialmente os seguintes comandos: Scatter do processo 0;
    Gatter: também do processo 0. AllGatter(coleta global); AlltoAll(distribuição global).
    Então, o mesmo processo 0 exibe os dados do vetor resultante. Comente os resultados encontrados.
*/

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) {
    int i, rank, tam, *VetInt = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    VetInt = new int[tam];
    int val = rank * tam;
    for (i = 0; i < tam; ++i) {
        VetInt[i] = val++;
    }
    /* cout << "Processo " << rank << " inicializou:\n";
    for (i = 0; i < tam; ++i) {
        cout << VetInt[i] << endl;
    } */

    MPI_Scatter(VetInt, 1, MPI_INT, VetInt, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(VetInt, 1, MPI_INT, VetInt, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Allgather(VetInt, 1, MPI_INT, VetInt, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Alltoall (VetInt, 1, MPI_INT, VetInt, 1, MPI_INT, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Resultado final: \n";
        for (i = 0; i < tam; ++i) {
            cout << VetInt[i] << endl;
        }
    }

    delete [] VetInt;
    VetInt = NULL;
    MPI_Finalize();
    return 0;
}