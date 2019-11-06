/* 	EX2:
	Paralelize o exemplo a seguir sem o uso da diretiva #pragma ompparallel for.
	for(i = 0; i < n; i++)
		z[i] = a * x[i] + y;
*/
#include <omp.h>
#include <iostream>
using namespace std;

#define N 4
#define TAM 40

int main() {
	int i, tid, lim, n, nthreads, nCount[TAM], rCount[TAM];

	int a = 5, y = 10;

	// inicializando com valores aleatórios e únicos
	for(i=0;i<TAM;i++)
	{
	    bool unique;
	    do
	    {
	      unique=true;
	      n=rand()%(1+TAM);
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

	cout << "Vetor inicializado:\n";
	for (i = 0; i < TAM; ++i) cout << "nCount[" << i << "] = " << nCount[i] << endl;
	cout << endl;

	#pragma omp parallel private(i,tid,n,lim,nthreads)
	{
		// pensei em dividir as tarefas entre as threads, vamo ver se consigo
		tid = omp_get_thread_num();
		nthreads = omp_get_num_threads();
		n = TAM / nthreads;

		lim = (tid + 1) * n;
		#pragma omp critical
		cout << "Thread nº" << tid << "\tParams: nthreads(" << nthreads << ") - n(" << n << ") - lim(" << lim << ")\n";

		for(i = tid * n; i < lim; i++) {
			if (i >= TAM ) break;
			rCount[i] = a * nCount[i] + y;
		}

	}

	cout << "\nVetor resultado:\n";
	for (i = 0; i < TAM; ++i) cout << "rCount[" << i << "] = " << rCount[i] << endl;

	return 0;
}