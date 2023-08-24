#include<iostream>
#include<queue>
#include<stack>
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

    void *DFS(void* threadid, void* vertex){
        int tid = *((int*) threadid)
        int v = *((int*) vertex)
        printf("Sou a thread %d saindo do vertice %d\n", tid, v);
        
        setMark(v, 1);
        int w = first(v);
        while(w<n){
            if(getMark(w) == 0) DFS(w);
            w = next(v, w);
        }
    }

};


int main(){
    Graph grafo(5);
    grafo.setEdge(0, 4, 1);
    grafo.setEdge(0, 1, 1);
    grafo.setEdge(1, 3, 1); 
    grafo.setEdge(2, 4, 1);
    grafo.setEdge(3, 2, 1);
    grafo.setEdge(4, 1, 1);
    grafo.DFS(0);
    
    return 0;
}
