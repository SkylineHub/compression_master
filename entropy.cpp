#include <ostream>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <thread>

#include "node.h"

using namespace std;

void calculateEntropy(Node * root, int k, double *entropy, long size){
    for (long j = 0; j < root->child.size(); j++) {
        if (root->child[j]->freq != root->freq) {
            double p;
            if (root->isLast) {
                p = (double) root->child[j]->freq / ((double) root->freq - 1.0);
            } else {
                p = (double) root->child[j]->freq / (double) root->freq;
            }
            double x = (double) root->child[j]->freq / (size-k);

            entropy[k] -= x * log2(p);
        }
        if(k+1 != 6){
            calculateEntropy(root->child[j], k+1, entropy, size);
        }
    }
}

float getKthEntropy(Node * root, int k, long size) {
    if(k < 1 || k > 6) {
        cout << "Mimo rozsah!" << endl;
        return 0;
    }
    k = k - 1;
    int newK = 0;

    double entropy[6];

    for (int i = 0; i < 6; i++) {
        entropy[i] = 0;
    }

    for (int i = 0; i < root->child.size(); i++) {
        calculateEntropy(root->child[i], newK, ref(entropy), size);
    }

    for (int i = 0; i < 6; i++) {
        cout << "K: " << i + 1 << endl;
        cout << "Entropy: " << entropy[i] << endl;
    }

    return entropy[k];
}

float calculateZeroOrderEntropy(Node * root, streamsize size) {
    float entropy = 0;
    for (int i = 0; i < root->child.size(); i++) {
        float x = (float)root->child[i]->freq/(float)size;
        entropy -= x * log2(x);
    }

    return entropy;
}

void addNodes(Node *root, char a, char b, char c, char d, char e, char f, char g, streamsize size, long i) {
    if (i < size - 7) {
        addNode(root, a, b, c, d, e, f, g);
        return;
    }
    if (i == size - 7) {
        addLastNode(root, a, b, c, d, e, f, g);
        return;
    }
    if (i == size - 6) {
        addNode(root, a, b, c, d, e, f);
        return;
    }
    if (i == size - 5) {
        addNode(root, a, b, c, d, e);
        return;
    }
    if (i == size - 4) {
        addNode(root, a, b, c, d);
        return;
    }
    if (i == size - 3) {
        addNode(root, a, b, c);
        return;
    }
    if (i == size - 2) {
        addNode(root, a, b);
        return;
    }
    if (i == size - 1) {
        addNode(root, a);
        return;
    }
}

int setLineType(char a, char b, char c, char d) {
    if (a == '0') {
        return 1;
    }
    if (a == '1') {
        return 2;
    }
    if (a == 'Q' && b == 'X' && c == '1' && d == '1') {
        return 3;
    }
    if (a == 'Q' && b == 'X' && c == '1' && d == '2') {
        return 4;
    }
    if (a == '#') {
        return 0;
    }
}

long* getSizes(ifstream* file) {
    long* sizes = new long[6]; //0 - root, 1 - header, 2 - first line, 3 - second line, 4 - third line, 5 - forth line

    for(int i = 0; i < 6; i++) {
        sizes[i] = 0;
    }

    string line;
    while(getline(*file, line)) {
        if (line[0] == '0') {
            sizes[2] += line.length() + 1;
            continue;
        }
        if (line[0] == '1') {
            sizes[3] += line.length() + 1;
            continue;
        }
        if (line[0] == 'Q' && line[1] == 'X' && line[2] == '1' && line[3] == '1') {
            sizes[4] += line.length() + 1;
            continue;
        }
        if (line[0] == 'Q' && line[1] == 'X' && line[2] == '1' && line[3] == '2') {
            sizes[5]  += line.length() + 1;
            continue;
        }
        if (line[0] == '#') {
            sizes[1] += line.length()+1;
            continue;
        }
        cout << "Error" << endl;
    }

    return sizes;
}

void setNodes(char* buffer, long size, Node* root, char a) {
    for(long i = 0; i < size; i++) {
        addNodes(root, buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4], buffer[i+5], buffer[i+6], size, i);
    }
    cout << "Done: " << a << endl;
}

void getEntropy(const string& filename) {
    ifstream file(filename, std::ios::binary | std::ios::ate);
    streamsize size = file.tellg();
    cout << size << endl;

    file.seekg(0, std::ios::beg);

    int type = 0; //header - 0, first - 1, second - 2, third - 3, forth - 4

    Node* roots = new Node[6]; //0 - root, 1 - header, 2 - first line, 3 - second line, 4 - third line, 5 - forth line
    long* counter = new long[6]; //0 - root, 1 - header, 2 - first line, 3 - second line, 4 - third line, 5 - forth line

    for(int i = 0; i < 6; i++) {
        roots[i] = *newNode('|');
        counter[i] = 0;
    }
    cout << "Getting sizes" << endl;
    long* sizes = getSizes(&file);
    cout << "Getting sizes done" << endl;

    char* buffer = new char[size];
    char* header = new char[sizes[1]];
    char* first = new char[sizes[2]];
    char* second = new char[sizes[3]];
    char* third = new char[sizes[4]];
    char* forth = new char[sizes[5]];

    cout << "Allocation done" << endl;

    file.clear();
    file.seekg(0, std::ios::beg);

    cout << "Setting done" << endl;

    if(file.read(buffer, size)) {
        cout << "Reading done" << endl;
        for (long i = 0; i < size; i++) {
            addNode(&roots[0], buffer[i]);

            if(buffer[i] == '\n') {
                type = setLineType(buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4]);
            }

            switch (type) {
                case 0:
                    header[counter[1]] = buffer[i];
                    counter[1]++;
                    break;
                case 1:
                    first[counter[2]] = buffer[i];
                    counter[2]++;
                    break;
                case 2:
                    second[counter[3]] = buffer[i];
                    counter[3]++;
                    break;
                case 3:
                    third[counter[4]] = buffer[i];
                    counter[4]++;
                    break;
                case 4:
                    forth[counter[5]] = buffer[i];
                    counter[5]++;
                    break;
            }
        }

        cout << "Loop done" << endl;

        delete[] counter;
        delete[] buffer;

        cout << "Getting buffers done" << endl;

        thread th1(setNodes, header, sizes[1], &roots[1], '0');
        thread th2(setNodes, first, sizes[2], &roots[2], '1');
        thread th3(setNodes, second, sizes[3], &roots[3], '2');
        thread th4(setNodes, third, sizes[4], &roots[4], '3');
        thread th5(setNodes, forth, sizes[5], &roots[5], '4');
        th1.join();
        th2.join();
        th3.join();
        th4.join();
        th5.join();
    }

    cout << "Tree completed." << endl;
    //printTree(&roots[5]);
    int k = 3;
    cout << "Header" << endl;
    float entropyHeader = getKthEntropy(&roots[1], k, sizes[1]);
    cout << "First" << endl;
    float entropyFirst = getKthEntropy(&roots[2], k, sizes[2]);
    cout << "Second" << endl;
    float entropySecond = getKthEntropy(&roots[3], k, sizes[3]);
    cout << "Third" << endl;
    float entropyThird = getKthEntropy(&roots[4], k, sizes[4]);
    cout << "Forth" << endl;
    float entropyForth = getKthEntropy(&roots[5], k, sizes[5]);
    cout << "Kth entropy completed." << endl;
    float entropy = calculateZeroOrderEntropy(&roots[0], size);
    cout << "Zero order entropy: " << entropy << endl;

    delete[] sizes;
    delete[] header;
    delete[] first;
    delete[] second;
    delete[] third;
    delete[] forth;
}