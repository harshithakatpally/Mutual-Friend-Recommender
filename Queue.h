#ifndef Queue_h
#define Queue_h


#endif /* Queue_h */

#include <iostream>
using namespace std;

//Queue
struct QueueNode
{
    int data;
    struct QueueNode* link;
};

class Queue
{
    struct QueueNode *front, *rear;
    
public:
    Queue()
    {
        front = NULL;
        rear = NULL;
    }
    bool isEmpty()
    {
        return front == NULL && rear == NULL;
    }
    //Push an element at end of queue
    void push(int element)
    {
        struct QueueNode* newNode = new QueueNode;
        newNode->data = element;
        if(rear == NULL && front == NULL)
        {
            rear = newNode;
            front = newNode;
            newNode->link = NULL;
        }
        else
        {
            rear->link = newNode;
            newNode->link = NULL;
            rear = newNode;
        }
    }
    //Pop element from the front of the queue
    int pop()
    {
        if(front==NULL)
            return NULL;
        struct QueueNode* temp = front;
        front = front->link;
        if(front == NULL)
        {
            rear = NULL;
        }
        return temp->data;
    }
};

