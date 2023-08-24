#include<iostream>
#include<pthread.h>
#define NUM_THREADS 5

using namespace std;

class Graph{
    public:
    int **matrix;
    int numEdge;
    int *mark;
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

        mark = new int[n];
        for(int i = 0; i<n; i++){
            mark[i] = 0;
        }
        numEdge = 0;
    }

    ~Graph() {
        for (int i = 0; i<n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        delete[] mark;
    }

    int first(int v){
        for(int i = 0; i<n; i++){
            if(matrix[v][i]) return i;
        }
        return n;
    }

    int next(int v, int w){
        for(int i = w+1; i<n; i++){
            if(matrix[v][i]) return i;
        }
        return n;
    }

    void setEdge(int i, int j, int wt){
        if(matrix[i][j] == 0) numEdge++;
        matrix[i][j] = wt;
    } 

    void delEdge(int i, int j){
        if(matrix[i][j]) numEdge--;
        matrix[i][j] = 0;
    }

    void setMark(int i, int val){
        mark[i] = val;
    }

    int getMark(int i){
        return mark[i];
    }

};

Graph grafo(10);

void *DFS(void* threadid){
    int v = *((int*) threadid);
    printf("Vértice %d\n", v);
    
    grafo.setMark(v, 1);
    
    int *w;
    w = (int*) malloc(sizeof(int));
    *w = grafo.first(v);
    
    while(*w<grafo.n){
        if(grafo.getMark(*w) == 0) DFS((void*)w);
        *w = grafo.next(v, *w);
    }
    pthread_exit(NULL);
}


int main(){
    grafo.setEdge(0, 4, 1);
    grafo.setEdge(0, 1, 1);
    grafo.setEdge(1, 3, 1); 
    grafo.setEdge(2, 4, 1);
    grafo.setEdge(3, 2, 1);
    grafo.setEdge(4, 1, 1);
    grafo.setEdge(4, 9, 1);
    grafo.setEdge(3, 5, 1);
    grafo.setEdge(5, 8, 1);
    grafo.setEdge(8, 7, 1);
    grafo.setEdge(9, 8, 0);
    
    pthread_t threads[NUM_THREADS];
    int *taskids[NUM_THREADS];
    int rc;
    for(int i=0;i<NUM_THREADS;i++){
        taskids[i] = (int*) malloc(sizeof(int));
        *taskids[i] = i;
        rc = pthread_create(&threads[i],NULL,DFS,(void*)taskids[i]);
        if(rc){
            printf("Erro! Código de retorno %d", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
    return 0;
}
