// EX3:	Implemente um programa que calcule a soma dos elementos de um vetor em paralelo.

#include <omp.h>
#include <iostream>
using namespace std;

#define N 10

int main() {
	int i;
	float nCount[N], result;

	#pragma omp parallel for simd
	for (i = 0; i < N; ++i)
		nCount[i] = (i+1) * 1.0;

	for (i = 0; i < N; ++i)
		cout << "nCount[" << i << "] = " << nCount[i] << endl;

	#pragma omp parallel for simd
	for (i = 0; i < N; ++i)
		result += nCount[i];
		
	cout << "\nResultado: " << result << endl;

	return 0;
}