#include <iostream>
#include <vector>

#include <stdlib.h>

using namespace std;

class Graph{
    public:
        int V;

        int** graph;

        int* dist;

        int* parent;

        Graph(int V);
        
        void print();

        void inicializaGrafo();

        void createLigation(int a, int b, int c);

        vector<int> getPossibleRoutes();
        
        int getLessDistanceOfPossibleRoutes(vector<int>);

        /** Diijskra **/
        int minDistance(int dist[], bool sptSet[]);

        int printSolution(int dist[]);

        int printParent(int parent[]);

        int dijkstra(int src);  

        int findLessDistance();
      
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
int Graph::dijkstra(int src){ 
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
    this->dist = dist;
    this->parent = parent;
    
    printSolution(dist); 
    printParent(parent);
    showRoute(parent, 0);

    return findLessDistance();
}

vector<int> removeVertex(vector<int> possibleRoutes, int v){
    vector<int>:: iterator i;
    i = possibleRoutes.begin();

    for(int j=0; j < possibleRoutes.size(); i++, j++){
        if(possibleRoutes.at(j) == v){
            possibleRoutes.erase(i);
        }
    }

    return possibleRoutes;
}
/**
 * Return the vertex that have the less distance from the source
 */

int Graph::findLessDistance(){
    int lessDistance = dist[1];
    int vertex = 0;

    for(int i=0; i < V; i++){
        if(dist[i] < lessDistance){
            vertex = i;
        }
    }

    return vertex;
}

int getLessDistanceOfPossibleRoutes(vector<int> possibleRoutes, int dist[]){
    int nextRoute = dist[possibleRoutes.at(0)];

    for(int i=1; i < possibleRoutes.size(); i++){
        if(dist[possibleRoutes.at(i)] < nextRoute)
            nextRoute = possibleRoutes.at(i);
    }

    return nextRoute;
}



vector<int> Graph::getPossibleRoutes(){
    vector<int> possibleRoutes;

    for(int i=0; i < V; i++){
        if(graph[0][i] != 0)
            possibleRoutes.push_back(i);
    }

    return possibleRoutes;
}

int Graph::getLessDistanceOfPossibleRoutes(vector<int>){

}


int main(){
    int nRotasVoo, nCidades;
    int nAmigos, acentosDisponiveis;

    cin >> nCidades;
    cin >> nRotasVoo;
    
    Graph graph(nCidades);

    graph.print();

    for(int i=0; i < nRotasVoo; i++){
        int cidadeA, cidadeB, preco;
        

        cin >> cidadeA;
        cin >> cidadeB;
        cin >> preco;

        graph.createLigation(cidadeA, cidadeB, preco);
        
        
    }

    cin >> nAmigos;
    cin >> acentosDisponiveis;

    if(nAmigos > acentosDisponiveis){
        int nRotas = nAmigos / acentosDisponiveis;
        int lessVertex = graph.dijkstra(0); // calcular o valor dessa rota
        cout << "LESS VERTEX " << lessVertex;
        int totalDistance = graph.dist[lessVertex];
        
        cout << "DIST " << endl;

        for(int i=0; i < graph.V; i++){
                printf("%d ", graph.dist[i]);
            }
        cout << "TOTAL DISTANCE: " << totalDistance << endl;

        cout << "DIST " << endl;
        for(int i=0; i < graph.V; i++){
            printf("%d ", graph.dist[i]);
        }

        for(int i=0; i < nRotas-1; i++){
            vector<int> possibleRoutes;
    
            possibleRoutes = graph.getPossibleRoutes();

            possibleRoutes = removeVertex(possibleRoutes, lessVertex);

            cout << "Possible routes\n";

            for(int i=0; i < possibleRoutes.size(); i++){
                printf("%d ", possibleRoutes.at(i));
            }

            cout << endl;

            cout << "Rotas " << nRotas << endl;

            int nextRoute = getLessDistanceOfPossibleRoutes(possibleRoutes, graph.dist);

            cout << "Next route " << nextRoute << endl;

            //graph.dijkstra(nextRoute);
           

            int distanceNextRouteToSource = graph.dist[nextRoute];
            cout << "Distance Next Route to Source " << distanceNextRouteToSource << endl;
            
            totalDistance += distanceNextRouteToSource + graph.dijkstra(nextRoute);

            cout << "Total distance: " << totalDistance << endl;
        }
        
    }

    graph.print();

    cout << "Less Vertex " << graph.dijkstra(0);

}