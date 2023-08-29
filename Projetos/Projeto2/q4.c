#define _XOPEN_SOURCE 600
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

pthread_barrier_t barrier;

typedef struct{
    int x, y;
} Point;

typedef struct {
    Point *p;
    int size;

} Set;
//ATTENTION: if the function ceil isn't recognized by the compiler, insert "-lm" after the source file in tasks.json
//+----------Please, insert your input matrix here-----------+

int mX = 5;
int mY = 5;
int matrix[5][5] = {{0,0,1,0,0},
                    {1,0,1,0,0},
                    {0,0,1,0,0},
                    {1,0,1,0,1},
                    {1,0,0,0,0}};
    





                          

//+----------Please, insert your input matrix here-----------+

int setCounter = 0; //total number of sets
pthread_barrier_t barrier;

Set *beginSet(){ // will create a set for each point in matrix
    Set *init;
    
    init = (Set *)malloc(sizeof(Set)*0);
    for(int i=0;i<mY;i++){
        for(int k=0;k<mX;k++){
            if(matrix[i][k]==1){
                setCounter++;
                Point temp;
                temp.x = k;
                temp.y = i;
                
                init = (Set *)realloc(init, sizeof(Set)*setCounter);
                init[setCounter-1].p = (Point *)malloc(sizeof(Point));
                
                init[setCounter-1].size = 1;
                init[setCounter-1].p[0] = temp;
            }
        }
    }
    
    return init;
}

int findIndexSet(int x, int y, Set *sets){ // find the set of a specific point of the matrix
    for(int i=0;i<setCounter;i++){
        for(int j=0;j<sets[i].size;j++){
            if(sets[i].p[j].x == x && sets[i].p[j].y == y){
                return i;
            }  
        }
    }
    return -1;
}

void JoinSets(int index1, int index2, Set *sets){ // will join sets
    if(index1!=index2){


        if(sets[index1].size>sets[index2].size){
            Point *temp = sets[index2].p;
            for(int i=0;i<sets[index2].size;i++){
                sets[index1].size++;
                sets[index1].p = (Point *)realloc(sets[index1].p, sizeof(Point)*sets[index1].size);
                sets[index1].p[sets[index1].size-1] = temp[i];
            }
            sets[index2].p = NULL;
            sets[index2].size = 0;
            
        }
        else{
            Point *temp = sets[index1].p;
            for(int i=0;i<sets[index1].size;i++){
                sets[index2].size++;
                sets[index2].p = (Point *)realloc(sets[index2].p, sizeof(Point)*sets[index2].size);
                sets[index2].p[sets[index2].size-1] = temp[i];
            }
            sets[index1].p = NULL;
            sets[index1].size = 0;
            
        }
    }
}









int N; // number of threads
pthread_t *threads; //vector of threads
Set *sets; //vector of sets


void *landscapeVerify(void *tid){
    int id = *((int *)(tid));
    for(int i=id*ceil((double)mY/N);i<(id*ceil((double)mY/N) + ceil((double)mY/N));i++){ //joining point with its surroundings
        for(int j=0;j<mX;j++){
            if(matrix[i][j]==1){
                if((i-1)>=id*ceil((double)mY/N) && (j-1)>=0 && matrix[i-1][j-1] == 1){ //top-left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets), sets);
                    
                }
                if((i-1)>=id*ceil((double)mY/N) && matrix[i-1][j] == 1){ // top
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j, i-1, sets), sets);
                    
                }
                if((i-1)>=id*ceil((double)mY/N) && (j+1)<mX && matrix[i-1][j+1] == 1){//top-right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j+1, i-1, sets), sets);
                    
                }
                if((j-1)>=0 && matrix[i][j-1] == 1){ //left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j-1,i,sets),sets);
                    
                }
                if((j+1)<mX && matrix[i][j+1] == 1){ //right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j+1, i, sets), sets);
                    
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && (j-1)>=0 && matrix[i+1][j-1] == 1){ // bottom-left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j-1, i+1, sets), sets);
                    
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && matrix[i+1][j] == 1){ // bottom
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j, i+1, sets), sets);
                    
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && (j+1)<mX && matrix[i+1][j+1] == 1){ //bottom-right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j+1, i+1, sets), sets);
                    
                }
                
            }
            
        }
    }
    pthread_barrier_wait(&barrier); // waits until all threads have uploaded all its lands
    if(id!=(N-1)){
        
        int i = id*ceil((double)mY/N) + ceil((double)mY/N);
        for(int j=0;j<mX;j++){ // joining points of different threads (bottom-up)
            if(matrix[i][j] == 1){
                if((i-1)>=0 && (j-1)>=0 && matrix[i-1][j-1] == 1){ //top-left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets), sets);
                }
                if((i-1)>=0 && matrix[i-1][j] == 1){ // top
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j, i-1, sets), sets);
                }
                if((i-1)>=0 && (j+1)<mX && matrix[i-1][j+1] == 1){//top-right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j+1, i-1, sets), sets);
                }
            }
        }
    }
    pthread_exit(NULL);
}




int main()
{
    
    sets = beginSet();
    printf("PLEASE, REMEMBER TO INSERT YOUR MATRIX IN THE CODE ON INPUT AREA ABOVE\n");
   
    printf("Type number of threads:\n");
    scanf("%d", &N);
    pthread_barrier_init(&barrier, NULL, N);
    threads = (pthread_t *)malloc(sizeof(pthread_t)*N);

    int *taskids[N];
    for(int i=0;i<N;i++){
        printf("Criando thread de id %d no main \n", i);
        taskids[i] = (int *)malloc(sizeof(int));
        *taskids[i] = i;
        int rc = pthread_create(&threads[i], NULL, landscapeVerify, (void *)taskids[i]);
        if(rc){
            printf("ERROR creating thread %d\n", i);
            exit(-1);
        }
    }

    
    for(int i=0;i<N;i++){
        pthread_join(threads[i],NULL);
    }
    int lands = 0;
    for(int i=0;i<setCounter;i++){
        if(sets[i].size!=0){
            lands++;
        }
    }
    printf("The number of islands is: %d\n", lands);
    free(sets);
    free(threads);
    return 0;
}
