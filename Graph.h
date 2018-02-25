#ifndef Graph_h
#define Graph_h


#endif /* Graph_h */

#include <iostream>
using namespace std;

//Adjacency List Node
struct AdjListNode
{
    int adjVertex;
    struct AdjListNode* next;
};


//Adjacency List
struct AdjList
{
    struct AdjListNode *head;
};

//Class Graph
class Graph
{
public:
    int V;
    struct AdjList* array;
    int **adjMatrix;
public:
    Graph(int V)
    {
        this->V = V;
        adjMatrix = new int *[V];
        array = new AdjList [V];
        //Initializing all array of lists of nodes and the adjacency matrix
        for (int i = 0; i < V; ++i)
        {
            array[i].head = NULL;
            adjMatrix[i] = new int [V];
            for(int j = 0; j < V; j++)
            {
                adjMatrix[i][j] = 0;
            }
        }
    }
    
    //Creating New Adjacency List Node
    AdjListNode* newAdjListNode(int adjVertex)
    {
        AdjListNode* newNode = new AdjListNode;
        newNode->adjVertex = adjVertex;
        newNode->next = NULL;
        return newNode;
    }
    
    //Adding Edge to Graph
    void addEdge(int src, int dest)
    {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;
        AdjListNode* newNode = newAdjListNode(dest);
        newNode->next = array[src].head;
        array[src].head = newNode;
        newNode = newAdjListNode(src);
        newNode->next = array[dest].head;
        array[dest].head = newNode;
    }
    
    //Printing adjacancy matrix
    void printMatrix()
    {
        for(int i=0; i<V; ++i)
        {
            for(int j=0; j<V; ++j)
            {
                cout<<adjMatrix[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};
