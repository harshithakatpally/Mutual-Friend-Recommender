#include <iostream>
#include <fstream>
#include "Graph.h"
#include "Queue.h"
#include "RedBlack.h"
using namespace std;


int main(int argc, const char * argv[]) {
    ifstream ip;
    string a;
    string b;
    string nodes;
    string edges;
    Queue q;
    int i=1;
    int currentValue;
    int current;
    int v;
    //Input data from a csv file. Change according to the location.
    ip.open("/Users/harshithareddy/Mutual-Friend-Recommender/input.csv", ifstream::in);
    if(!ip.is_open())
        cout<<"Error file open"<<endl;
    getline(ip, nodes, ',');
    getline(ip, edges, '\n');
    //Convert the data to graph
    Graph gh(atoi(nodes.c_str()));
    while(i <= atoi(edges.c_str()))
    {
        getline(ip, a, ',');
        getline(ip, b, '\n');
        gh.addEdge(atoi(a.c_str()), atoi(b.c_str()));
        i++;
    }
    RedBlack rb(atoi(nodes.c_str()));
    for (v = 0; v < gh.V; ++v)
    {
        AdjListNode* temp = gh.array[v].head;
        //For every vertex add it's friends to a queue
        while (temp)
        {
            q.push(temp->adjVertex);
            temp = temp->next;
        }
        //Pop every friend in the queue and traverse it's friends to check mutual friends
        while(!q.isEmpty())
        {
            current = q.pop();
            AdjListNode* currentFriend = gh.array[current].head;
            while(currentFriend)
            {
                if(currentFriend->adjVertex != v && !gh.adjMatrix[v][currentFriend->adjVertex])
                {
                    //If mutual friend is not present in the tree, insert it else add 1 to its count value
                    if(!rb.containsKey(rb.treeArray[v].root, currentFriend->adjVertex))
                    {
                        rb.insert(v, currentFriend->adjVertex, 1);
                    }
                    else
                    {
                        currentValue = rb.getValue(rb.treeArray[v].root, currentFriend->adjVertex);
                        rb.update(v, currentFriend->adjVertex, currentValue);
                    }
                }
                currentFriend = currentFriend->next;
            }
        }
        //Output all mutual friends in decreasing order
        cout<<v<<" {";
        rb.displayTree(rb.treeArray[v].root);
        cout<<"}"<<endl;
        
    }
    
    return 0;

}
