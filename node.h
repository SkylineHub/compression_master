struct Node
{
    char key;
    int freq = 1;
    Node *parent = nullptr;
    std::vector<Node *>child;
    bool isLast = false;
};

Node *newNode(char key);

void addNode(Node *root, char a);
void addNode(Node *root, char a, char b);
void addNode(Node *root, char a, char b, char c);
void addNode(Node *root, char a, char b, char c, char d);
void addNode(Node *root, char a, char b, char c, char d, char e);
void addNode(Node *root, char a, char b, char c, char d, char e, char f);
void addNode(Node *root, char a, char b, char c, char d, char e, char f, char g);
void addLastNode(Node *root, char a, char b, char c, char d, char e, char f, char g);

void printTree(Node * root);
