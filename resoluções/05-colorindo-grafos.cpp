// C++ implementation of the approach 
#include <bits/stdc++.h> 
using namespace std; 
  
class Graph { 
  
    // Number of vertex 
    int V; 
  
    // Number of edges 
    int E; 
  
    // Adjacency matrix 
    int** adj; 
  
public: 
    // To create the initial adjacency matrix 
    Graph(int v, int e); 
  
    // Function to insert a new edge 
    void addEdge(int start, int e); 
  
    int connectedComponents(); 

    void DFSUtil(int v, bool visited[]); 

    void createLigation(int x, int y);

    int isPossibleNewEdges(int newEdges, int colours[]);
}; 
  
// Function to fill the empty adjacency matrix 
Graph::Graph(int v, int e) 
{ 
    this->V = v; 
    this->E = e; 
    adj = new int*[v]; 
    for (int row = 0; row < v; row++) { 
        adj[row] = new int[v]; 
        for (int column = 0; column < v; column++) { 
            adj[row][column] = 0; 
        } 
    } 
} 
  
// Function to add an edge to the graph 
void Graph::addEdge(int start, int e) 
{ 
  
    // Considering a bidirectional edge 
    adj[start][e] = 1; 
    adj[e][start] = 1; 
} 
  
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
  
            connectedComponents++;
        } 
    } 

    return connectedComponents;
} 
  
void Graph::DFSUtil(int v, bool visited[]) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 

    // Recur for all the vertices 
    // adjacent to this vertex 
    int i; 
    for(i = 0; i != V; i++) {
        if(adj[v][i] == 1 && !visited[i]) 
            DFSUtil(i, visited);
    }
        
} 

void Graph::createLigation(int x, int y){
    addEdge(x, y);
}

int Graph::isPossibleNewEdges(int newEdges, int colours[]){
    for(int i=0; newEdges > 0 && i < V; i++){
        for(int j=0; newEdges > 0  && j < V; j++){
            if(adj[i][j] != 1 && adj[i][j] != i && colours[i] != colours[j]){
                //verificar se a possível ligação é de cor diferente
                addEdge(i,j);
                newEdges--; 
            }
        }
    }
    
    return newEdges;
}
  
// Driver code 
int main() 
{  
    int cases, nVertex, nEdges;
    int newEdges, nCores;
    
    int x,y;

    cin >> cases;

    for(int i=0; i < cases; i++){
        cin >> nVertex;
        cin >> nEdges;
        cin >> newEdges;
        cin >> nCores;
        
        int colours[nCores];

        Graph graph(nVertex, nEdges);

        for(int j=0; j < nVertex; j++){
            cin >> colours[i];
        }

        for(int k=0; k < nEdges; k++){
            cin >> x;
            cin >> y;

            graph.createLigation(x-1, y-1);
        }
        
        int result = graph.isPossibleNewEdges(newEdges, colours);

        //cout << "RESULT: " << result << endl;

        
        if(result != 0)
            cout << "N" << endl;
        else{
            result = graph.connectedComponents();
            if(result == 1)
                cout << "Y" << endl;
            else
                cout << "N" << endl;
        } 
            

    }
} 