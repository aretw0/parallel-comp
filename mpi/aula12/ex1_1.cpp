/*  EX1:
    Crie três programas que calculem a média dos números contidos em um vetor.
    O processo master deve criar um vetor aleatório de números e dividir entre os demais processos partes do vetor.
    Cada um deve calcular a média de sua parte e devolver ao processo master.
    Por fim o processo master deve informar a média geral.
    Obrigatório o uso de 'Broadcast', 'Reduce', 'Scatter' e 'Gatter'.
*/

// Broadcast

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std; 

#define MAX 10000 // 0-MAX
#define TAM 10000 // Nunca maior que MAX
 
int main(int argc, char* argv[]) {
    int i, n, lim, rank, tam, sum = 0;
    float med;
    int nCount[TAM];

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
       /*  cout << "\nProcesso nº" << rank << " de "<< tam << " inicializou:\n";
        for (i = 0; i < TAM; i++)
        {
            cout << nCount[i] << endl;
        } */

        MPI_Bcast( nCount, TAM, MPI_INT, 0, MPI_COMM_WORLD);

        float medsSum = 0;

        for (i = 1; i < tam; i++) {
            if (i != rank) {
                MPI_Bcast(&med, 1, MPI_FLOAT, i, MPI_COMM_WORLD);
                // cout << "Recebido med " << med << endl;
                ++sum;
                medsSum += med;
            }
        }
        cout << "A média geral é: " << medsSum/(float)sum << endl;
    } else {
        MPI_Bcast( nCount, TAM, MPI_INT, 0, MPI_COMM_WORLD);
        
        n = TAM / (tam - 1);
        lim = rank * n;
        if (rank == (tam - 1)) {
            lim = TAM;
        }

        // cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu:\n";
        int size = 0;
        for(i = (rank - 1) * n; i < lim; i++) {
            // cout << nCount[i] << endl;
            if (i >= TAM ) break;
            sum += nCount[i];
            ++size;
        }

        med = (float)sum/(float)size;
        MPI_Bcast( &med, 1, MPI_FLOAT, rank, MPI_COMM_WORLD);
        // cout << "Média de Processo nº" << rank << " de "<< tam << ": " << med << endl;
    }

    MPI_Finalize();
    return 0;
}