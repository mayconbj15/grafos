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

// a structure to represent a weighted edge in graph  
class Edge  
{  
    public: 
    int src, dest, weight;  
}; 

class Graph{
    public:
        int V, E;
        double** graph;
        
        // graph is represented as an array of edges.  
        // Since the graph is undirected, the edge  
        // from src to dest is also edge from dest  
        // to src. Both are counted as 1 edge here.  
        Edge* edge; 
        Graph(int V);

        void geraGrafo(vector<Vertex> lista, int V);

        double calculaDistancia(Vertex a, Vertex b);

        void print();

        void printArray(double array[]);

        void inicializaGrafo();


        double sumOfWeights(int parent[]);

        vector<Vertex> createLigation(vector<string> ligation, vector<Vertex> lista);

        vector<Vertex> addEdge(double v, double w, vector<Vertex> lista);
};

Graph::Graph(int V){
    this->V = V;
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

vector<Vertex> Graph::createLigation(vector<string> ligation, vector<Vertex> lista){
    return addEdge(stod(ligation[0]), stod(ligation[1]), lista);
}

vector<Vertex> Graph::addEdge(double v, double w, vector<Vertex> lista) { 
    lista.push_back(Vertex(v,w));
    
    return lista;
} 

double Graph::sumOfWeights(int parent[]){
    double sum = 0.0;

    for (int i = 1; i < V; i++)  
        sum += this->graph[i][parent[i]];

    return sum;
}

// A structure to represent a subset for union-find  
class subset  
{  
    public: 
    int parent;  
    int rank;  
};  
  
// A utility function to find set of an element i  
// (uses path compression technique)  
int find(subset subsets[], int i)  
{  
    // find root and make root as parent of i  
    // (path compression)  
    if (subsets[i].parent != i)  
        subsets[i].parent = find(subsets, subsets[i].parent);  
  
    return subsets[i].parent;  
}  
  
// A function that does union of two sets of x and y  
// (uses union by rank)  
void Union(subset subsets[], int x, int y)  
{  
    int xroot = find(subsets, x);  
    int yroot = find(subsets, y);  
  
    // Attach smaller rank tree under root of high  
    // rank tree (Union by Rank)  
    if (subsets[xroot].rank < subsets[yroot].rank)  
        subsets[xroot].parent = yroot;  
    else if (subsets[xroot].rank > subsets[yroot].rank)  
        subsets[yroot].parent = xroot;  
  
    // If ranks are same, then make one as root and  
    // increment its rank by one  
    else
    {  
        subsets[yroot].parent = xroot;  
        subsets[xroot].rank++;  
    }  
}  
  
// Compare two edges according to their weights.  
// Used in qsort() for sorting an array of edges  
int myComp(const void* a, const void* b)  
{  
    Edge* a1 = (Edge*)a;  
    Edge* b1 = (Edge*)b;  
    return a1->weight > b1->weight;  
}  
  
// The main function to construct MST using Kruskal's algorithm  
void KruskalMST(Graph* graph)  
{  
    int V = graph->V;  
    Edge result[V]; // Tnis will store the resultant MST  
    int e = 0; // An index variable, used for result[]  
    int i = 0; // An index variable, used for sorted edges  
  
    // Step 1: Sort all the edges in non-decreasing  
    // order of their weight. If we are not allowed to  
    // change the given graph, we can create a copy of  
    // array of edges  
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);  
  
    // Allocate memory for creating V ssubsets  
    subset *subsets = new subset[( V * sizeof(subset) )];  
  
    // Create V subsets with single elements  
    for (int v = 0; v < V; ++v)  
    {  
        subsets[v].parent = v;  
        subsets[v].rank = 0;  
    }  
  
    // Number of edges to be taken is equal to V-1  
    while (e < V - 1 && i < graph->E)  
    {  
        // Step 2: Pick the smallest edge. And increment  
        // the index for next iteration  
        Edge next_edge = graph->edge[i++];  
  
        int x = find(subsets, next_edge.src);  
        int y = find(subsets, next_edge.dest);  
  
        // If including this edge does't cause cycle,  
        // include it in result and increment the index  
        // of result for next edge  
        if (x != y)  
        {  
            result[e++] = next_edge;  
            Union(subsets, x, y);  
        }  
        // Else discard the next_edge  
    }  
  
    // print the contents of result[] to display the  
    // built MST  
    cout<<"Following are the edges in the constructed MST\n";  
    for (i = 0; i < e; ++i)  
        cout<<result[i].src<<" -- "<<result[i].dest<<" == "<<result[i].weight<<endl;  
    return;  
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

        graph.inicializaGrafo();

        string buffer;
        getline(cin, buffer);
        
        vector<Vertex> lista;

        for(int j=0; j<num_vertex; j++){
            string atualLigation;
        
            getline(cin, atualLigation);

            vector<string> result = split(atualLigation, ' '); 
            
            lista = graph.createLigation(result, lista);
        }

        for(int i=0; i < graph.V; i++){
            cout << "Lista: " << lista.at(i).x << " " << lista.at(i).y;
        }

        graph.geraGrafo(lista, graph.V);

//        graph.print();
        double sumOfWeigths = graph.primMST(); 
        cout << "sumOfWeigths" << sumOfWeigths << "\n";

        printf("%.2lf \n", sumOfWeigths/100);
    }
    
    return 0; 
} 