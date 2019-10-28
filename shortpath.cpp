#include <iostream>
#include <stdlib.h>
#include <iomanip>


using namespace std;
const int INF = 1500;


class Graph {
private:
      int** adjMatrix;
      int numVertices;
      bool *visited;
public:

    Graph(int numVertices) {
        this->numVertices = numVertices;
        adjMatrix = new int*[numVertices];
        visited = new bool[numVertices];
        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new int[numVertices];
            visited[i] = false;
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = INF;
        }
    }
 
    void addEdge(int i, int j,int cost) {
        adjMatrix[i][j] = cost;
    }
 
    void removeEdge(int i, int j) {
        adjMatrix[i][j] = INF;
    }
 
    int isEdge(int i, int j) {
        return adjMatrix[i][j];
    }

    void printAdjMat() {
        cout << "Adjacency Matrix of Graph\n" << endl ; 
        cout<<"    ";
        for(int i=0;i<numVertices;i++){
            //cout<<std::setfill(' ')<<std::setw(16);
            cout << i<<"\t";
        }
        cout <<"\n" <<endl;
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++){
                //cout<<std::setfill(' ')<<std::setw(16);
                if(adjMatrix[i][j]==INF){
                    cout<<"INF"<<"\t";
                }
                else
                    cout << adjMatrix[i][j]<<"\t";
            }
            cout <<"\n" <<endl;
        }
        cout << "\n\n\n" << endl ; 
        
    }

    void printvisit(){
        cout<<"The visited array: \n"<<endl;
        for (int i = 0; i < numVertices; i++) {
            cout << visited[i] << "\t";
        }
        cout<<endl;
    }

    int findclosest(int dist[]){
        int min_idx;
        int min=INF;

        for(int i=0;i<numVertices;i++){
            if(visited[i]==false && dist[i] <= min){
                min_idx = i;
                min=dist[i];
            }
        }
        return min_idx;
    }

    void findShortpath(int source){
        //dist array to be operated on...
        int dist[numVertices];
        

        //initialize dist array as per cost...
        for(int i=0;i<numVertices;i++){
            dist[i] = INF;
        }
        //set source as visited...
        dist[source] = 0;
        

        for(int i=0;i<numVertices-1;i++){         //one-by-one...
            //find the closest unvisited neighbour for each vertex...
            int u = findclosest(dist);
            visited[u]=true;

            for(int w=0;w<numVertices;w++){     //now, iterate over all the vertices...
                //if a vertex is not visited and is more feasible to visit via closest neighbour...
                if(!visited[w] && adjMatrix[u][w] && dist[u]!=INF && (dist[u]+adjMatrix[u][w] < dist[w])){
                    //update distance to feasible one...
                    cout<<"Distance update at "<<w << "\tChange: " <<dist[w] << "-->" << dist[u] + adjMatrix[u][w]<<endl;
                    dist[w] = dist[u] + adjMatrix[u][w];
                }
            }

            cout<<"The current vertex was: " << i << "\nClosest neighbour was: " << u << endl;
            //cout<<"The shortest distances to each vertex are: "<<endl;
            cout<<"Updated distances..."<<endl;
            for(int i=0;i<numVertices;i++){
                if(dist[i]==INF){
                    cout<<"INF"<<"\t";
                    continue;
                }
                cout<<dist[i]<<"\t";    
            }
            cout<<"\n\n"<<endl;
        }
       
    }



 
    ~Graph() {          //Destructor
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
    }
};




int main(){

    Graph *g1 = new Graph(8);
    g1->addEdge(0,0,0);
    g1->addEdge(1,1,0);
    g1->addEdge(2,2,0);
    g1->addEdge(3,3,0);
    g1->addEdge(4,4,0);
    g1->addEdge(5,5,0);
    g1->addEdge(6,6,0);
    g1->addEdge(7,7,0);

    g1->addEdge(2,0,100);
    g1->addEdge(1,0,30);
    g1->addEdge(2,1,80);
    
    g1->addEdge(3,2,120);
    g1->addEdge(4,3,150);
    g1->addEdge(4,5,25);
    g1->addEdge(5,3,100);
    g1->addEdge(5,6,90);
    g1->addEdge(5,7,140);  
    g1->addEdge(6,7,100);
    g1->addEdge(7,0,170);
    
    g1->printAdjMat();
    g1->findShortpath(4);
    
    return 0;
}







