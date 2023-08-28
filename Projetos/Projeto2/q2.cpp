#include<iostream>
#include<pthread.h>
#define NUM_THREADS 7

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

~Graph() {
    for (int i = 0; i<n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void setEdge(int i, int j){
    if(matrix[i][j] == 0) numEdge++;
    matrix[i][j] = 1;
}

};

Graph grafo(NUM_THREADS);

bool DFS(int tid, int v, bool *mark, bool **mark_vertex){
    printf("Thread %d Vértice %d\n", tid, v);

    if(mark[v]) return true;
    mark[v] = true;

    for(int i = 0; i<grafo.n; i++){
        if((mark_vertex[v][i] == false) && (grafo.matrix[v][i])){
            mark_vertex[v][i] = true;
            return DFS(tid,i,mark,mark_vertex);
        }
    }
    return false;
}

void *FindDeadlock(void* threadid){
    int tid = *((int*) threadid);
    printf("Thread %d Vértice %d\n", tid, tid);

    int size = grafo.n;
    bool mark[size];
    bool **mark_vertex;
    mark_vertex = new bool*[size];
    for (int i = 0; i < size; i++) {
        mark_vertex[i] = new bool[size];
    }

    mark[tid] = true;

    for(int i = 0; i<size; i++){
        bool deadlock;
        if((mark_vertex[tid][i] == false) && (grafo.matrix[tid][i])){
            mark_vertex[tid][i] = true;
            deadlock = DFS(tid,i,mark,mark_vertex);
        }
        if (deadlock){
            printf("Deadlock encontrado.\n");
            exit(0);
        }
    }
    
}

int main(){
grafo.setEdge(0, 4);
grafo.setEdge(1, 6);
grafo.setEdge(2, 1);
grafo.setEdge(3, 0);
grafo.setEdge(3, 0);
grafo.setEdge(5, 2);
grafo.setEdge(6, 5);

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

}
