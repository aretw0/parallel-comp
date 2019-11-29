/*  EX3:
    Crie um programa paralelo que encontre o menor número em um vetor.
    O vetor deve ter um tamanho considerável e a tarefa deve ser dividida entre os slaves.
    O processo master não deve participar efetivamente da busca.
*/

#include <mpi.h>
#include <iostream>
#include <time.h>
#include <limits.h>
using namespace std;

#define MAX 10000 // 0-MAX
#define TAM 10000 // Nunca maior que MAX
 
int main(int argc, char* argv[]) {
    int i, n, lim, rank, tam, nCount[TAM], prey = INT_MAX, target = -1;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    if (rank == 0) {
        srand(time(NULL));

        for(i=0;i<TAM;i++)
        {
            bool unique;
            do
            {
                unique=true;
                n=rand()%(1+MAX);
                for(int i1=0;i1<i;i1++)
                {
                    if(nCount[i1]==n)
                    {
                        unique=false;     
                        break;
                    }
                }
            }while(!unique);
            nCount[i]=n;
        }
        for (i = 0; i < tam; i++) {
            if (i != rank) {
                MPI_Send(&nCount, TAM, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        int preyW;
        int targetW;
        int rankW;

        for (i = 1; i < tam; i++) {
            if (i != rank) {
                MPI_Recv(&preyW, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MPI_Recv(&targetW, 1, MPI_INT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                /* cout << "Recebido preyW " << preyW << " targetW " << targetW << endl;
                cout << "Com prey " << prey << " target " << target << endl; */
                if (preyW < prey) {
                    prey = preyW;
                    target = targetW;
                    rankW = i;
                }
            }
        }
        cout << "O menor número do vetor é o " << prey << " se encontra na posição [" << target << "].\n";
        cout<< "E foi encontrado pelo processo " << rankW << ".\n";
    } else {

        MPI_Recv(&nCount, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        /* cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu:\n";
        for (i = 0; i < TAM; i++)
        {
            cout << nCount[i] << endl;
        } */

        n = TAM / (tam - 1);

        lim = rank * n;
        if (rank == (tam - 1)) {
            lim = TAM;
        }
        // cout << "Processo nº" << rank << " de "<< tam << ". Params: n(" << n << ") - lim(" << lim << ")\n";

        for(i = (rank - 1) * n; i < lim; i++) {
            if (i >= TAM ) break;
            if (nCount[i] < prey) {
                prey = nCount[i];
                target = i;
                break;
            }
        }

        MPI_Send(&prey, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
        MPI_Send(&target, 1, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}