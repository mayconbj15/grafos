#include <iostream>
#include <vector>
#include <limits.h>

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

        vector<int> getPossibleRoutes(int src);

        /** Diijskra **/
        int minDistance(int dist[], bool sptSet[]);

        int printSolution(int dist[]);

        int printParent(int parent[]);

        int dijkstra(int src);  
   
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
        printf("%d \t\t %d\n", i, dist[i]); 
    }
} 

int Graph::printParent(int parent[]){
    for(int i=0; i < V; i++){
        printf("Parent: %d \t\t %d\n", i, parent[i]);
    }
}
  
// Function that implements Dijkstra's single source shortest path algorithm 
// for a graph represented using adjacency matrix representation 
int Graph::dijkstra(int src){ 
    int* parent = (int*)malloc(V * sizeof(int));

    int* dist = (int*)malloc(V * sizeof(int)); // The output array.  dist[i] will hold the shortest 
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
  
    this->dist = dist;
    this->parent = parent;
    
    return dist[V-1];
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

void showRoute(int parent[], int src, int vertex){
    if(vertex != src){
        showRoute(parent, src, parent[vertex]);
        printf("%d ", vertex);
    }else{
        printf("%d ", src);
    }
}

int getLessRoute(vector<int> weightOfRoutes){
    int lessRoute = weightOfRoutes.at(0);

    vector<int>::iterator i;
    vector<int>::iterator j;
    int k = 0;

    j = weightOfRoutes.begin();
    for(i = weightOfRoutes.begin(); k < weightOfRoutes.size(); i++, k++){
        if(weightOfRoutes.at(k) < lessRoute){
            lessRoute = weightOfRoutes.at(k);
            j = i;
        }
            
    }
    
    weightOfRoutes.erase(j);

    return lessRoute;
}

vector<int> Graph::getPossibleRoutes(int src){
    vector<int> possibleRoutes;

    for(int i=0; i < V; i++){
        if(graph[0][i] != 0 && graph[0][i] != src)
            possibleRoutes.push_back(i);
    }

    return possibleRoutes;
}

int getPeoplesInRoute(int nAmigos, int acentosDisponiveis){
    return acentosDisponiveis >= nAmigos ? nAmigos : acentosDisponiveis;
}


int main(){
    int nRotasVoo, nCidades;
    int nAmigos, acentosDisponiveis;

    int instancia = 1;

    while(scanf("%d %d", &nCidades, &nRotasVoo) != EOF) {
        Graph graph(nCidades);
        
        for(int i=0; i < nRotasVoo; i++){
            int cidadeA, cidadeB, preco;
        
            cin >> cidadeA;
            cin >> cidadeB;
            cin >> preco;

            graph.createLigation(cidadeA, cidadeB, preco);
        }

        cin >> nAmigos;
        cin >> acentosDisponiveis;
        
        int peoplesInRoute = getPeoplesInRoute(nAmigos, acentosDisponiveis); //take how many people 'll in the route

        int currentWeight = graph.dijkstra(0); // calculate the distance of the vertex n-1 to the src
        int totalPrice = peoplesInRoute * currentWeight; //get the total price of current route
        
        int nRotas = nAmigos / acentosDisponiveis; //get the numbers of routes

        if(nRotas < nRotasVoo){
            int nRotas = nAmigos / acentosDisponiveis;
        
            int src = 0;
            vector<int> possibleRoutes;
            possibleRoutes = graph.getPossibleRoutes(src); //get the possibles routes from the source

            for(int i=nRotas-1; i > 0; i--){
                
                int nextRoute = possibleRoutes.at(i); //get the next route to go
                
                int distanceNextRouteToSource = graph.dist[nextRoute]; 
                int currentWeight = graph.dijkstra(nextRoute); //get the current distance 

                currentWeight += distanceNextRouteToSource; //get the total distance of this route

                int currentPrice = peoplesInRoute * currentWeight;

                totalPrice += currentPrice;
            }
            
            cout << "Instancia " << instancia << endl << endl << totalPrice << endl << endl <<endl << endl;

        } else if(nRotas > nRotasVoo){
            cout << "Instancia " << instancia << endl << endl << "impossivel";
        }

        instancia++;   
    }
    
}