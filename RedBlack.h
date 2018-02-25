#ifndef RedBlack_h
#define RedBlack_h


#endif /* RedBlack_h */

#include <iostream>
using namespace std;
//RedBlack node
struct RedBlackNode
{
    int key;
    int value;
    struct RedBlackNode* left;
    struct RedBlackNode* right;
    struct RedBlackNode* parent;
    int color;
    
};
//Array of RedBlack trees
struct RedBlackArray
{
    struct RedBlackNode* root;
};

class RedBlack
{
public:
    struct RedBlackArray* treeArray;
public:
    //Initialize the array
    RedBlack(int V)
    {
        treeArray = new RedBlackArray[V];
        for (int i = 0; i < V; ++i)
        {
            treeArray[i].root = NULL;
        }
    }
    //Create new node and initialize the values
    RedBlackNode* newRedBlackNode(int key, int value)
    {
        RedBlackNode* newNode = new RedBlackNode;
        newNode->key = key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        newNode->color = 0;
        return newNode;
    }
    
    
    //Display tree values in descending order
public:
    void displayTree(struct RedBlackNode* header)
    {
        if(header)
        {
            displayTree(header->right);
            cout<<header->key<<"="<<header->value<<"  " ;
            displayTree(header->left);
        }
    }
    //Left rotation of red black tree
public:
    void leftRotation(struct RedBlackNode* tempRoot, struct RedBlackNode* newNode, int header)
    {
        struct RedBlackNode* temp;
        temp = newNode->right;
        newNode->right = temp->left;
        if(temp->left != NULL)
            temp->left->parent = newNode;
        temp->parent = newNode->parent;
        if(newNode->parent == NULL)
            treeArray[header].root = temp;
        else if(newNode == newNode->parent->left)
            newNode->parent->left = temp;
        else
            newNode->parent->right = temp;
        temp->left = newNode;
        newNode->parent = temp;
    }
    
    //Right rotation for red black tree
public:
    void rightRotation(struct RedBlackNode* tempRoot, struct RedBlackNode* newNode, int header)
    {
        struct RedBlackNode* temp;
        temp = newNode->left;
        newNode->left = temp->right;
        if(temp->right != NULL)
            temp->right->parent = newNode;
        temp->parent = newNode->parent;
        if(newNode->parent == NULL)
            treeArray[header].root = temp;
        else if(newNode == newNode->parent->left)
            newNode->parent->left = temp;
        else
            newNode->parent->right = temp;
        temp->right = newNode;
        newNode->parent = temp;
    }
    //Insertion of node
public:
    void insert(int header, int key, int value)
    {
        struct RedBlackNode* newNode = newRedBlackNode(key, value);
        if(treeArray[header].root)
        {
            insertNode(treeArray[header].root, newNode);
            insertFix(treeArray[header].root, newNode, header);
        }
        else
        {
            treeArray[header].root = newNode;
            newNode->color = 1;
        }
        
    }
    
public:
    struct RedBlackNode* insertNode(struct RedBlackNode* tempRoot, struct RedBlackNode* newNode)
    {
        if(tempRoot == NULL)
        {
            return newNode;
        }
        if(tempRoot->value >= newNode->value)
        {
            tempRoot->left = insertNode(tempRoot->left, newNode);
            tempRoot->left->parent = tempRoot;
            
        }
        else
        {
            tempRoot->right = insertNode(tempRoot->right, newNode);
            tempRoot->right->parent = tempRoot;
        }
        return tempRoot;
    }
    
public:
    void insertFix(struct RedBlackNode* tempRoot, struct RedBlackNode* newNode, int header)
    {
        while(newNode != tempRoot && newNode->color != 1 && newNode->parent->color == 0)
        {
            if(newNode->parent == newNode->parent->parent->left)
            {
                struct RedBlackNode* temp = newNode->parent->parent->right;
                if(temp != NULL && temp->color == 0)
                {
                    newNode->parent->color = 1;
                    temp->color = 1;
                    newNode->parent->parent->color = 0;
                    newNode = newNode->parent->parent;
                }
                else
                {
                    if(newNode == newNode->parent->right)
                    {
                        newNode = newNode->parent;
                        leftRotation(tempRoot, newNode, header);
                    }
                    newNode->parent->color = 1;
                    newNode->parent->parent->color = 0;
                    rightRotation(tempRoot, newNode->parent->parent, header);
                }
            }
            else
            {
                struct RedBlackNode* temp = newNode->parent->parent->left;
                if(temp != NULL && temp->color == 0)
                {
                    newNode->parent->color = 1;
                    temp->color = 1;
                    newNode->parent->parent->color = 0;
                    newNode = newNode->parent->parent;
                }
                else
                {
                    if(newNode == newNode->parent->left)
                    {
                        newNode = newNode->parent;
                        rightRotation(tempRoot, newNode, header);
                    }
                    newNode->parent->color = 1;
                    newNode->parent->parent->color = 0;
                    leftRotation(tempRoot, newNode->parent->parent, header);
                }
            }
        }
        treeArray[header].root->color = 1;
    }
    //Deletion of node
public:
    void deleteNode(int header, struct RedBlackNode* tempRoot, struct RedBlackNode* temp)
    {
        struct RedBlackNode* y = temp;
        struct RedBlackNode* x;
        int yorgcolor = y->color;
        if(temp->left == NULL && temp->right == NULL)
        {
            if(tempRoot == temp)
                treeArray[header].root = NULL;
            else if(temp->parent->left == temp)
                temp->parent->left = NULL;
            else
                temp->parent->right = NULL;
            x = NULL;
        }
        else if(temp->left == NULL)
        {
            x = temp->right;
            RBTransplant(header, temp, temp->right);
            if(yorgcolor == 1)
                deleteFix(header, treeArray[header].root, x);
        }
        else if(temp->right == NULL)
        {
            x = temp->left;
            RBTransplant(header, temp, temp->left);
            if(yorgcolor == 1)
                deleteFix(header, treeArray[header].root, x);
        }
        else
        {
            y = treeMinimum(temp->right);
            yorgcolor = y->color;
            x = y->right;
            if(y->parent == temp && x != NULL)
            {
                x->parent = y;
            }
            else if(y->parent != temp)
            {
                RBTransplant(header, y, y->right);
                y->right = temp->right;
                y->right->parent = y;
            }
            RBTransplant(header, temp, y);
            y->left = temp->left;
            y->left->parent = y;
            y->color = temp->color;
            if(yorgcolor == 1 && x != NULL)
                deleteFix(header, treeArray[0].root, x);
        }
        
    }
    
    
public:
    void deleteFix(int header, struct RedBlackNode* tempRoot, struct RedBlackNode* temp)
    {
        struct RedBlackNode* w;
        while(temp != tempRoot && temp->color == 1)
        {
            if(temp == temp->parent->left)
            {
                w = temp->parent->right;
                if(w->color == 0)
                {
                    w->color = 1;
                    temp->parent->color = 0;
                    leftRotation(tempRoot, temp->parent, header);
                    w = temp->parent->right;
                }
                if(w->left->color == 1 && w->right->color == 1)
                {
                    w->color = 0;
                    temp = temp->parent;
                }
                else
                {
                    if(w->right->color == 1)
                    {
                        w->left->color = 1;
                        w->color = 0;
                        rightRotation(tempRoot, w, header);
                        w = temp->parent->right;
                    }
                    w->color = temp->parent->color;
                    temp->parent->color = 1;
                    w->right->color = 1;
                    leftRotation(tempRoot, temp->parent, header);
                    temp = tempRoot;
                }
            }
            
            else if(temp == temp->parent->right)
            {
                w = temp->parent->left;
                if(w->color == 0)
                {
                    w->color = 1;
                    temp->parent->color = 0;
                    rightRotation(tempRoot, temp->parent, header);
                    w = temp->parent->left;
                }
                if(w->right->color == 1 && w->left->color == 1)
                {
                    w->color = 0;
                    temp = temp->parent;
                }
                else
                {
                    if(w->left->color == 1)
                    {
                        w->right->color = 1;
                        w->color = 0;
                        leftRotation(tempRoot, w, header);
                        w = temp->parent->left;
                    }
                    w->color = temp->parent->color;
                    temp->parent->color = 1;
                    w->left->color = 1;
                    rightRotation(tempRoot, temp->parent, header);
                    temp = tempRoot;
                }
            }
        }
        if(temp != NULL)
            temp->color = 1;
    }
    
    //Transplanting a subtree in place of another
public:
    void RBTransplant(int header, struct RedBlackNode* u, struct RedBlackNode* v)
    {
        if(u->parent == NULL)
            treeArray[header].root = v;
        else if(u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        if(v != NULL)
            v->parent = u->parent;
    }
    
    //Finding the minimum node in a subtree
public:
    struct RedBlackNode* treeMinimum(struct RedBlackNode* temp)
    {
        while(temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp;
    }
    
    //Updating the value of a node
public:
    void update(int header, int key1, int val)
    {
        int newValue = val + 1;
        int newKey = key1;
        struct RedBlackNode* temp = updateNode(treeArray[header].root, key1);
        deleteNode(header,treeArray[header].root, temp);
        insert(header, newKey, newValue);
    }
    
public:
    struct RedBlackNode* updateNode(struct RedBlackNode* header, int key)
    {
        struct RedBlackNode* x =  NULL;
        if(header != NULL)
        {
            if(header->key == key)
            {
                x = header;
                return header;
            }
            x = updateNode(header->left, key);
            if (x == NULL)
                x = updateNode(header->right, key);
            if(x != NULL)
                return x;
        }
        return NULL;
    }
    
    //Checking whether the key is present in the tree
public:
    bool containsKey(struct RedBlackNode* header, int key)
    {
        bool x = false;
        if(header != NULL)
        {
            if(header->key == key)
            {
                x = true;
                return true;
            }
            x = containsKey(header->left, key);
            if (x == false)
                x = containsKey(header->right, key);
            if(x != false)
                return x;
        }
        return false;
    }
    
    //Getting the value of a node
public:
    int getValue(struct RedBlackNode* header, int key)
    {
        int x = 0;
        if(header != NULL)
        {
            if(header->key == key)
            {
                x = header->value;
                return header->value;
            }
            x = getValue(header->left, key);
            if (x == 0)
                x = getValue(header->right, key);
            if(x != 0)
                return x;
        }
        return 0;
    }
    
};
