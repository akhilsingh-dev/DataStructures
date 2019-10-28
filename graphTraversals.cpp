#include <iostream> 
#include <list> 
using namespace std; 
  
class Graph{ 
private:
    int V;                                      // No. of vertices 
    list<int> *adj;                             // Pointer to an array containing adjacency lists  
public: 
    void DFSRec(int v, bool visited[]);
    Graph(int V);                               // Constructor 
    void addEdge(int v, int w);                 // function to add an edge to graph 
    //void DFS();                               // prints DFS traversal of the complete graph 
    void BFS(int s);
}; 
  
Graph::Graph(int V){ 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::addEdge(int v, int w){ 
    adj[v].push_back(w); 
} 
  
void Graph::DFSRec(int v, bool visited[]){ 
    visited[v] = true; 
    cout << v << " "; 
  
    list<int>::iterator i; 
    
    for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        if(!visited[*i]) 
            DFSRec(*i, visited); 

} 

void Graph::BFS(int s){ 
    bool *visited = new bool[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    list<int> queue; 
  
    visited[s] = true; 
    queue.push_back(s); 
  
    list<int>::iterator i; 
  
    while(!queue.empty()){ 
        s = queue.front(); 
        cout << s << " "; 
        queue.pop_front(); 

        for (i = adj[s].begin(); i != adj[s].end(); ++i){ 
            if (!visited[*i]){ 
                visited[*i] = true; 
                queue.push_back(*i); 
            } 
        } 
    } 
}


  
int main() 
{ 
    Graph g(5); 
    g.addEdge(0, 1); 
    g.addEdge(0, 2); 
    g.addEdge(1, 2); 
    g.addEdge(2, 0); 
    g.addEdge(2, 3); 
    g.addEdge(3, 3);
    g.addEdge(4,1);
    g.addEdge(4,2);
    g.addEdge(4,3);
    g.addEdge(3,4);
    g.addEdge(2,4);
    g.addEdge(1,4); 
    
    
    bool visit[5] = {false,false,false,false,false};
    
    cout << "\nFollowing is Depth First Traversal\n"; 
    g.DFSRec(2,visit);

    cout << "\nFollowing is Breadth First Traversal\n"; 
    g.BFS(2); 
    return 0; 
} 