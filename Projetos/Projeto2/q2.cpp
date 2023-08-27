#include<iostream>
#include<pthread.h>
#define NUM_THREADS 5
#define TAM_GRAPH 6

using namespace std;

class Graph{
    public:
    int **matrix;
    int numEdge;
    int n;

    Graph(int nv){
        n = nv;
        matrix = new int*[n];
        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 0;
            }
        }
        numEdge = 0;
    }

    void setEdge(int i, int j){
        if(matrix[i][j] == 0) numEdge++;
        matrix[i][j] = 1;
    } 
    
};

Graph grafo(TAM_GRAPH);

bool DFS(int tid, int v, bool *mark){
    printf("Thread %d Vértice %d\n", tid, v);
    
    mark[v] = true;
    
    for (int i = 0; i<grafo.n; i++){
        if((grafo.matrix[v][i] == 1) && (mark[i] == false)) return DFS(tid,i,mark);
        if((grafo.matrix[v][i] == 1) && (mark[i] == true)) return true;
    }
    return false;
}

void *FindDeadlock(void* threadid){
    int tid = *((int*) threadid);
    printf("Thread %d Vértice %d\n", tid, tid);
    
    int size = grafo.n;
    bool mark[size];
    
    mark[tid] = true;
    
    for(int i = tid; i<size; i++){
        bool deadlock;
        if(mark[i] == false) deadlock = DFS(tid,i,mark);
        if (deadlock == true){
            printf("Deadlock encontrado.\n");
            exit(-1);
        }
    }
}

int main(){
    grafo.setEdge(0, 3);
    grafo.setEdge(1, 5);
    grafo.setEdge(1, 2);
    grafo.setEdge(2, 3);
    grafo.setEdge(4, 1);
    grafo.setEdge(4, 5);
    grafo.setEdge(5, 3);
    
    pthread_t threads[NUM_THREADS];
    int *threadids[NUM_THREADS];
    int rc;
    for(int i=0;i<NUM_THREADS;i++){
        threadids[i] = (int*) malloc(sizeof(int));
        *threadids[i] = i;
        rc = pthread_create(&threads[i],NULL,FindDeadlock,(void*)threadids[i]);
        if(rc){
            printf("Erro! Código de retorno %d", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
