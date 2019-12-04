//  EX3: Calcule se um numero é primo ou não.

#include <mpi.h>
#include <iostream>
#include <time.h>
using namespace std;

int main(int argc, char* argv[]) {
    int i, n, lim, rank, tam, target;
    bool *res = NULL;
    bool isPrime = true;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&tam);

    /* cout << "Processo " << rank << " inicializou:\n";
    for (i = 0; i < tam; ++i) {
        cout << VetInt[i] << endl;
    } */

    if (rank == 0) {
        res = new bool[tam];
        cout << "- Primos paralelos -\n\nEntre com um inteiro positivo: ";
	    cin >> target;
	    cout << endl;
    }

    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    n = target / tam;

    lim = (rank + 1) * n;
    if (rank == (tam - 1)) {
        lim = target;
    }

    for(i = rank * n; i <= lim; i++) {
        if (i <= 1) continue;
        int cal = i + 2;
        if (cal > target) break;
        if(target % i == 0)
        {
            isPrime = false;
            break;
        }
    }

    MPI_Gather(&isPrime, 1, MPI_CXX_BOOL, res, 1, MPI_CXX_BOOL, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        if (isPrime) {
            for (i = 0; i < tam; ++i) {
                if (!res[i]){
                    isPrime = false;
                    break;
                }
            }
        }
        cout << target;
        if (isPrime) {
            cout << " é um número primo\n";
        } else {
            cout << " não é um número primo\n";
        }
        delete [] res;
        res = NULL;
    }

    MPI_Finalize();
    return 0;
}