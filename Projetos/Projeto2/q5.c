#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define true 1 
#define false 0

int NUM_THREADS;
int N;
int* primeNumbers;
int* mutex;

void printArr(){    //Printa o indice das posicoes do array primeNumbers que esta true
    
    printf("Prime numbers under %d : ", N);
    
    for(int i=0; i<N; i++){
        if(primeNumbers[i] > 0)
            printf("%d ", i);
    }
    printf("\n");
}

void* crivo(void *threadID){
    int id = *((int *)threadID);
    for(int i= id+2; i<N; i++){                             //comeca do id+2 para pular 0 e 1 que nao sao primos
            if(mutex[i]==false && primeNumbers[i]){         //Só continua no indice se o mutex[i] nao tenha sido verificado e se primeNumbers[i]==true
                mutex[i] = true;                            //mutex == true diz que o numero ja foi verificado
                //printf("Number %d at thread %d\n", i, id);
                for(int j=i+1; j<N; j++){                   //Como i é um primo, use-o para encontrar multiplos nos indices seguintes
                    if( primeNumbers[j] && (j % i == 0))    // Se primeNumbers[j]==true 
                        primeNumbers[j] -= 1;               // primeNumbers[i] = false porque não é primo
                }                                           //Usei -1 para verificar se esse valor só era modificado uma vez
            }
    }
}

void makeThreads(){                     //Criação das Threads
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];

    int rc;   int t;   
  
    for(t=0; t<NUM_THREADS; t++){      
        taskids[t] = (int *) malloc(sizeof(int)); 
        *taskids[t] = t;
        rc = pthread_create(&threads[t], NULL, crivo, (void *) taskids[t]);     
        if (rc){                        //Tratamento de erro    
            printf("ERRO; código de retorno é %d\n", rc);         
            exit(-1); 
        }
    }   
    
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);
}

int main(){
    printf("Insert a natural number: ");
    scanf("%d", &N);
    primeNumbers = (int*) malloc(N * sizeof(int));
    mutex = (int*) malloc(N * sizeof(int));
    if(N<=1){
        primeNumbers[0] = false;
        primeNumbers[1] = false;
        mutex[0] = false;
        mutex[1] = false;
    }
    for(int i=2; i<N; i++){
        primeNumbers[i] = true;             //primeNumbers[i]==true -> O indice eh um possivel primo
        mutex[i] = false;                   //mutex[i]==false -> o array primeNumbers[i] ainda não foi verificado
    }
    printf("Number of threads: ");
    scanf("%d", &NUM_THREADS);
        
    makeThreads();
        
    printArr();
    pthread_exit(NULL);
    free(primeNumbers);
    free(mutex);
}
