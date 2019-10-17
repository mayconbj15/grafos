// C++ program to print connected components in 
// an undirected graph 
#include<iostream> 
#include <list> 
using namespace std; 
  
// Graph class represents a undirected graph 
// using adjacency list representation 
class Graph 
{ 
    int V;    // No. of vertices 
  
    // Pointer to an array containing adjacency lists 
    list<char> *adj; 
  
    // A function used by DFS 
    void DFSUtil(int v, bool visited[]); 

public: 
    Graph(int V);   // Constructor 
    void addEdge(char v, char w); 
    int connectedComponents(); 

    int codeChar(char c);
    char decodeInt(int n);
    void createLigation(string ligation);
    void showTheConnectedComponents(Graph g, int numberCase);
}; 
  
// Method to print connected components in an 
// undirected graph and return the numbers of 
// components connecteds
int Graph::connectedComponents() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    for(int v = 0; v < V; v++) 
        visited[v] = false; 
    
    int connectedComponents = 0;

    for (int v=0; v<V; v++) 
    { 
        if (visited[v] == false) 
        { 
            // print all reachable vertices 
            // from v 
            DFSUtil(v, visited); 
  
            cout << "\n"; 
            connectedComponents++;
        } 
    } 

    return connectedComponents;
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    cout << decodeInt(v) << ","; 
  
    // Recur for all the vertices 
    // adjacent to this vertex 
    list<char>::iterator i; 
    for(i = adj[v].begin(); i != adj[v].end(); i++) 
        if(!visited[*i]) 
            DFSUtil(*i, visited); 
} 
  
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<char>[V]; 
} 
  

//method to add an undirected edge
void Graph::addEdge(char v, char w) 
{ 
    adj[codeChar(v)].push_back(codeChar(w)); // Add w to v’s list. 
    adj[codeChar(w)].push_back(codeChar(v)); // Add w to v’s list. 
} 

int Graph::codeChar(char c){
    return (int)c - 97;
}

char Graph::decodeInt(int n){
    return (char)(n+97);
}

void Graph::createLigation(string ligation){
    addEdge(ligation.at(0), ligation.at(2));
}

void Graph::showTheConnectedComponents(Graph g, int numberCase){
    cout << "Case #" << numberCase << ":\n";

    int connectedCompents = g.connectedComponents();

    cout << connectedCompents << " connected components\n\n";
}
  
// Drive program to test above 
int main() 
{ 
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
        }
        g.showTheConnectedComponents(g, i+1);
    }

    return 0; 
} 