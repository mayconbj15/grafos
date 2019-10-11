#include<iostream> 
#include <list> 
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <vector> 

using namespace std;

class Graph{
    public:
        int V;
        int** graph;

        Graph(int V);

        void initializeGraph();
        
        void print();

        void createLigation(string ligation);

        void addEdge(char u, char v);

        void addEdge(int u, int v);

        bool verifyBolado(int** graph, int v);

        bool verifyBolado(int** graph, int v, bool bolado);
};

Graph::Graph(int V){
    this->V = V;

    initializeGraph();
}

void Graph::initializeGraph(){    
    this->graph = (int**)malloc(this->V * sizeof(int*)); //Aloca um Vetor de Ponteiros
 
    for (int i = 0; i < this->V; i++){ //Percorre as linhas do Vetor de Ponteiros
        this->graph[i] = (int*) malloc(this->V * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (int j = 0; j < this->V; j++){ //Percorre o Vetor de Inteiros atual.
                this->graph[i][j] = 0; //Inicializa com 0.
        }
    }
}


void Graph::createLigation(string ligation){
    addEdge(ligation.at(0), ligation.at(2));
}

void Graph::addEdge(char u, char v){
    addEdge((int)u - 48, (int)v - 48);
}

void Graph::addEdge(int u, int v) {
    this->graph[u-1][v-1] = 1;
}

bool Graph::verifyBolado(int** graph, int v) {
    return verifyBolado(graph, v, false);
}

bool Graph::verifyBolado(int** graph, int v, bool bolado) {
    if(v < this->V){
        bolado = false;    

        for(int j=0; j < this->V; j++){
            if(this->graph[v][j] == 1){
                bolado = true;
                bolado = verifyBolado(this->graph, v+1, bolado);
            }
        }
        
    }
  
    return bolado;
}

void Graph::print(){
    cout << "GRAFO \n";

    for(int i=0; i<this->V; i++){
        for(int j=0; j<this->V; j++){
            cout << this->graph[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int quantTest;
    int vertex;
    int edges;
    
    cin >> quantTest; //receive the cases of test
    

    for(int i=0; i<quantTest; i++){
        cin >> vertex; //receive the number of vertex
        cin >> edges; //receive the number of edges
        
       
        //buffer to clear the '\n' character of the input above
        string buffer;
        getline(cin, buffer);
        
        Graph g(vertex);
        
        for(int j=0; j<edges; j++){
            string atualLigation;
        
            getline(cin, atualLigation);
            
            g.createLigation(atualLigation);

            //g.print();
        }

        if(g.verifyBolado(g.graph, 0))
            cout << "Bolada\n";
        else
            cout << "Nao bolada\n";
    }
        
    return 0;  
}