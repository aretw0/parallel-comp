/* EX2:
	Imagine que threads de um programa paralelo qualquer estão em uma "corrida".
	Todas elas só podem iniciar suas tarefas em um determinado instante.
	Implemente um programa que execute uma tarefa qualquer em paralelo,
	todas as threads devem imprimir a hora de início da tarefa (deve ser o mesmo tempo para todas).
	Note que é necessária uma sincronização.
*/
#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

#define N 8

int main() {
	time_t rawtime;
  	struct tm * timeinfo;
  	char buffer [80];

	omp_set_num_threads(N);

	int n, i, tid;
	bool isPrime;
	cout << "- Primos paralelos -\n\nEntre com um inteiro positivo: ";
	cin >> n;
	cout << endl;

	#pragma omp parallel private(rawtime,timeinfo,buffer,tid,isPrime,i)
	{
		tid = omp_get_thread_num();
		#pragma omp barrier
		time(&rawtime);
		timeinfo = localtime (&rawtime);
  		strftime (buffer,80,": %X",timeinfo);
  		#pragma omp critical
		cout << "Thread nº" << tid << ": " << buffer << endl;
		#pragma omp barrier
		#pragma omp single
		cout << endl;
		
		isPrime = true;
		for(i = 2; i <= n / 2; ++i)
		{
			if(n % i == 0)
			{
			  isPrime = false;
			  break;
			}
		}
		#pragma omp critical
		{
			cout << "Thread nº" << tid << " descobriu que ";
			if (isPrime)
				cout << "n=" << n << " é um número primo.";
			else
			  	cout << "n=" << n << " não é um número primo.";
			cout << endl;
		}
	}

	return 0;
}