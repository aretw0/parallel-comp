/*  EX1:
    Crie três programas que calculem a média dos números contidos em um vetor.
    O processo master deve criar um vetor aleatório de números e dividir entre os demais processos partes do vetor.
    Cada um deve calcular a média de sua parte e devolver ao processo master.
    Por fim o processo master deve informar a média geral.
    Obrigatório o uso de 'Broadcast', 'Reduce', 'Scatter' e 'Gatter'.
*/

// Scatter e Gatter

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std; 

#define MAX 10000 // 0-MAX
#define TAM 10000 // Nunca maior que MAX
 
int main(int argc, char* argv[]) {
    int i, size, n, lim, rank, tam, sum = 0, *rCount = NULL, *nCount = NULL;
    float med, *recData = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    size = TAM / tam;

    rCount = new int[size];

    if (rank == 0) {
        recData = new float[tam];
        nCount = new int[TAM];

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
        /* cout << "\nProcesso nº" << rank << " de "<< tam << " inicializou:\n";
        for (i = 0; i < TAM; i++)
        {
            cout << nCount[i] << endl;
        } */
    }

    MPI_Scatter(nCount, size, MPI_INT, rCount, size, MPI_INT, 0, MPI_COMM_WORLD);
        
    // cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu:\n";
    for(i = 0; i < size; i++) {
        // cout << rCount[i] << endl;
        if (i >= TAM ) break;
        sum += rCount[i];
    }

    med = (float)sum/(float)size;
    // cout << "Média de Processo nº" << rank << " de "<< tam << ": " << med << endl;
    
    MPI_Gather(&med, 1, MPI_FLOAT, recData, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        float fsum = 0;
        // cout << "Recebeu: " << endl;
        for (i = 0; i < tam; i++)
        {
            // cout << recData[i] << endl;
            fsum += recData[i];
        }

        cout << "A média geral é: " << fsum/(float)tam << endl;

        delete [] nCount;
        delete [] recData;
        nCount = NULL;
        recData = NULL;
    }

    delete [] rCount;
    rCount = NULL;
    MPI_Finalize();
    return 0;
}