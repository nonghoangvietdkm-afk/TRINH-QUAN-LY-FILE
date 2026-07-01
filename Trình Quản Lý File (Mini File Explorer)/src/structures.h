#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Cấu trúc Node kết hợp N-ary Tree và Linked List (Child-Sibling representation)
struct Node {
    string name;
    bool isFolder;
    int size;
    Node* parent;
    Node* firstChild;  // Con trỏ tới con đầu tiên
    Node* nextSibling; // Con trỏ tới anh em tiếp theo (Linked List)

    Node(string n, bool folder, int s = 0)
        : name(n), isFolder(folder), size(s), parent(nullptr), firstChild(nullptr), nextSibling(nullptr) {
    }
};

class FileExplorer {
private:
    Node* root;
    Node* current;
    stack<Node*> historyBack;
    stack<Node*> historyForward;

    void printTreeRec(Node* node, string prefix, bool isLast);
    void clearTree(Node* node);
    int calculateSizeRec(Node* node);
    void saveRec(Node* node, ofstream& out, int depth);

public:
    FileExplorer();
    ~FileExplorer();

    void pwd();
    void ls();
    void mkdir(string name);
    void touch(string name, int size);
    void rm(string name);
    void renameNode(string oldName, string newName);
    void cd(string name);
    void back();
    void forward();
    void searchBFS(string name);
    void tree();
    void totalSize();
    void saveToFile(string filename);
    void loadFromFile(string filename);

    // Helper cho quá trình test
    string getCurrentName() { return current->name; }
};

#endif
