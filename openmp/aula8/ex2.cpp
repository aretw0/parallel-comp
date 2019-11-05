/* 	EX1:
	Criar 4 threads que multipliquem todos os elementos de um vetor por um escalar e ache o maior elemento.
	As operações devem ser realizadas em paralelo.
*/
#include <omp.h>
#include <iostream>
using namespace std;

#define N 4
#define TAM 30
#define SCALAR 7

int main() {
	int i, n, nCount[TAM], index = -1, major = -2147483648;

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

	omp_set_num_threads(N);
	#pragma omp parallel for
	for (i = 0; i < TAM; ++i) {
		nCount[i] *= SCALAR;
		if (nCount[i] >= major) {
			index = i;
			major = nCount[i];
		}
	}

	cout << "\nVetor multiplicado por escalar:\n";
	for (i = 0; i < TAM; ++i) cout << "nCount[" << i << "] = " << nCount[i] << endl;

	cout << "\nO maior elemento é nCount[" << index << "] = " << nCount[index] << endl;
	return 0;
}