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
    int i, rank, tam, *VetInt = NULL, *RecInt = NULL, rec;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    VetInt = new int[tam];
    RecInt = new int[tam];
    int val = rank * tam;
    for (i = 0; i < tam; ++i) {
        VetInt[i] = val++;
    }
    
    /* for (i = 0; i < tam; ++i) {
        cout << "Processo " << rank << " inicializou: " << VetInt[i] << endl;
    } */

    MPI_Scatter(VetInt, 1, MPI_INT, &rec, 1, MPI_INT, 0, MPI_COMM_WORLD);
    cout << "Processo " << rank << " recebeu (SCATTER): " << rec << endl;
    MPI_Gather(&rec, 1, MPI_INT, RecInt, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (i = 0; i < tam; ++i) {
            cout << "Processo " << rank << " recebeu (GATHER): " << RecInt[i] << endl;
        }
    }

    MPI_Allgather(&rec, 1, MPI_INT, RecInt, 1, MPI_INT, MPI_COMM_WORLD);

    for (i = 0; i < tam; ++i) {
        cout << "Processo " << rank << " recebeu (ALLGATHER): " << RecInt[i] << endl;
    }

    MPI_Alltoall(VetInt, 1, MPI_INT, RecInt, 1, MPI_INT, MPI_COMM_WORLD);

    for (i = 0; i < tam; ++i) {
        cout << "Processo " << rank << " recebeu (ALLTOALL): " << RecInt[i] << endl;
    }

    delete [] VetInt;
    VetInt = NULL;
    delete [] RecInt;
    RecInt = NULL;
    MPI_Finalize();
    return 0;
}