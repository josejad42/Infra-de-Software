#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define STRING_SIZE 10
int T; // number of threads
char senha[11]; // password input
char descoberto[11]; // password output after algorithm


void *findChar(void *tid){
    int id = *((int *)tid);
    for(int i=id;i<STRING_SIZE;i = i + T){
        for(int j=0;j<127;j++){ // iterate through all ascii values until match
            if(senha[i] == j){
                printf("thread %d descobriu o caractere (%c) que fica no índice %d da string\n",id, j, i);
                descoberto[i] = j; // assign password output with value found
                break;
            }
        }
    }
    pthread_exit(NULL);
}

int main(){
    printf("Digite o número de threads:\n");
    scanf("%d", &T);
    printf("digite sua senha(max 10 caracteres):\n");
    scanf("%s", senha);
    clock_t begin = clock();
    pthread_t threads[T];
    
    int *taskids[T];
    for(int i=0;i<T;i++){
        printf("Criando thread de id %d no main \n", i);
        taskids[i] = (int *)malloc(sizeof(int));
        *taskids[i] = i;
        int rc = pthread_create(&threads[i], NULL, findChar, (void *)taskids[i]);
        if(rc){
            printf("ERRO ao criar thread %d", i);
            exit(-1);
        }
    }

    for(int i=0;i<T;i++){
        int *res;
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();
    double time = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("Senha descoberta, hehe: %s\n", descoberto);
    printf("TEMPO DE EXECUÇÃO: %lf\n", time);

    return 0;
}
