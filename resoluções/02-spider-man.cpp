// C++ program to print connected components in 
// an undirected graph 
#include<iostream> 
#include <list> 
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <vector> 

using namespace std; 

class Vertex{
   
    
public: 
    int x;
    int y; 

    Vertex(int x, int y);   // Constructor 
    void showVertex();
}; 

Vertex::Vertex(int x, int y) 
{ 
    this->x = x;
    this->y = y;
}

void Vertex::showVertex() {
    cout << "(" << this->x << ", " << this->y << ")\n"; 
}

class Graph{
    public:
        int V;
        double** graph;

        Graph(int V);

        void geraGrafo(vector<Vertex> lista, int V);

        void dijkstra(int src);

        int printSolution(double dist[]);

        int minDistance(double dist[], bool sptSet[]);

        double calculaDistancia(Vertex a, Vertex b);

        void print();

        void printArray(double array[]);

        void inicializaGrafo();
};

Graph::Graph(int V){
    this->V = V;
}

void Graph::inicializaGrafo(){
    //cout << "INICIALIZA GRAFO \n";
    
    this->graph = (double**)malloc(this->V * sizeof(double*)); //Aloca um Vetor de Ponteiros
 
    for (int i = 0; i < this->V; i++){ //Percorre as linhas do Vetor de Ponteiros
        this->graph[i] = (double*) malloc(this->V * sizeof(double)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (int j = 0; j < this->V; j++){ //Percorre o Vetor de Inteiros atual.
                this->graph[i][j] = 0; //Inicializa com 0.
        }
    }
}

void Graph::geraGrafo(vector<Vertex> lista, int V){
    //double graph[V][V];
    double distance;

    for(int i=0; i<lista.size(); i++){
        for(int j=0; j<lista.size(); j++){
            if(i != j){
                distance = calculaDistancia(lista.at(i), lista.at(j));
                this->graph[i][j] = distance;
                /*cout << "DISTANCIA: "; 
                lista.at(i).showVertex();
                lista.at(j).showVertex();
                cout << distance << "\n";
                this->print();*/
            }

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

double Graph::calculaDistancia(Vertex a, Vertex b){
    double distance;

    distance = sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2));

    return distance;
}


  
// A C++ program for Dijkstra's single source shortest path algorithm. 
// The program is for adjacency matrix representation of the graph 
  
  
// Number of vertices in the graph 
 
  
// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int Graph::minDistance(double dist[], bool sptSet[]) 
{ 
    // Initialize min value 
    double min = INT_MAX;
    int min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
// A utility function to print the constructed distance array 
int Graph::printSolution(double dist[]) 
{ 
    printf("Vertex \t\t Distance from Source\n"); 
    for (int i = 0; i < this->V; i++) 
        printf("%d \t\t %lf\n", i, dist[i]); 
} 
  
// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
void Graph::dijkstra(int src) 
{ 
    double dist[V]; // The output array.  dist[i] will hold the shortest 
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
        cout << "MIN INDEX OF" << count << ": " << u << "\n";

        // Mark the picked vertex as processed 
        sptSet[u] = true; 
  
        // Update dist value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < V; v++) 
  
            // Update dist[v] only if is not in sptSet, there is an edge from 
            // u to v, and total weight of path from src to  v through u is 
            // smaller than current value of dist[v] 
            if (!sptSet[v] && this->graph[u][v] && dist[u] != INT_MAX 
                && dist[u] + this->graph[u][v] < dist[v]) 
                dist[v] = dist[u] + this->graph[u][v]; 
    } 
    printArray(dist);
    // print the constructed distance array 
    printSolution(dist); 
}

void Graph::printArray(double array[]){
    for(int i=0; i < V; i++){
        cout << array[i] << " ";
    }
    cout << "\n";
}

  
// driver program to test above function 
int main() 
{ 
    Graph graph(5);

        
    graph.inicializaGrafo();

    vector<Vertex> lista;

    lista.push_back(Vertex(0,0));
    lista.push_back(Vertex(0,100));
    lista.push_back(Vertex(100,200));
    lista.push_back(Vertex(200,400));
    lista.push_back(Vertex(300,300));

    graph.geraGrafo(lista, graph.V);

    //graph.print();
  
    graph.dijkstra(0); 
  
    return 0; 
} 