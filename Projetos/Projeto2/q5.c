#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
typedef struct{
    int x, y;
} Point;

typedef struct {
    Point *p;
    int size;

} Set;



int mX = 10;
int mY = 10;
int matrix[10][10]; 

int setCounter = 0;

Set *beginSet(){
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

int findIndexSet(int x, int y, Set *sets){
    for(int i=0;i<setCounter;i++){
        for(int j=0;j<sets[i].size;j++){
            if(sets[i].p[j].x == x && sets[i].p[j].y == y){
                return i;
            }  
        }
    }
    return -1;
}

void JoinSets(int index1, int index2, Set *sets){
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









int N;
pthread_t *threads;
Set *sets;
void printState(){
    for(int i=0;i<setCounter;i++){
        printf("Set %d: ", i);
        for(int j=0;j<sets[i].size;j++){
            printf("(%d,%d), ", sets[i].p[j].x, sets[i].p[j].y);
        }
        printf("\n");
        
    }
    printf("\n");
}

void *landscapeVerify(void *tid){
    int id = *((int *)(tid));
    for(int i=id*ceil((double)mY/N);i<(id*ceil((double)mY/N) + ceil((double)mY/N));i++){
        for(int j=0;j<mX;j++){
            if(matrix[i][j]==1){
                if((i-1)>=id*ceil((double)mY/N) && (j-1)>=0 && matrix[i-1][j-1] == 1){ //top-left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j-1,i-1,sets), sets);
                    printState();
                }
                if((i-1)>=id*ceil((double)mY/N) && matrix[i-1][j] == 1){ // top
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j, i-1, sets), sets);
                    printState();
                }
                if((i-1)>=id*ceil((double)mY/N) && (j+1)<mX && matrix[i-1][j+1] == 1){//top-right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i-1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i-1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j+1, i-1, sets), sets);
                    printState();
                }
                if((j-1)>=0 && matrix[i][j-1] == 1){ //left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j-1,i,sets),sets);
                    printState();
                }
                if((j+1)<mX && matrix[i][j+1] == 1){ //right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i,sets));
                    JoinSets(findIndexSet(j,i,sets), findIndexSet(j+1, i, sets), sets);
                    printState();
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && (j-1)>=0 && matrix[i+1][j-1] == 1){ // bottom-left
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j-1, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j-1,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j-1, i+1, sets), sets);
                    printState();
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && matrix[i+1][j] == 1){ // bottom
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j, i+1, sets), sets);
                    printState();
                }
                if((i+1)<(id*ceil((double)mY/N) + ceil((double)mY/N)) && (j+1)<mX && matrix[i+1][j+1] == 1){ //bottom-right
                    printf("id: %d\n", id);
                    printf("joining (%d, %d) e (%d,%d)\n", j, i, j+1, i+1);
                    printf("index1 = %d; index2 = %d\n", findIndexSet(j,i,sets), findIndexSet(j+1,i+1,sets));
                    JoinSets(findIndexSet(j, i, sets), findIndexSet(j+1, i+1, sets), sets);
                    printState();
                }
                
            }
            
        }
    }
    if(id!=(N-1)){
        pthread_join(threads[id+1], NULL);
        int i = id*ceil((double)mY/N) + ceil((double)mY/N);
        for(int j=0;j<mX;j++){
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
    srand(time(0));
    for(int i=0;i<mY;i++){
        for(int j=0;j<mX;j++){
            
            matrix[i][j] = rand()%2;
            printf("%d", matrix[i][j]);
        }
        printf("\n");
        
    }

    
    sets = beginSet();
    
    printState();
    printf("digite o número de Threads:\n");
    scanf("%d", &N);
    threads = (pthread_t *)malloc(sizeof(pthread_t)*N);

    int *taskids[N];
    for(int i=0;i<N;i++){
        printf("Criando thread de id %d no main \n", i);
        taskids[i] = (int *)malloc(sizeof(int));
        *taskids[i] = i;
        pthread_create(&threads[i], NULL, landscapeVerify, (void *)taskids[i]);
    }

    pthread_join(threads[0], NULL);
    int lands = 0;
    for(int i=0;i<setCounter;i++){
        if(sets[i].size!=0){
            lands++;
        }
    }
    printState();
    printf("A quantidade de ilhas é: %d\n", lands);
    return 0;
}