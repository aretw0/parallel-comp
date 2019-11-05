// EX1: Crie 5 threads que escrevam seus IDs na tela

#include <omp.h>
#include <iostream>
using namespace std;

int main() {
	omp_set_num_threads(5);
	int tid;
	#pragma omp parallel private(tid)
	{
		tid = omp_get_thread_num();
		cout << "Thread ID: " << tid << endl;
	}
	return 0;
}