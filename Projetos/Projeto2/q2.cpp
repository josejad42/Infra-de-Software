#include<iostream>
#include<pthread.h>
#define NUM_THREADS 6

//OBS: para compilar e executar o arquivo c++, usa-se a linha de comando $ g++ nomedoarquivo.cpp -o nome && ./nome $ no terminal aberto no diretório do arquivo
//Feito com a versão 11 do g++

using namespace std;

class Graph{       //Classe grafo que servirá para o grafo de alocação
    public:
    int **matrix;
    int numEdge;
    int n;
    
    Graph(int nv){     //Método que inicializa o grafo
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
    
    ~Graph() {        //Método que desaloca memória referente ao grafo
        for (int i = 0; i<n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    void setEdge(int i, int j){      // método que cria aresta entre vértices do grafo
        if(matrix[i][j] == 0) numEdge++;
        matrix[i][j] = 1;
    }

};

Graph grafo(NUM_THREADS);        // cria um grafo, para cada vértice temos uma Thread
int NumThreadsSemCiclo = 0;      // variável que indica quantas Threads terminaram a execuçao sem encontrar ciclos
bool deadlockEncontrado = false; // variável que indica se um deadlock foi encontrado

bool DFS(int tid, int v, bool *mark, bool **mark_vertex){ // Função auxiliar que realiza uma busca por profundidade no grafo
    printf("Thread %d Vertice %d\n", tid, v);

    if(mark[v]) return true; // verifica a existencia de deadlocks, analisando se o vertice atual já está marcado
    mark[v] = true;          // marca o vertice atual 

    for(int i = 0; i<grafo.n; i++){
        if((mark_vertex[v][i] == false) && (grafo.matrix[v][i])){ // verifica se a aresta ainda não foi percorrida e se ela existe no grafo
            mark_vertex[v][i] = true;           // marca aresta como visitada
            return DFS(tid,i,mark,mark_vertex); // chama recursivamente a função
        }
    }
    mark[v] = false; //desmarca vértice atual na volta para nó anterior
    return false;
}

void *FindDeadlock(void* threadid){             //Função que encontra um ciclo se houver
    if (deadlockEncontrado) pthread_exit(NULL); //Finaliza a thread se um deadlock já foi encontrado
    int tid = *((int*) threadid);
    printf("Thread %d Vertice %d\n", tid, tid);

    int size = grafo.n;
    bool mark[size];    // vetor que indica os vértices marcados
    for (int i = 0; i<size; i++){
        mark[i] = false;
    }
    bool **mark_vertex; // matriz que indica as arestas visitadas
    mark_vertex = new bool*[size];
    for (int i = 0; i < size; i++) {
        mark_vertex[i] = new bool[size];
    }
    for(int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            mark_vertex[i][j] = false;
        }
    }

    mark[tid] = true;  // marca vértice inicial
    bool deadlock;     // variável que indica a existência de deadlocks

    for(int i = 0; i<size; i++){
        if (deadlockEncontrado) pthread_exit(NULL);                   //Finaliza a thread se um deadlock já foi encontrado
        if((mark_vertex[tid][i] == false) && (grafo.matrix[tid][i])){ // verifica se a aresta ainda não foi percorrida e se ela existe no grafo
            mark_vertex[tid][i] = true;                               //marca aresta como visitada
            deadlock = DFS(tid,i,mark,mark_vertex); 
        }
        if (deadlock){
            printf("Deadlock encontrado.\n");
            deadlockEncontrado = true;
            pthread_exit(NULL);
        }
    }
    
    if(!deadlock) NumThreadsSemCiclo++; //incrementa a variável quando a execuçao da thread nao encontrar deadlock 
    if(NumThreadsSemCiclo == NUM_THREADS) printf("Sem deadlock nesse grafo de alocação.\n"); //se nenhuma das threads encontrou um ciclo, não existe deadlock no grafo de alocação
    
    for(int i = 0; i<size; i++){
        delete[] mark_vertex[i];
    }
    delete[] mark_vertex;
    
    pthread_exit(NULL);
}

int main(){
    grafo.setEdge(0, 3);    //linhas 90 a 97 adicionam as arestas do grafo de alocação
    grafo.setEdge(1, 5);
    grafo.setEdge(1, 2);
    grafo.setEdge(2, 3);
    grafo.setEdge(4, 1);
    grafo.setEdge(4, 5);
    grafo.setEdge(5, 3);
    grafo.setEdge(3, 1);
 
    pthread_t threads[NUM_THREADS];
    int *threadids[NUM_THREADS];
    int rc;
    for(int i=0; i<NUM_THREADS; i++){ // inicializa uma Thread para cada vertice do grafo de alocação
        threadids[i] = (int*) malloc(sizeof(int));
        *threadids[i] = 3;
        rc = pthread_create(&threads[i],NULL,FindDeadlock,(void*)threadids[i]);
        if(rc){
            printf("Erro! Codigo de retorno %d", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);

}
