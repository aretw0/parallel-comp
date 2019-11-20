/*  EX 3:
    Existem muitas formas de se obter o valor aproximado de π através de métodos numéricos.
    Consideramos que π é um número irracional e transcendente, de forma que os métodos de cálculo sempre
    envolvem aproximações, aproximações sucessivas e/ou séries infinitas de somas, multiplicações e divisões.
    Abaixo segue um algoritmo utilizando um método estatístico para o calculo de π,
    altere o mesmo para que seja executado usando OpenMP, ou implemente um método da sua preferencia.
    Mais informações em http://pt.wikipedia.org/wiki/Pi#M.C3.A9todos_de_c.C3.A1lculo
    
    #include <stdio.h>
    #include <stdlib.h
    #include <limits.h>
    #include <time.h>
    int main () {
        srand((unsignedint)time((time_t *)NULL));
        int in = 0, out = 0; doubled, x, y, pi; longlongcont = 10516267;
        while (cont-->0) {
            x = (double) rand()/ (double)INT_MAX;
            y = (double) rand()/ (double)INT_MAX;
            d = x*x + y*y;
            (d<=1.0) ? in++ : out++;
        }
        pi = 4.0 * (float) in / (float) (in + out);
        printf("pi (aprox.) = %2.13f\n", pi)
    } 
*/