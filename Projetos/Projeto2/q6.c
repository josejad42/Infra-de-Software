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

// DINAMICO:
typedef struct {
    int inicio;
    int fim;
    int passo;
    void (*f)(int);
    int isTaken;
    int done;
} paramDinamico;

typedef struct {
    int inicio;
    int fim;
    int passo;
    int chunk_size;
    int N;
} paramPai;

paramDinamico *param;
pthread_mutex_t lock;
pthread_cond_t notTaken;
pthread_cond_t taken;


void *pai_dinamico(void *pai) {
    pthread_mutex_lock(&lock);
    paramPai *Pai = (paramPai *) pai;

    int restante = floor(((Pai -> fim) - (Pai -> inicio)) / (Pai ->passo));
    double rest_cmp =  ((Pai ->fim) - (Pai ->inicio)) / (double) (Pai -> passo);
    if(rest_cmp > restante) restante++;
    param -> inicio = Pai -> inicio;
    param -> passo = Pai -> passo;
    param -> isTaken = 1;
    param -> fim = -1;
    pthread_mutex_unlock(&lock);
    
    while(restante >= (Pai -> chunk_size)) {
        pthread_mutex_lock(&lock);
        while(param -> isTaken == 0) {
            pthread_cond_wait(&taken, &lock);
        }
        if(param -> fim == -1) {
            param -> fim = (param -> inicio) + (Pai -> chunk_size - 1) * (param -> passo);
            param -> isTaken = 0;
            restante -= (Pai -> chunk_size);
            pthread_cond_broadcast(&notTaken);
            pthread_mutex_unlock(&lock);
        }
        else {
            param -> inicio = (param -> inicio) + (Pai -> chunk_size) * (param -> passo);
            param -> fim = param -> inicio + (Pai -> chunk_size - 1) * (param -> passo);
            param -> isTaken = 0;
            restante -= (Pai -> chunk_size);
            pthread_cond_broadcast(&notTaken);
            pthread_mutex_unlock(&lock);
        }

    }

    
        pthread_mutex_lock(&lock);
        while(param -> isTaken == 0) {
            pthread_cond_wait(&taken, &lock);
        }
        param -> inicio = param -> fim + (Pai -> passo);
        param -> fim = param -> inicio + (Pai -> passo) * (restante - 1);
        param -> isTaken = 0;
        param -> done = 1;
        
        
        pthread_cond_broadcast(&notTaken);
        pthread_mutex_unlock(&lock);

    
        

    pthread_exit(NULL);
    
    

}

void *filho_dinamico() {
    int start, passo, final, done;
    while(1) {
        final = start - 1;
        pthread_mutex_lock(&lock);
        if(param -> isTaken == 1) {
            pthread_cond_wait(&notTaken, &lock);
        }
        
        start = param -> inicio;
        passo = param -> passo;
        final = param -> fim;
        done = param -> done;
        param -> isTaken = 1;
        pthread_cond_broadcast(&taken);
        pthread_mutex_unlock(&lock);

        if(start <= final)
            printf("Thread filho recebe iterações %d-%d\n", start, final);

        for(int i = start; i <= final; i += passo) {
            param -> f(i);
        }

        if(done == 1) {
            
            pthread_exit(NULL);
        } 



    }

        

}

int resto;

void *pai_guided(void *pai) {
    paramPai *Pai = (paramPai *) pai;

    int restante = floor(((Pai -> fim) - (Pai -> inicio)) / (Pai -> passo));
    double rest_cmp =  (Pai -> fim - Pai -> inicio) / (double) Pai -> passo;
    if(rest_cmp > restante) restante++;

    resto = floor(restante / (Pai -> N));
    double resto_cmp = restante / (double) (Pai -> N);
    if(resto_cmp > resto) resto++;

    pthread_mutex_lock(&lock);
    param -> fim = -1;
    param -> inicio = Pai -> inicio;
    param -> isTaken = 1;
    param -> passo = Pai -> passo;
    pthread_mutex_unlock(&lock);

    while(restante >= Pai -> chunk_size) {
        pthread_mutex_lock(&lock);
        while(param -> isTaken == 0) {
            pthread_cond_wait(&taken, &lock);
        }
        int n_chunk = (resto >= (Pai -> chunk_size) ? resto : Pai -> chunk_size);
        if(param -> fim == -1) {
            param -> inicio = Pai -> inicio;
            param -> fim = param -> inicio + (n_chunk - 1) * (param -> passo);
            param -> isTaken = 0;

            restante -= n_chunk;
            resto = floor(restante / (Pai -> N));
            double resto_cmp = restante / (double) (Pai -> N);
            if(resto_cmp > resto) resto++;

            n_chunk = (resto > (Pai -> chunk_size) ? resto : Pai -> chunk_size);
            
            pthread_cond_broadcast(&notTaken);
            pthread_mutex_unlock(&lock);
        }
        else {
            param -> inicio = param -> fim + param -> passo;
            param -> fim = param -> inicio + (n_chunk - 1) * (param -> passo);
            param -> isTaken = 0;

            restante -= n_chunk;
            resto = floor(restante / (Pai -> N));
            double resto_cmp = restante / (double) (Pai -> N);
            if(resto_cmp > resto) resto++;

            n_chunk = (resto > (Pai -> chunk_size) ? resto : Pai -> chunk_size);
            
            pthread_cond_broadcast(&notTaken);
            pthread_mutex_unlock(&lock);

        }



    }
    pthread_mutex_lock(&lock);
    while(param -> isTaken == 0) {
        pthread_cond_wait(&taken, &lock);
    }
    param -> inicio = param -> fim + (param -> passo);
    param -> fim = param -> inicio + (param -> passo) * (restante - 1);
    param -> isTaken = 0;
    param -> done = 1;
        
        
    pthread_cond_broadcast(&notTaken);
    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);


    


}




void omp_for(int inicio, int passo, int final, int schedule, int chunk_size, void (*f) (int)) {
    int N = 4; // numero de threads;
    pthread_t threads[N];
    pthread_t pai;

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
    else if(schedule == 1) { // DYNAMIC:
        param = (paramDinamico *) malloc(sizeof(paramDinamico));
        param -> isTaken = 1;
        param -> f = f;
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&taken, NULL);
        pthread_cond_init(&notTaken, NULL);

        paramPai *papai = (paramPai *) malloc(sizeof(paramPai));
        papai ->chunk_size = chunk_size;
        papai -> inicio = inicio;
        papai -> fim = final;
        papai -> N = N;
        papai -> passo = passo;

        pthread_create(&pai, NULL, pai_dinamico, (void *) papai);

        for(int i = 0; i < N; i++) {
            pthread_create(&threads[i], NULL, filho_dinamico, NULL);
        }

        for(int i = 0; i < N; i++) {
            pthread_join(threads[i], NULL);
        }
    }
    else if(schedule == 2) { // guided:
        param = (paramDinamico *) malloc(sizeof(paramDinamico));
        param -> isTaken = 1;
        param -> f = f;
        pthread_mutex_init(&lock, NULL);
        pthread_cond_init(&taken, NULL);
        pthread_cond_init(&notTaken, NULL);

        paramPai *papai = (paramPai *) malloc(sizeof(paramPai));
        papai ->chunk_size = chunk_size;
        papai -> inicio = inicio;
        papai -> fim = final;
        papai -> N = N;
        papai -> passo = passo;

        pthread_create(&pai, NULL, pai_guided, (void *) papai);

        for(int i = 0; i < N; i++) {
            pthread_create(&threads[i], NULL, filho_dinamico, NULL);
        }

        for(int i = 0; i < N; i++) {
            pthread_join(threads[i], NULL);
        }
    }



}



int main() {
    
    omp_for(0, 2, 20, 2, 3, f);
    

}
