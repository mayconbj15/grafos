#include<iostream> 
#include <list> 
#include <string> 
#include <sstream>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <vector> 

using namespace std; 

class Vertex{
   
    
public: 
    double x;
    double y; 

    Vertex(double x, double y);   // Constructor 
    void showVertex();
}; 

Vertex::Vertex(double x, double y) 
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

        double calculaDistancia(Vertex a, Vertex b);

        void print();

        void printArray(double array[]);

        void inicializaGrafo();

        int minKey(double key[], bool mstSet[]);

        void printMST(int parent[]); 

        double primMST();  

        double sumOfWeights(int parent[]);

        vector<Vertex> createLigation(vector<string> ligation, vector<Vertex> lista);

        vector<Vertex> addEdge(double v, double w, vector<Vertex> lista);
};

Graph::Graph(int V){
    this->V = V;

    inicializaGrafo();
}

void Graph::inicializaGrafo(){    
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
    double distance = 0.0;

    distance = sqrt(pow((b.x - a.x),2) + pow((b.y - a.y),2));

    return distance;
}

vector<Vertex> Graph::createLigation(vector<string> ligation, vector<Vertex> lista){
    return addEdge(stod(ligation[0]), stod(ligation[1]), lista);
}

vector<Vertex> Graph::addEdge(double v, double w, vector<Vertex> lista) { 
    lista.push_back(Vertex(v,w));
    
    return lista;
} 
  
// A utility function to find the vertex with  
// minimum key value, from the set of vertices  
// not yet included in MST  
int Graph::minKey(double key[], bool mstSet[])  
{  
    // Initialize min value  
    double min = INT_MAX;
    int min_index;  
  
    for (int v = 0; v < V; v++)  
        if (mstSet[v] == false && key[v] < min)  
            min = key[v], min_index = v;  
  
    return min_index;  
}  
  
// A utility function to print the  
// constructed MST stored in parent[]  
void Graph::printMST(int parent[])  
{  
    cout<<"Edge \tWeight\n";  
    for (int i = 1; i < V; i++)  
        cout<<parent[i]<<" - "<<i<<" \t"<<this->graph[i][parent[i]]<<" \n";  

    
}

double Graph::sumOfWeights(int parent[]){
    double sum = 0.0;

    for (int i = 1; i < V; i++){  
        sum += this->graph[i][parent[i]];
        cout << "menor " << graph[i][parent[i]];
    }

    return sum;
}
  
// Function to construct and print MST for  
// a graph represented using adjacency  
// matrix representation  
double Graph::primMST()  
{  
    // Array to store constructed MST  
    int parent[V];  
      
    // Key values used to pick minimum weight edge in cut  
    double key[V];  
      
    // To represent set of vertices not yet included in MST  
    bool mstSet[V];  
  
    // Initialize all keys as INFINITE  
    for (int i = 0; i < V; i++)  
        key[i] = INT_MAX, mstSet[i] = false;  
  
    // Always include first 1st vertex in MST.  
    // Make key 0 so that this vertex is picked as first vertex.  
    key[0] = 0;  
    parent[0] = -1; // First node is always root of MST  
  
    // The MST will have V vertices  
    for (int count = 0; count < V - 1; count++) 
    {  
        // Pick the minimum key vertex from the  
        // set of vertices not yet included in MST  
        int u = minKey(key, mstSet);  
  
        // Add the picked vertex to the MST Set  
        mstSet[u] = true;  
  
        // Update key value and parent index of  
        // the adjacent vertices of the picked vertex.  
        // Consider only those vertices which are not  
        // yet included in MST  
        for (int v = 0; v < V; v++)  
            // graph[u][v] is non zero only for adjacent vertices of m  
            // mstSet[v] is false for vertices not yet included in MST  
            // Update the key only if graph[u][v] is smaller than key[v]  
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])  
                parent[v] = u, key[v] = graph[u][v];  
    }  
  
    // print the constructed MST  
    printMST(parent);  
    return sumOfWeights(parent);
}

vector<string> split(string strToSplit, char delimeter) {
    stringstream ss(strToSplit);
    string item;
    vector<string> splittedStrings;
    
    while (getline(ss, item, delimeter)) {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

// driver program to test above function 
int main() 
{ 
    int cases;
    int num_vertex;

    cin >> cases;

    for(int i=0; i < cases; i++){
        cin >> num_vertex;
        Graph graph(num_vertex);

        //graph.inicializaGrafo();

        string buffer;
        getline(cin, buffer);
        
        vector<Vertex> lista;

        for(int j=0; j<num_vertex; j++){
            string atualLigation;
        
            getline(cin, atualLigation);

            vector<string> result = split(atualLigation, ' '); 
            atualLigation = "";
            
            lista = graph.createLigation(result, lista);
        }


        graph.geraGrafo(lista, graph.V);

        graph.print();

        double sumOfWeigths = graph.primMST(); 

        printf("%.2f \n\n", sumOfWeigths/100);
    }
    
    return 0; 
} 