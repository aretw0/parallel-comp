/*  EX1:
    Generalize o exemplo a seguir para um número arbitrário de threads.
    Considere que o numero de colunas é maior que o numero de threads em execução.
    
    #pragma omp parallel private(i, myid) shared(a,n)
    myid = omp_get_thread_num();
    for(i = 0; i < n; i++) {
        a[i][myid] = 1.0;
    }
*/