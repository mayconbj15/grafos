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
        list<int> *adj;

        Graph(int V);

        void initializeGraph();
        void createLigation(int x, int y);
        bool verifyBolado(int** graph, int v);
        bool isSC();
        Graph getTranspose(); 

        void DFSUtil(int v, bool visited[]) ; 
        void verifyBolado();
    private:
        void addEdge(int u, int v);
        bool verifyBolado(int** graph, int v, bool bolado);
};

Graph::Graph(int V){
    this->V = V;
    adj = new list<int>[V]; 
}



void Graph::createLigation(int x, int y){
    addEdge(x, y);
}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v); // Add w to v’s list.
}
void Graph::verifyBolado() 
{ 
    // Mark all the vertices as not visited 
    bool *visited = new bool[V]; 
    vector<int> listOfVertex;

    for(int v = 0; v < V; v++) 
        visited[v] = false; 
    
    int connectedComponents = 0;

    for (int v=2; v<V; v++) 
    { 
        if (visited[v] == false) 
        { 
            // print all reachable vertices 
            // from v 
             DFSUtil(v, visited); 
            
        } 
    } 
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    //cout << v << endl;
  
    // Recur for all the vertices 
    // adjacent to this vertex 
    list<int>::iterator i; 
    for(i = adj[v].begin(); i != adj[v].end(); i++) 
        if(!visited[*i]) 
            DFSUtil(*i, visited); 

} 

bool Graph::isSC() 
{ 
    // St1p 1: Mark all the vertices as not visited (For first DFS) 
    bool visited[V]; 
    
    for (int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Step 2: Do DFS traversal starting from first vertex. 
    //cout << "Normal\n";
    /*DFSUtil(0, visited); 
  
     // If DFS traversal doesn’t visit all vertices, then return false. 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
             return false; */
  
    // Step 3: Create a reversed graph 
    Graph gr = getTranspose(); 
  
    // Step 4: Mark all the vertices as not visited (For second DFS) 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    // Step 5: Do DFS for reversed graph starting from first vertex. 
    // Staring Vertex must be same starting point of first DFS 
    //cout << "Transpose\n";
    gr.DFSUtil(0, visited); 
  
    // If all vertices are not visited in second DFS, then 
    // return false 
    for (int i = 0; i < V; i++) 
        if (visited[i] == false) 
             return false; 
  
    return true; 
} 

Graph Graph::getTranspose() 
{ 
    Graph g(V); 
    for (int v = 0; v < V; v++) 
    { 
        // Recur for all the vertices adjacent to this vertex 
        list<int>::iterator i; 
        for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        { 
            g.adj[*i].push_back(v); 
        } 
    } 
    return g; 
} 


int main() {
    int vertex;
    int edges;

    int x,y;
    
    cin >> vertex; //receive the number of vertex
    cin >> edges; //receive the number of edges
    
    Graph g(vertex);
    
    for(int j=0; j<edges; j++){
        cin >> x;
        cin >> y;
        
        g.createLigation(x-1, y-1);
        //g.print();
    }
    
    g.isSC()? cout << "Bolada\n" : cout << "Nao bolada\n";

    /*if(g.verifyBolado(g.graph))
        cout << "Bolada \n";
    else
        cout << "Nao bolada \n";*/
    
        
    return 0;  
}