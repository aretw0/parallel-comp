/* 	EX3:
	Implemente uma busca simples em um vetor.
	A busca deve ser dividida entre as threads.
	Para cada posição do vetor testada, a thread deve imprimir na tela se encontrou ou não o elemento.
	No fim, o programa deve informar se o elemento está ou não no vetor, caso esteja,
	onde se encontra e qual thread o encontrou. 
*/
#include <omp.h>
#include <iostream>
using namespace std;

#define N 5
#define MAX 100 // 0-MAX
#define TAM 50 // Nunca maior que MAX

int main() {
	bool uniqueOn = false; // desligar unicidade ou não
	
	int n, i, tid, tWin[N] = { 0 }, nCount[TAM];
	bool findit = false; 

	// inicializando com valores aleatórios e únicos
	for(i=0;i<TAM;i++)
	{
		if (uniqueOn) {
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
		} else {
			nCount[i] = rand()%(1+MAX);
		}
	}

	cout << "- Busca paralela -\n\nEntre com um inteiro positivo entre 0 a "<< MAX <<": ";
	cin >> n;
	cout << endl;

	omp_set_num_threads(N);
	#pragma omp parallel for private(tid)
	for (i = 0; i < TAM; ++i)
	{
		tid = omp_get_thread_num();
		if (nCount[i] == n) {
			findit = true;
			++tWin[tid];
			#pragma omp critical
			cout << "Thread nº" << tid << " encontrou.\n";
		} else {
			#pragma omp critical
			cout << "Thread nº" << tid << " não encontrou.\n";
		}
	}

	if (findit) {
		cout << "\nO elemento está no vetor!\n";
		cout << "E as Threads que encontraram o elemento foram: \n";
		for (i = 0; i < N; ++i) {
			if (tWin[i] != 0) {
				cout << "Thread nº" << i << endl;
			}
		}
	} else {
		cout << "\nO elemento não está no vetor!\n";
	}

	return 0;
}