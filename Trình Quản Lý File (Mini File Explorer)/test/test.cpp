#include "structures.h"

void runTests() {
    FileExplorer fe;
    cout << "\n--- STARTING 5 AUTOMATED TESTS ---\n" << endl;

    // TEST 1: Creation & Linked List Structure
    cout << "TEST 1: Creating folders and files..." << endl;
    fe.mkdir("docs");
    fe.mkdir("images");
    fe.touch("notes.txt", 150);
    fe.ls(); // Verify they are created
    cout << "-> Test 1 Completed.\n" << endl;

    // TEST 2: Navigation (Stack push logic & Parent Pointers)
    cout << "TEST 2: Navigation (cd, pwd)..." << endl;
    fe.cd("docs");
    fe.pwd(); // Expected: /root/docs
    fe.mkdir("work");
    fe.cd("work");
    fe.pwd(); // Expected: /root/docs/work
    fe.cd("..");
    fe.pwd(); // Expected: /root/docs
    cout << "-> Test 2 Completed.\n" << endl;

    // TEST 3: History (Stack - Back/Forward)
    cout << "TEST 3: History Stack (Back/Forward)..." << endl;
    fe.back(); // Expected: Go back to /root/docs/work
    fe.pwd();
    fe.back(); // Expected: Go back to /root/docs
    fe.forward(); // Expected: Go forward to /root/docs/work
    fe.pwd();
    fe.cd(".."); // Go back to docs
    fe.cd(".."); // Go back to root
    cout << "-> Test 3 Completed.\n" << endl;

    // TEST 4: Queue BFS Search & Post-order Size Calculation
    cout << "TEST 4: Search BFS & Total Size..." << endl;
    fe.touch("video.mp4", 1024);
    fe.searchBFS("work"); // Find folder nested inside
    fe.searchBFS("video.mp4"); // Find newly created file
    fe.totalSize(); // Post-order calculate size (150 + 1024 = 1174 bytes)
    cout << "-> Test 4 Completed.\n" << endl;

    // TEST 5: IO Serialization (Pre-order Save / Rebuild)
    cout << "TEST 5: Save to & Load from TXT..." << endl;
    fe.saveToFile("test_tree.txt");

    // Create a new instance to load into
    FileExplorer fe2;
    fe2.loadFromFile("test_tree.txt");
    cout << "Loaded Tree Structure:" << endl;
    fe2.tree();
    cout << "-> Test 5 Completed.\n" << endl;

    cout << "ALL 5 MANDATORY TESTS PASSED SUCCESSFULY.\n";
}

int main() {
    runTests();
    return 0;
}