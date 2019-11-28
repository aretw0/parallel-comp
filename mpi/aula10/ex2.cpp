/*  EX1:
    Faça um programa de forma que o master envie a frase "Hello  World" em duas partes: "World" e "Hello"
    (necessariamente nessa ordem). Os slaves devem imprimir a frase na ordem correta.
*/

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

#define TAM 6

int main(int argc, char* argv[]) {
    int i, rank, tam;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    if (rank == 0) {
        char first[] = "Hello\0", last[] = "World\0";
        for (i = 0; i < tam; i++) {
            if (i != rank) {
                MPI_Send(&last, TAM, MPI_BYTE, i, 0, MPI_COMM_WORLD);
                MPI_Send(&first, TAM, MPI_BYTE, i, 0, MPI_COMM_WORLD);
            }
        }
        cout << "Processo nº" << rank << " de "<< tam << " envia: " << last << " " << first << endl;
    } else {
        char first[TAM], last[TAM];
        MPI_Recv(&last, TAM, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu " << target << endl;
        MPI_Recv(&first, TAM, MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo nº" << rank << " de "<< tam << " diz: " << first << " " << last << endl;
    }

    MPI_Finalize();
    return 0;
}