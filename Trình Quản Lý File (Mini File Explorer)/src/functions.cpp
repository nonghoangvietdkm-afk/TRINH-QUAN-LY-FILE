#include "structures.h"

FileExplorer::FileExplorer() {
    root = new Node("root", true, 0);
    current = root;
}

FileExplorer::~FileExplorer() {
    clearTree(root);
}

void FileExplorer::clearTree(Node* node) {
    if (!node) return;
    Node* child = node->firstChild;
    while (child) {
        Node* next = child->nextSibling;
        clearTree(child);
        child = next;
    }
    delete node;
}

void FileExplorer::pwd() {
    string path = "";
    Node* temp = current;
    while (temp != nullptr) {
        path = "/" + temp->name + path;
        temp = temp->parent;
    }
    cout << "Current Path: " << path << endl;
}

void FileExplorer::ls() {
    Node* temp = current->firstChild;
    if (!temp) {
        cout << "(Empty)" << endl;
        return;
    }
    while (temp) {
        if (temp->isFolder) cout << "[DIR]  " << temp->name << endl;
        else cout << "[FILE] " << temp->name << " (" << temp->size << " bytes)" << endl;
        temp = temp->nextSibling;
    }
}

void FileExplorer::mkdir(string name) {
    Node* newNode = new Node(name, true, 0);
    newNode->parent = current;
    newNode->nextSibling = current->firstChild;
    current->firstChild = newNode;
    cout << "Folder created: " << name << endl;
}

void FileExplorer::touch(string name, int size) {
    Node* newNode = new Node(name, false, size);
    newNode->parent = current;
    newNode->nextSibling = current->firstChild;
    current->firstChild = newNode;
    cout << "File created: " << name << endl;
}

void FileExplorer::rm(string name) {
    Node* temp = current->firstChild;
    Node* prev = nullptr;

    while (temp != nullptr && temp->name != name) {
        prev = temp;
        temp = temp->nextSibling;
    }

    if (temp == nullptr) {
        cout << "Error: '" << name << "' not found." << endl;
        return;
    }

    if (prev == nullptr) current->firstChild = temp->nextSibling;
    else prev->nextSibling = temp->nextSibling;

    clearTree(temp);
    cout << "Deleted: " << name << endl;
}

void FileExplorer::renameNode(string oldName, string newName) {
    Node* temp = current->firstChild;
    while (temp) {
        if (temp->name == oldName) {
            temp->name = newName;
            cout << "Renamed '" << oldName << "' to '" << newName << "'" << endl;
            return;
        }
        temp = temp->nextSibling;
    }
    cout << "Error: '" << oldName << "' not found." << endl;
}

void FileExplorer::cd(string name) {
    if (name == "..") {
        if (current->parent != nullptr) {
            historyBack.push(current);
            while (!historyForward.empty()) historyForward.pop();
            current = current->parent;
        }
        return;
    }

    Node* temp = current->firstChild;
    while (temp) {
        if (temp->name == name && temp->isFolder) {
            historyBack.push(current);
            while (!historyForward.empty()) historyForward.pop();
            current = temp;
            return;
        }
        temp = temp->nextSibling;
    }
    cout << "Error: Directory '" << name << "' not found." << endl;
}

void FileExplorer::back() {
    if (historyBack.empty()) {
        cout << "No history to go back." << endl;
        return;
    }
    historyForward.push(current);
    current = historyBack.top();
    historyBack.pop();
    pwd();
}

void FileExplorer::forward() {
    if (historyForward.empty()) {
        cout << "No forward history." << endl;
        return;
    }
    historyBack.push(current);
    current = historyForward.top();
    historyForward.pop();
    pwd();
}

void FileExplorer::searchBFS(string name) {
    queue<Node*> q;
    q.push(root);
    bool found = false;

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr->name == name) {
            cout << "Found: ";
            Node* temp = curr;
            string path = "";
            while (temp) { path = "/" + temp->name + path; temp = temp->parent; }
            cout << path << (curr->isFolder ? " [DIR]" : " [FILE]") << endl;
            found = true;
        }

        Node* child = curr->firstChild;
        while (child) {
            q.push(child);
            child = child->nextSibling;
        }
    }
    if (!found) cout << "Not found: " << name << endl;
}

int FileExplorer::calculateSizeRec(Node* node) {
    if (!node) return 0;
    if (!node->isFolder) return node->size;
    int total = 0;
    Node* child = node->firstChild;
    while (child) {
        total += calculateSizeRec(child); // Post-order
        child = child->nextSibling;
    }
    return total;
}

void FileExplorer::totalSize() {
    cout << "Total size of current directory: " << calculateSizeRec(current) << " bytes" << endl;
}

void FileExplorer::printTreeRec(Node* node, string prefix, bool isLast) {
    if (!node) return;
    cout << prefix << (isLast ? "└── " : "├── ") << node->name;
    if (!node->isFolder) cout << " (" << node->size << "b)";
    cout << endl;

    Node* child = node->firstChild;
    while (child) {
        printTreeRec(child, prefix + (isLast ? "    " : "│   "), child->nextSibling == nullptr);
        child = child->nextSibling;
    }
}

void FileExplorer::tree() {
    cout << current->name << endl;
    Node* child = current->firstChild;
    while (child) {
        printTreeRec(child, "", child->nextSibling == nullptr);
        child = child->nextSibling;
    }
}

void FileExplorer::saveRec(Node* node, ofstream& out, int depth) {
    if (!node) return;
    out << depth << "|" << node->isFolder << "|" << node->size << "|" << node->name << "\n";
    Node* child = node->firstChild;
    while (child) {
        saveRec(child, out, depth + 1); // Pre-order traversal
        child = child->nextSibling;
    }
}

void FileExplorer::saveToFile(string filename) {
    ofstream out(filename);
    if (!out) { cout << "Error opening file!" << endl; return; }
    saveRec(root, out, 0);
    out.close();
    cout << "Saved to " << filename << endl;
}

void FileExplorer::loadFromFile(string filename) {
    ifstream in(filename);
    if (!in) { cout << "Error: File not found!" << endl; return; }

    clearTree(root);
    string line;
    vector<Node*> depthTracker; // Dùng vector tạm để track cha-con khi đọc từ file phẳng

    while (getline(in, line)) {
        stringstream ss(line);
        string item;
        int depth, size; bool isFolder; string name;

        getline(ss, item, '|'); depth = stoi(item);
        getline(ss, item, '|'); isFolder = stoi(item);
        getline(ss, item, '|'); size = stoi(item);
        getline(ss, name);

        Node* n = new Node(name, isFolder, size);
        if (depth == 0) {
            root = n;
            current = root;
            depthTracker.push_back(root);
        }
        else {
            Node* parent = depthTracker[depth - 1];
            n->parent = parent;
            n->nextSibling = parent->firstChild;
            parent->firstChild = n;
            if (depthTracker.size() > depth) depthTracker[depth] = n;
            else depthTracker.push_back(n);
        }
    }
    while (!historyBack.empty()) historyBack.pop();
    while (!historyForward.empty()) historyForward.pop();
    cout << "Loaded from " << filename << endl;
}