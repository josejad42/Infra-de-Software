#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
#define arraySize 10        //Tamanho fixo do array que é a base de dados

pthread_mutex_t db = PTHREAD_MUTEX_INITIALIZER;             //Controla o acesso ao array
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;          //Controla o acesso a "rc"

int rc = 0;             //nº de processos lendo ou querendo ler
int* array;             //base de dados

int NUM_READERS;
int NUM_WRITERS;

void* reader(void *threadID){
    while(1){   //Loop infinito para as threads leitoras
    int readerID = *((int *)threadID);
    
        printf("Reader %d : wants to read\n", readerID);
        
        pthread_mutex_lock(&mutex);             //Obtem acesso a rc
        rc += 1;                                //Mais uma leitora acessando a região crítica
        if(rc ==1)                              //Se este for o 1º leitor
            pthread_mutex_lock(&db);

        pthread_mutex_unlock(&mutex);           //Libera acesso exclusivo para as threads leitoras
        
        //read_data_base;
        int index = rand() % (arraySize - 1);   //Aleatorizando qual índice do array será acessado
        printf("Reader %d : reading %d at index %d \n", readerID, array[index], index);
        
        pthread_mutex_lock(&mutex);
        rc -= 1;                                //Menos uma leitora acessando a região crítica
        
        if(!rc)                                 //Se este for o último leitor
            pthread_mutex_unlock(&db);

        pthread_mutex_unlock(&mutex);           //libera o acesso para threads escritoras
        
        //use_data_base
        printf("Reader %d : finished\n", readerID);
        
    }   //Loop infinito para as threads leitoras
}

void* writer(void *threadID){
    while(1){   //Loop infinito para as threads escritoras
    int writerId = *((int *)threadID);
        //think_up_data;
        printf("Writer %d : wants to write\n", writerId);
        
        pthread_mutex_lock(&db);                //Obtém acesso exclusivo ao array
        
        //write_data_base();                    //Escreve no array
        int index = rand() % (arraySize - 1);   //Aleatorizando qual índice do array será acessado
        array[index] = writerId;
        printf("Writer %d : writing %d at %d \n", writerId, writerId, index);
        
        pthread_mutex_unlock(&db);              //Libera para outros processos
        printf("Writer %d : finished\n", writerId);
        
   }    //Loop infinito para as threads escritoras
}

void makeThreads(){         //Função para criar as threads leitoras e escritoras
    pthread_t readersT[NUM_READERS];
    int *taskids_R[NUM_READERS];
    
    pthread_t Writers[NUM_WRITERS];
    int *taskids_W[NUM_WRITERS];

    int rc_r, rc_w;   int tR, tW;   
  
    for(tR=0; tR<NUM_READERS; tR++){      //Loop para criar as threads leitoras
        taskids_R[tR] = (int *) malloc(sizeof(int)); 
        *taskids_R[tR] = tR;
        rc_r = pthread_create(&readersT[tR], NULL, reader, (void *) taskids_R[tR]);      
        if (rc_r){         
            printf("ERRO; código de retorno é %d\n", rc_r);         
            exit(-1); 
        }
    }   
    
    for(tW=0; tW<NUM_WRITERS; tW++){    //Loop para criar as threads escritoras
        taskids_W[tW] = (int *) malloc(sizeof(int));
        *taskids_W[tW] = tW;
        rc_w = pthread_create(&Writers[tW], NULL, writer, (void *) taskids_W[tW]);
        if(rc_w){
            printf("ERRO; código de retorno é %d\n", rc_w);         
            exit(-1); 
        }
    }
    
    free(array);
    pthread_exit(NULL);
}

int main(){
    array = (int*) malloc(arraySize * sizeof(int));
    
    for(int i=0; i<arraySize; i++)  //Inicializando o array da base de dados
        array[i] = 0;
        
    printf("Number of Readers: ");
    scanf("%d", &NUM_READERS);
    printf("Number of Writers: ");
    scanf("%d", &NUM_WRITERS);
    
    makeThreads();
    
    return 0;
}
