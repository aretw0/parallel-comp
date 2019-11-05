/* EX3:
	Implemente a soma de vetores em paralelo.
	Crie e inicialize dois vetores A e B.
	Armazene a soma  deles em um vetor C.
	O programa deve exibir qual thread realizou cada operação.
	Mostre o resultado. 
*/
#include <omp.h>
#include <iostream>
using namespace std;

#define N 10

int main() {
	int i, tid;
	float a[N], b[N], c[N];

	for (i=0; i<N; i++)
		a[i] = b[i] = i*1.0;

	#pragma omp parallel private(i,tid)
	{
		#pragma omp for
		for (i=0; i<N; i++) {
			tid = omp_get_thread_num();
			cout << "Thread nº" << tid << "  ";
			cout << "c[" << i << "] = " << "a[" << i << "] + b[" << i << "]\n"; 
			c[i] = a[i] + b[i]; 
		}
	}

	cout << "\nResultado:\n";
	for (i = 0; i < N; ++i)
		cout << "c[" << i << "] = " << c[i] << endl;

	return 0;
}