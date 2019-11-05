/*	EX2:
	Crie um vetor de inteiros de um tamanho qualquer, com valores inicializados.
	Faça o produto desse vetor com um número escalar (as multiplicações devem ser feitas em paralelo).
	Ao final, mostre o resultado do vetor após a multiplicação.
*/
#include <omp.h>
#include <iostream>
using namespace std;

int main() {
	int n = 5;
	int nCount[n] = {0, 1, 2, 3, 4}, i = 0;
	int scalar = 10;

	#pragma omp parallel for simd
	for (i = 0; i < n; ++i)
		nCount[i] *= scalar;

	cout << "Resultado:\n";
	for (i = 0; i < n; ++i)
	{
		cout << "nCount[" << i << "] = " << nCount[i] << endl;
	}
	return 0;
}