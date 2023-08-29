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


int tamanho; // tamanho estático



void f(int i) { // função f(pode ser qualquer uma)
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
} paramDinamico; // tipo do recurso compartilhado

typedef struct {
    int inicio;
    int fim;
    int passo;
    int chunk_size;
    int N;
} paramPai; // tipo do parametro para o processo pai

paramDinamico *param;
pthread_mutex_t lock;
pthread_cond_t notTaken;
pthread_cond_t taken;


void *pai_dinamico(void *pai) {
    pthread_mutex_lock(&lock); // inicialização(buscando valores para que o loop sempre dê certo)
    paramPai *Pai = (paramPai *) pai;

    int restante = floor(((Pai -> fim) - (Pai -> inicio)) / (Pai ->passo));
    double rest_cmp =  ((Pai ->fim) - (Pai ->inicio)) / (double) (Pai -> passo);
    if(rest_cmp > restante) restante++;
    param -> inicio = Pai -> inicio;
    param -> passo = Pai -> passo;
    param -> isTaken = 1;
    param -> fim = -1;
    pthread_mutex_unlock(&lock);
    
    while(restante >= (Pai -> chunk_size)) { // se o nº de iterações for maior que o chunk_size, pode-se atualizar o recurso com-
    // partilhado com iterações de tamanho chunk_size
        pthread_mutex_lock(&lock); // lock no mutex(para alterar)
        while(param -> isTaken == 0) { // se a última iteração não for escolhida por nenhuma thread filha, wait.
            pthread_cond_wait(&taken, &lock); 
        }
        if(param -> fim == -1) { // inicialização(indentificado com fim = -1)
            param -> fim = (param -> inicio) + (Pai -> chunk_size - 1) * (param -> passo);
            param -> isTaken = 0;
            restante -= (Pai -> chunk_size);
            pthread_cond_broadcast(&notTaken); // desbloqueia todos aqueles que estavam esperando iterações
            pthread_mutex_unlock(&lock);
        }
        else { // define os valores de inicio e fim com base nos dados que estavam anteriormente no recurso compartilhado
            param -> inicio = (param -> inicio) + (Pai -> chunk_size) * (param -> passo);
            param -> fim = param -> inicio + (Pai -> chunk_size - 1) * (param -> passo);
            param -> isTaken = 0;
            restante -= (Pai -> chunk_size);
            pthread_cond_broadcast(&notTaken);
            pthread_mutex_unlock(&lock);
        }

    }

    
        pthread_mutex_lock(&lock); // esse caso trabalha quanto restante(iterações) < num_chunks, distribuindo um valor menor de
        // iterações
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
        final = start - 1; // feito para que, por segurança, não execute o for indevidamente antes de iniciar as variaveis
        pthread_mutex_lock(&lock);
        if(param -> isTaken == 1) { // dorme se não houver iteração nova disponível
            pthread_cond_wait(&notTaken, &lock);
        }
        
        start = param -> inicio;
        passo = param -> passo;
        final = param -> fim;
        done = param -> done;
        param -> isTaken = 1;
        pthread_cond_broadcast(&taken); // acorda o processo pai ao pegar a iteração
        pthread_mutex_unlock(&lock);

        if(start <= final)
            printf("Thread filho recebe iterações %d-%d\n", start, final); // "debug"

        for(int i = start; i <= final; i += passo) {
            param -> f(i);
        }

        if(done == 1) { // se não houver iterações disponiveis, encerra a thread
            
            pthread_exit(NULL);
        } 



    }

        

}

int resto; // representa o ceil(iterações / n_threads)

void *pai_guided(void *pai) {
    paramPai *Pai = (paramPai *) pai;

    int restante = floor(((Pai -> fim) - (Pai -> inicio)) / (Pai -> passo));
    double rest_cmp =  (Pai -> fim - Pai -> inicio) / (double) Pai -> passo; // mais uma vez, equivalente ao ceil já que não está
    if(rest_cmp > restante) restante++;                                      // funcionando nas nossas maquinas

    resto = floor(restante / (Pai -> N));
    double resto_cmp = restante / (double) (Pai -> N);
    if(resto_cmp > resto) resto++;

    pthread_mutex_lock(&lock); // inicialização
    param -> fim = -1;
    param -> inicio = Pai -> inicio;
    param -> isTaken = 1;
    param -> passo = Pai -> passo;
    pthread_mutex_unlock(&lock);

    while(restante >= Pai -> chunk_size) { // casos em que iterações = ceil(restantes/ nº threads) ou chunk_size
        pthread_mutex_lock(&lock);
        while(param -> isTaken == 0) { // trava se nenhuma thread filha pegar a iteração
            pthread_cond_wait(&taken, &lock);
        }
        int n_chunk = (resto >= (Pai -> chunk_size) ? resto : Pai -> chunk_size); // escolhe o maior: ceil ou chunk_size.
        if(param -> fim == -1) { // inicialização pro loop dar certo
            param -> inicio = Pai -> inicio;
            param -> fim = param -> inicio + (n_chunk - 1) * (param -> passo);
            param -> isTaken = 0;

            restante -= n_chunk;
            resto = floor(restante / (Pai -> N));
            double resto_cmp = restante / (double) (Pai -> N);
            if(resto_cmp > resto) resto++;

            n_chunk = (resto > (Pai -> chunk_size) ? resto : Pai -> chunk_size);
            
            pthread_cond_broadcast(&notTaken); // acordando as threads filhas
            pthread_mutex_unlock(&lock);
        }
        else { // caso geral
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
    pthread_mutex_lock(&lock); // esse caso ocorre quando, inevitavelmente,  0 < iterações restantes < chunk_size
    // caso restante = 0, não faz diferença
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
        double rest_cmp =  (final - inicio) / (double) passo; // essas 3 linhas representam um ceil(final - inicio/ passo).
        if(rest_cmp > restante) restante++; //                   porque não estava funcionando aqui.

        pair **p = (pair **) malloc(N*sizeof(pair *)); // será uma vetor de vetores, cada um para uma thread.

        tamanho = 0;

        while(restante >= N * chunk_size) { // isso representa a parte em que é possivel passar o mesmo chunk_size para todas as
        // threads, ou seja, restante(numero de iterações) >= N * chunk_size. Aloca em round_robin nos vetores.
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
        
        if(restante != 0) { // Caso o numero de iterações seja menor que N * chunk_size, não será possivel distribuir igualmente
        // o memso numero de iterações = chunk_size para todas as threads.
            if(restante % N == 0) { // Caso mais simples: distribuir restante / N para todas as threads, se N for dividor de restante
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
            else { // Caso haja um resto q( 0<q<N), uma unidade será distribuída para q-1 threads.
            // exemplo restante = 10. 10 % 4 = 2. Assim, as duas primeiras threads terão uma iteração a mais.
            // seguindo o exemplo: T0(3 it), T1(3 it), T2(2 it), T3(2 it).
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
                        if(i == 0) { // o inc considera o deslocamento do final de cada iteração por conta do resto.
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
        param = (paramDinamico *) malloc(sizeof(paramDinamico)); // variavel global(recurso compartilhado)
        param -> isTaken = 1; // impede que, antes de inicializar os valores, as threads filhas peguem valores errados
        param -> f = f;
        pthread_mutex_init(&lock, NULL); // inicializando mutex, condições...
        pthread_cond_init(&taken, NULL);
        pthread_cond_init(&notTaken, NULL);

        paramPai *papai = (paramPai *) malloc(sizeof(paramPai)); // inicializando parametro do processo pai
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
        param = (paramDinamico *) malloc(sizeof(paramDinamico)); // recurso compartilhado e inicialização análoga ao caso 1
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
    
    omp_for(0, 2, 20, 0, 3, f); //  passando os parâmetros para o omp for

    pthread_exit(NULL);
    

}
