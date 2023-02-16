#include <bits/stdc++.h>
using namespace std;

#define ll long long
struct Node
{
    string data;
    Node **children;
    ll childCount;
};


void dotGenerator (Node* root)
{
    // generate dot file for graph representation
    // redirect output to a file
    freopen("output.txt", "w", stdout);


    cout << "digraph ASTVisual {\n";
    queue<Node *> queueNode;
    queueNode.push(root);

    while (!queueNode.empty())
    {
        Node *currNode = queueNode.front();       
         queueNode.pop();
        ll cC= currNode->childCount;


        for (ll i = 0; i < cC; i++)
        {

            cout << currNode->data << " -> " << currNode->children[i]->data << endl;
            queueNode.push(currNode->children[i]);
        }

    }
    cout << "  }\n";
}
