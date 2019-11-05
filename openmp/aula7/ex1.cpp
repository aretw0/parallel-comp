/* EX1:
	Implemente um programa que realize a soma e a subtração de dois vetores simultaneamente, ou seja,
	dado um vetor A e B com valores, realize a soma e armazene em  C  e  a  subtração  em  D.
	O cálculo de C e D deve ser feito de forma simultânea, por  2 threads. 
*/
#include <omp.h>
#include <iostream>
using namespace std;

#define N 10

int main() {
	int i
	float a[N], b[N],c[N],d[N];

	#pragma omp parallel for simd
	for (i = 0; i < N; ++i) {
		a[i] = (i+5) * 1.0;
		b[i] = i * 1.0;
	}

	#pragma omp parallel private(i)
	{
		#pragma omp sections nowait
		{
			#pragma omp section
			{
				#pragma omp critical
				cout << "Thread Add nº" << omp_get_thread_num() << endl;

				#pragma omp parallel for simd
				for (i = 0; i < N; ++i)
					c[i] = a[i] + b[i];
				/*for (i=0; i<N; i++)
					c[i] = a[i] + b[i];*/
				
			}
			#pragma omp section
			{
				#pragma omp critical
				cout << "Thread Sub nº" << omp_get_thread_num() << endl;
				
				#pragma omp parallel for simd
				for (i = 0; i < N; ++i)
					d[i] = a[i] - b[i];
				/*for (i=0; i<N; i++)
					d[i] = a[i] - b[i];*/
			}
		}
	}

	for (i = 0; i < N; ++i) {
		cout << "c[" << i << "] = " << c[i] << endl;
		cout << "d[" << i << "] = " << d[i] << endl;
	}

	return 0;
}