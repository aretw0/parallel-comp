#include <omp.h>
#include <iostream>
using namespace std;


int main() {
	int nthreads, tid;
	#pragma omp parallel private(nthreads,tid)
	{
		tid = omp_get_thread_num();
		cout << "A Thread " << tid << " diz Oi Mundo \n";
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			cout << "O numero de Threads é "<< nthreads <<"\n";
		}
	}
	return 0;
}