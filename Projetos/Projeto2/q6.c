#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

// cada thread terá o mesmo numero de pares, mas o seu range muda.
typedef struct {
    int inicio; // inicio
    int fim; // fim
    int passo;
    void (*f)(int);
} pair;


int tamanho;



void f(int i) {
    printf("numero: %d\n", i);
}

void *executar_estatico(void * param) {
   pair *p = ((pair *) param);

   for(int i = 0; i < tamanho; i++) {
        for(int j = p[i].inicio; j <= p[i].fim; j += p[i].passo) {
            p[i].f(j);
        }
   }

}

void omp_for(int inicio, int passo, int final, int schedule, int chunk_size, void (*f) (int)) {
    int N = 4; // numero de threads;
    pthread_t threads[N];

    if(schedule == 0) { // case: static

        int restante = floor((final - inicio) / passo);
        double rest_cmp =  (final - inicio) / (double) passo;
        if(rest_cmp > restante) restante++;

        pair **p = (pair **) malloc(N*sizeof(pair *));

        tamanho = 0;

        while(restante >= N * chunk_size) {
            tamanho++;
            for(int i = 0; i < N; i++) {
                p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                p[i][tamanho-1].inicio = (inicio + i*chunk_size *passo) + (tamanho-1) * N *chunk_size * passo;
                p[i][tamanho-1].fim = p[i][tamanho-1].inicio + ((chunk_size - 1) * passo);
                p[i][tamanho-1].passo = passo;
                p[i][tamanho-1].f = f;
            }
            restante -= N*chunk_size;
        }
        
        if(restante != 0) {
            if(restante % N == 0) {
                int c_new = restante / N;
                tamanho++;
                for(int i = 0; i < N; i++) {
                    if(i == 0) {
                        p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                        p[i][tamanho-1].inicio = (inicio + i*chunk_size *passo) + (tamanho-1) * N *chunk_size * passo;
                        p[i][tamanho-1].fim = p[i][tamanho-1].inicio + ((c_new - 1) * passo);
                        p[i][tamanho-1].passo = passo;
                        p[i][tamanho-1].f = f;

                    }
                    else {
                        p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                        p[i][tamanho-1].inicio = p[i-1][tamanho-1].inicio + (c_new * passo);
                        p[i][tamanho-1].fim = p[i][tamanho-1].inicio + ((c_new - 1) * passo);
                        p[i][tamanho-1].passo = passo;
                        p[i][tamanho-1].f = f;
                    }
                }
            }
            else {
                int alterados = restante % N;
                int c_new = floor(restante / N);
                tamanho++;
                int inc = 0;

                for(int i = 0; i < N; i++) {
                    if(alterados > 0) {
                        if(i == 0) {
                            p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                            p[i][tamanho-1].inicio = (inicio + i*chunk_size *passo) + (tamanho-1) * N *chunk_size * passo;
                            p[i][tamanho-1].fim = p[i][tamanho-1].inicio + (c_new * passo);
                            p[i][tamanho-1].passo = passo;
                            p[i][tamanho-1].f = f;
                            alterados--;
                            if(alterados == 0) inc = 1;
                            
                        }
                        else {
                            p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                            p[i][tamanho-1].inicio = p[i-1][tamanho-1].inicio + ((c_new + 1) * passo);
                            p[i][tamanho-1].fim = p[i][tamanho-1].inicio + (c_new * passo);
                            p[i][tamanho-1].passo = passo;
                            p[i][tamanho-1].f = f;
                            alterados--;
                            if(alterados == 0) inc = 1;
                        }
                    }

                    else {
                        if(i == 0) {
                            p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                            p[i][tamanho-1].inicio = (inicio + i*chunk_size *passo) + (tamanho-1) * N *chunk_size * passo;
                            p[i][tamanho-1].fim = p[i][tamanho-1].inicio + ((c_new-1) * passo);
                            p[i][tamanho-1].passo = passo;
                            p[i][tamanho-1].f = f;

                        }
                        else {
                            p[i] = (pair *) realloc(p[i], sizeof(pair) * tamanho);
                            p[i][tamanho-1].inicio = p[i-1][tamanho-1].inicio + ((c_new + inc) * passo);
                            p[i][tamanho-1].fim = p[i][tamanho-1].inicio + ((c_new -1 ) * passo);
                            p[i][tamanho-1].passo = passo;
                            p[i][tamanho-1].f = f;
                            if(inc != 0) inc = 0;
                        }
                    }
                }
            }
        }

        for(int i = 0; i < N; i++) {
            pthread_create(&threads[i], NULL, executar_estatico, (void *) p[i]);
        }

        for(int i = 0; i < N; i++) {
            pthread_join(threads[i], NULL);
        }
    }



}



int main() {
    
    omp_for(0, 3, 20, 0, 2, f);
    

}
