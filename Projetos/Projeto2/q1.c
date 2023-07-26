#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define STRING_SIZE 10
int T;
char senha[11];
char descoberto[11];


void *findChar(void *tid){
    int id = *((int *)tid);
    for(int i=id;i<STRING_SIZE;i = i + T){
        for(int j=0;j<127;j++){
            if(senha[i] == j){
                descoberto[i] = j;
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
    pthread_t threads[T];
    
    int *taskids[T];
    for(int i=0;i<T;i++){
        printf("Criando thread de id %d no main \n", i);
        taskids[i] = (int *)malloc(sizeof(int));
        *taskids[i] = i;
        pthread_create(&threads[i], NULL, findChar, (void *)taskids[i]);
    }

    for(int i=0;i<T;i++){
        int *res;
        pthread_join(threads[i], NULL);
    }

    printf("Senha descoberta, hehe: %s\n", descoberto);

    return 0;
}
