/* 	EX4:
	Implemente um programa paralelo que varra um vetor e mostre seus elementos na tela,
	juntamente com a identificação da thread que o imprimiu.
	Os elementos devem ser impressos necessariamente em ORDEM. 
*/
#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

#define N 10
#define TAM 30
#define STEP 3 // step do ordered

int main() {
	int i, n, nCount[TAM];
	srand(time(NULL));

	// inicializando com valores aleatórios e únicos
	for(i=0;i<TAM;i++)
	{
	    bool unique;
	    do
	    {
	      unique=true;
	      n=rand()%TAM;
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
	
	omp_set_num_threads(N);
	#pragma omp parallel for ordered schedule(static, STEP)
	for (i = 0; i < TAM; ++i) {
		#pragma omp ordered
		cout << "Thread nº" << omp_get_thread_num() << " | nCount[" << i << "]\t= " << nCount[i] << endl;
	}

	return 0;
}