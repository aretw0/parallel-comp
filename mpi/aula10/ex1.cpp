/*  EX1:
    Implemente uma busca simples em um vetor.
    A busca deve ser dividida entre os processos.
    Para cada posição do vetor testada, a processo deve imprimir na tela se encontrou ou não o elemento.
    No fim, o programa deve informar se o elemento está ou não no vetor, caso esteja, onde se encontra e
    qual processo o encontrou.
*/

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

#define MAX 100 // 0-MAX
#define TAM 50 // Nunca maior que MAX
 
int main(int argc, char* argv[]) {
    int i, n, lim, rank, tam, nCount[TAM], prey = -1, target;
    bool findit = false;

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
        cout << "- Busca paralela -\n\nEntre com um inteiro positivo entre 0 a "<< MAX << ": ";
        cin >> target;
        cout << endl;
        for (i = 0; i < tam; i++) {
            if (i != rank) {
                MPI_Send(&target, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&nCount, TAM, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

    } else {
        MPI_Recv(&target, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu " << target << endl;
        MPI_Recv(&nCount, TAM, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        /* cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu:\n";
        for (i = 0; i < TAM; i++)
        {
            cout << nCount[i] << endl;
        } */
    }

    n = TAM / tam;

	lim = (rank + 1) * n;
    if (rank == (tam - 1)) {
        lim = TAM;
    }
	// cout << "Processo nº" << rank << " de "<< tam << ". Params: n(" << n << ") - lim(" << lim << ")\n";

    for(i = rank * n; i < lim; i++) {
        if (i >= TAM ) break;
        cout << "Processo nº" << rank << " de "<< tam;
        if (nCount[i] == target) {
            cout << " encontrou.\n";
            findit = true;
            prey = i;
            break;
        } else {
            cout<< " não encontrou.\n";
        }
    }

    cout << "\nProcesso nº" << rank << " de "<< tam;
    if (findit) {
        cout << " encontrou " << target << " na posição " << prey << ".\n\n";
    } else {
        cout << " não encontrou "<< target << ".\n\n";
    }
   
    MPI_Finalize();
    return 0;
}