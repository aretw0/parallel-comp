/*  EX5:
    Crie um programa que calcule a média dos números contidos em um vetor.
    O processo master deve criar um vetor aleatório de números e dividir entre os demais processos partes do vetor.
    Cada um deve calcular a média de sua parte e devolver ao processo master.
    Por fim o processo master deve informar a média geral.
    Obrigatório o uso de comunicação em grupo.
*/

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

#define MAX 10000 // 0-MAX
#define TAM 10000 // Nunca maior que MAX
 
int main(int argc, char* argv[]) {
    int i, n, lim, rank, tam, sum = 0, size = 0;
    float med;
    int* nCount = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    if (rank == 0) {
        srand(time(NULL));
        nCount = new int[TAM];
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

        size = TAM / (tam - 1);
        int tamTotal = TAM;
        for (i = 0; i < tam; i++) {
            if (i != rank) {
                if (i == (tam - 1)) size = tamTotal;
                else tamTotal -= size;
                MPI_Send(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(&nCount[(i-1)*n], size, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        float medsSum = 0;

        for (i = 1; i < tam; i++) {
            if (i != rank) {
                MPI_Recv(&med, 1, MPI_FLOAT, i, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // cout << "Recebido med " << med << endl;
                ++sum;
                medsSum += med;
            }
        }
        cout << "\nA média geral é: " << medsSum/(float)sum << endl;
    } else {

        MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        nCount = new int[size];
        MPI_Recv(nCount, size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        /* cout << "\nProcesso nº" << rank << " de "<< tam << " recebeu:\n";
        for (i = 0; i < size; i++)
        {
            cout << nCount[i] << endl;
        } */

        for(i = 0; i < size; i++) {
            sum += nCount[i];
        }
        
        med = (float)sum/(float)size;
        // cout << "Média de Processo nº" << rank << " de "<< tam << ": " << med << endl;
        MPI_Send(&med, 1, MPI_FLOAT, 0, rank, MPI_COMM_WORLD);
    }
    delete [] nCount; 
    nCount = NULL;
    MPI_Finalize();
    return 0;
}