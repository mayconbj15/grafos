#include <iostream>

#include <stdlib.h>

using namespace std;

class Graph{
    public:
        int V;

        int** graph;

        Graph(int V);
        
        void print();

        void inicializaGrafo();

        void createLigation(int a, int b, int c);

        /** Diijskra **/
        int minDistance(int dist[], bool sptSet[]);

        int printSolution(int dist[]);

        int printParent(int parent[]);

        void dijkstra(int src);  
      
};

Graph::Graph(int V){
    this->V = V;

    inicializaGrafo();
}

void Graph::inicializaGrafo(){    
    this->graph = (int**)malloc(this->V * sizeof(int*)); //Aloca um Vetor de Ponteiros
 
    for (int i = 0; i < this->V; i++){ //Percorre as linhas do Vetor de Ponteiros
        this->graph[i] = (int*) malloc(this->V * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (int j = 0; j < this->V; j++){ //Percorre o Vetor de Inteiros atual.
                this->graph[i][j] = 0; //Inicializa com 0.
        }
    }
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

void Graph::createLigation(int a, int b, int c){
    this->graph[a-1][b-1] = c;
    this->graph[b-1][a-1] = c;
}

// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int Graph::minDistance(int dist[], bool sptSet[]){ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
// A utility function to print the constructed distance array 
int Graph::printSolution(int dist[]){ 
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < V; i++) {
        printf("%d \t\t %d\n", i+1, dist[i]); 
    }
} 

int Graph::printParent(int parent[]){
    for(int i=0; i < V; i++){
        printf("Parent: %d \t\t %d\n", i+1, parent[i]);
    }
}

int showRoute(int parent[], int vertex){
    if(vertex != 0){
        showRoute(parent, parent[vertex]);
        printf("Route: %d ", parent[vertex]);
    }
}
  
// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void Graph::dijkstra(int src){ 
    int parent[V];

    int dist[V]; // The output array.  dist[i] will hold the shortest 
    // distance from src to i 
  
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
    // path tree or shortest distance from src to i is finalized 
  
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, sptSet[i] = false; 
  
    // Distance of source vertex from itself is always 0 
    dist[src] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < V - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to src in the first iteration. 
        int u = minDistance(dist, sptSet); 
  
        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < V; v++) 
  
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + graph[u][v] < dist[v]){
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u; 
                } 
                
    } 
  
    // print the constructed distance array 
    printSolution(dist); 
    printParent(parent);
    showRoute(parent, 4);
} 

int main(){
    int nRotasVoo, nCidades;

    cin >> nCidades;
    cin >> nRotasVoo;
    
    Graph graph(nCidades);

    graph.print();

    for(int i=0; i < nRotasVoo; i++){
        int cidadeA, cidadeB, preco;
        int nAmigos, acentosDisponiveis;

        cin >> cidadeA;
        cin >> cidadeB;
        cin >> preco;

        graph.createLigation(cidadeA, cidadeB, preco);
        
        //cin >> nAmigos;
        //cin >> acentosDisponiveis;
    }

    graph.print();

    graph.dijkstra(0);

}