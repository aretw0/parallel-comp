/* 	EX3:
	Reescreva o código seguinte, colocando as operações de barreira explicitamente,
	de modo a maximizar o desempenho, mas sem alterar o resultado da execução.

	#pragma omp parallel
	{
		#pragma omp for
		for (j = 0; j < n; j++){
			a[j]= b[j] + c[j];
		}
		#pragma omp for
		for (j = 0; j < n; j++){
			d[j] = e[j] * f;
		}
		#pragma omp for
		for (j = 0; j < n; j++){
			z[j] = (a[j]+a[j+1]) * 0.5;
		}
	}
*/

#include <omp.h>
#include <iostream>
using namespace std;

#define TAM 5
int main() {
	int j, f = 10;
	int a[TAM], b[TAM] = { 1,2,3,4,5}, c[TAM] = { 5,4,3,2,1}, d[TAM], e[TAM] = {2,5,3,1,4};
	float z[TAM];
	#pragma omp parallel private(j)
	{
		#pragma omp for
		for (j = 0; j < TAM; j++){
			a[j]= b[j] + c[j];
		}
		#pragma omp for
		for (j = 0; j < TAM; j++){
			d[j] = e[j] * f;
		}
		#pragma omp barrier
		#pragma omp for
		for (j = 0; j < TAM; j++){
			z[j] = (a[j]+a[j+1]) * 0.5;
		}
	}

	cout << "\nVetores resultado:\n";
	for (j = 0; j < TAM; ++j) {
		cout << "a[" << j << "] = " << a[j] << endl;
		cout << "d[" << j << "] = " << d[j] << endl;
		cout << "z[" << j << "] = " << z[j] << endl;
	}
	return 0;
}