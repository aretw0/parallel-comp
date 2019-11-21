/* 	EX2:
	Implemente o jogo "pedra-papel-tesoura" onde os jogadores são threads.
    Como entrada tem-se a quantidade de rodadas que serão jogadas.
    Como saída, deve-se apresentar uma mensagem mostrando o placar final.
    Lembrando que pedra vence tesoura, que vence papel, que vence pedra. 
*/
#include <omp.h>
#include <iostream>
#include <time.h>
using namespace std;

#define PPT 3
#define PEDRA 0
#define PAPEL 1
#define TESOURA 2

int main() {
    omp_set_num_threads(2);
    int win1 = 0, win2 = 0;
    int res1, res2;

	int n = 1;

    srand(time(NULL));

    cout << "- Pedra, papel e tesoura -\n\nEntre com o nº de rodadas: ";
	cin >> n;
	cout << endl;

    // ate aqui

    //  int resto = num1 % num2;

	// inicializando com valores aleatórios e únicos
    for (int i = 0; i < n; i++)
    {   
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                res1 = rand() % PPT;
            }
            #pragma omp section
            {
                res2 = rand() % PPT;
            }
        }
        if (res1 != res2) {
            if (res1 == PEDRA && res2 == TESOURA) {
                ++win1;
            } else if (res2 == PEDRA && res1 == TESOURA) {
                ++win2;
            } else if (res1 == PEDRA && res2 == PAPEL) {
                ++win2;
            } else if (res2 == PEDRA && res1 == PAPEL) {
                ++win1;
            } else if (res1 == PAPEL && res2 == TESOURA) {
                ++win2;
            } else if (res2 == PAPEL && res1 == TESOURA) {
                ++win1;
            }
        }
    }

    cout << "-- Placar final ("<< n <<" rodadas) --\n\n";
    cout << "- Thread nº1: " << win1 << " vitórias.\n";
    cout << "- Thread nº2: " << win2 << " vitórias.\n";

	return 0;
}