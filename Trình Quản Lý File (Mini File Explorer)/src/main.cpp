#include "structures.h"

void displayMenu() {
    cout << "\n=== MINI FILE EXPLORER ===" << endl;
    cout << "1. ls       - List contents" << endl;
    cout << "2. pwd      - Print working directory" << endl;
    cout << "3. tree     - Print ASCII tree" << endl;
    cout << "4. cd       - Change directory" << endl;
    cout << "5. mkdir    - Create folder" << endl;
    cout << "6. touch    - Create file" << endl;
    cout << "7. rm       - Delete file/folder" << endl;
    cout << "8. rename   - Rename file/folder" << endl;
    cout << "9. back     - Go back (History)" << endl;
    cout << "10. forward - Go forward (History)" << endl;
    cout << "11. search  - Find file/folder by name (BFS)" << endl;
    cout << "12. size    - Calculate total size (Post-order)" << endl;
    cout << "13. save    - Save tree to TXT" << endl;
    cout << "14. load    - Load tree from TXT" << endl;
    cout << "0. exit     - Quit application" << endl;
    cout << "==========================" << endl;
    cout << "Enter command number: ";
}

int main() {
    FileExplorer fe;
    int choice;
    string input1, input2;
    int size;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: fe.ls(); break;
        case 2: fe.pwd(); break;
        case 3: fe.tree(); break;
        case 4:
            cout << "Enter folder name (or '..'): "; cin >> input1;
            fe.cd(input1); break;
        case 5:
            cout << "Enter folder name: "; cin >> input1;
            fe.mkdir(input1); break;
        case 6:
            cout << "Enter file name: "; cin >> input1;
            cout << "Enter file size: "; cin >> size;
            fe.touch(input1, size); break;
        case 7:
            cout << "Enter name to delete: "; cin >> input1;
            fe.rm(input1); break;
        case 8:
            cout << "Old name: "; cin >> input1;
            cout << "New name: "; cin >> input2;
            fe.renameNode(input1, input2); break;
        case 9: fe.back(); break;
        case 10: fe.forward(); break;
        case 11:
            cout << "Enter name to search: "; cin >> input1;
            fe.searchBFS(input1); break;
        case 12: fe.totalSize(); break;
        case 13:
            cout << "Filename to save (e.g., data.txt): "; cin >> input1;
            fe.saveToFile(input1); break;
        case 14:
            cout << "Filename to load: "; cin >> input1;
            fe.loadFromFile(input1); break;
        case 0: return 0;
        default: cout << "Invalid choice." << endl;
        }
    }
    return 0;
}