#include <iostream>
#include <vector>
#include <queue>

#include "node.h"

using namespace std;

Node *newNode(char key)
{
    Node *node = new Node;
    node->key = key;
    return node;
}

Node *newNode(char key, Node *parent, bool isLast)
{
    Node *node = new Node;
    node->key = key;
    node->parent = parent;
    node->isLast = isLast;
    return node;
}

Node* addChild(Node *root, char x, bool isLast) {
    int i;
    for (i = 0; i < root->child.size(); i++) {
        if (root->child[i]->key == x) {
            root->child[i]->freq += 1;
            root->child[i]->isLast = isLast;
            return root->child[i];
        }
    }
    (root->child).push_back(newNode(x, root, isLast));
    return root->child[i];
}

void addNode(Node *root, char a) {
    addChild(root, a, true);
}

void addNode(Node *root, char a, char b) {
    Node* i = addChild(root, a, false);
    addChild(i, b, true);
    cout << "Last 1" << endl;
}

void addNode(Node *root, char a, char b, char c) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    addChild(j, c, true);
    cout << "Last 2" << endl;
}

void addNode(Node *root, char a, char b, char c, char d) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    Node* l = addChild(j, c, false);
    addChild(l, d, true);
    cout << "Last 3" << endl;
}

void addNode(Node *root, char a, char b, char c, char d, char e) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    Node* l = addChild(j, c, false);
    Node* p = addChild(l, d, false);
    addChild(p, e, true);
    cout << "Last 4" << endl;
}

void addNode(Node *root, char a, char b, char c, char d, char e, char f) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    Node* l = addChild(j, c, false);
    Node* p = addChild(l, d, false);
    Node* q = addChild(p, e, false);
    addChild(q, f, true);
    cout << "Last 6" << endl;
}

void addNode(Node *root, char a, char b, char c, char d, char e, char f, char g) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    Node* l = addChild(j, c, false);
    Node* p = addChild(l, d, false);
    Node* q = addChild(p, e, false);
    Node* m = addChild(q, f, false);
    addChild(m, g, false);
}

void addLastNode(Node *root, char a, char b, char c, char d, char e, char f, char g) {
    Node* i = addChild(root, a, false);
    Node* j = addChild(i, b, false);
    Node* l = addChild(j, c, false);
    Node* p = addChild(l, d, false);
    Node* q = addChild(p, e, false);
    Node* m = addChild(q, f, false);
    addChild(m, g, true);
    cout << "Last 7" << endl;
}

void printTree(Node * root)
{
    if (root==nullptr)
        return;

    queue<Node *> q;
    q.push(root);
    bool first = true;
    while (!q.empty())
    {
        long n = q.size();

        while (n > 0)
        {
            Node * p = q.front();
            q.pop();
            if(!first) {
                cout << p->key << "(" << (p->freq) << ")" << "(" << (p->isLast) << ")" << " -> (" << (p->parent->key) << ") | ";
            }
            first = false;
            for (auto & i : p->child)
                q.push(i);
            n--;
        }
        cout << endl;
    }
}