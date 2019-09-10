// A C++ program to print topological sorting of a DAG 
#include<iostream> 
#include <list> 
#include <stack>
#include <vector> 
using namespace std; 
  
// Class to represent a graph 
class Graph 
{ 
    int V;    // No. of vertices' 
  
    // Pointer to an array containing adjacency listsList 
    vector<int> *adj; 

public: 
    Graph(int V);   // Constructor 
  
     // function to add an edge to graph 
    void addEdge(char v, char w); 
  
    // prints a list of vertices in the graph
    void print(); 

    // verify if exist a path between two vertices
    bool hasPath(int a, int b);

    // transform char in int
    int codeChar(char c);

    // transform a int in char
    char decodeInt(int n);

    // walk in a graph
    bool Graph::walk(int u, int v);
}; 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new vector<int>[V]; 
} 
  
void Graph::addEdge(char v, char w) 
{ 
    adj[codeChar(v)].push_back(codeChar(w)); // Add w to v’s list. 
} 

int Graph::codeChar(char c){
    return (int)c - 97;
}

char Graph::decodeInt(int n){
    return (char)(n+97);
}

void Graph::print(){
    cout << "V: " << this->V << "\n";
    for(int i=0; i<this->V; i++){
        cout << "V: " << decodeInt(i) << "---> ";
        for(int j=0; j<this->adj[i].size(); j++){
            cout << (char)(this->decodeInt(adj[i].at(j)))  << ",";
        }
        cout << "\n";
    }
}

bool Graph::hasPath(int verticeInicial, int verticeFinal){
    bool hasPath = false;

    int cont = 0;
    int verticeAtual = verticeFinal;
    while(verticeAtual != verticeInicial || cont < this->V){
       
        // motor da recursividade onde irá tentar achar caminho por todos os vertices adjacente ao vertice atual
        for(int i=0; i<this->adj[verticeAtual].size(); i++){
            hasPath = walk(verticeAtual, i);
        }
        cont++;
    }
    for(int i = b;)
    return hasPath;
}

bool Graph::walk(int u, int v){
    bool hasPath = false;

     if(u == v){
            hasPath = true;
        }
        else{
            // vai para o próximo vértice se o próximo vertice é diferente do que ele acabou de vir
            //int nextVertice = this->adj[v].at
            //walk(a, )
        }
    return hasPath;
}


    
// Driver program to test above functions 
int main() 
{ 
    int casesOfTest;
    int vertices; //value of n
    int edges;

    /*cout << "n vertices";
    cin >> casesOfTest;
    cin >> vertices;
    cin >> edges;*/

    for(int i=0; i<casesOfTest; i++){

    }

    // Create a graph with n vertices 
    Graph g(3); 
    g.addEdge('a', 'b'); 
    g.addEdge('a', 'c'); 
    g.addEdge('b', 'c'); 
    g.addEdge('b', 'a');
    g.addEdge('c', 'a');
    g.addEdge('c', 'b');
    
    g.print();
  
    return 0; 
} 