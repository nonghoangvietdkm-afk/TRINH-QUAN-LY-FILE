#include "structures.h"

// Hàm khởi tạo (Constructor): Chạy đầu tiên khi tạo đối tượng FileExplorer
FileExplorer::FileExplorer() {
    // Tạo ra thư mục gốc tên là "root", là thư mục (true), dung lượng bằng 0
    root = new Node("root", true, 0);
    // Ban đầu, đặt vị trí đứng hiện tại (current) chính là thư mục gốc root
    current = root;
}

// Hàm hủy (Destructor): Tự động chạy khi chương trình kết thúc để giải phóng bộ nhớ
FileExplorer::~FileExplorer() {
    // Gọi hàm clearTree để xóa toàn bộ các nút tính từ gốc root tránh rò rỉ bộ nhớ
    clearTree(root);
}

// Hàm đệ quy để xóa toàn bộ cây
void FileExplorer::clearTree(Node* node) {
    // Nếu nút rỗng (không tồn tại) thì dừng lại không làm gì cả
    if (!node) return;
    
    // Lấy ra đứa con đầu tiên của nút hiện tại
    Node* child = node->firstChild;
    // Vòng lặp duyệt qua tất cả các con (các anh em nằm cùng hàng)
    while (child) {
        // Lưu lại địa chỉ của đứa em kế tiếp trước khi xóa đứa con hiện tại
        Node* next = child->nextSibling;
        // Gọi đệ quy để xóa toàn bộ nhánh con bên dưới đứa con này
        clearTree(child);
        // Chuyển sang đứa em kế tiếp để tiếp tục vòng lặp
        child = next;
    }
    // Sau khi các con đã bị xóa sạch, tiến hành xóa chính nút hiện tại khỏi bộ nhớ
    delete node;
}

// Hàm in ra đường dẫn từ thư mục gốc đến vị trí hiện tại (pwd - Print Working Directory)
void FileExplorer::pwd() {
    // Chuỗi rỗng để lưu đường dẫn kết quả
    string path = "";
    // Dùng một con trỏ tạm bắt đầu từ vị trí thư mục đang đứng (current)
    Node* temp = current;
    
    // Vòng lặp đi ngược lên trên cho đến khi vượt qua cả thư mục gốc (temp thành nullptr)
    while (temp != nullptr) {
        // Nối thêm tên thư mục hiện tại vào phía trước chuỗi path (ví dụ: "/docs" + path)
        path = "/" + temp->name + path;
        // Di chuyển con trỏ tạm lên thư mục cha của nó
        temp = temp->parent;
    }
    // In đường dẫn hoàn chỉnh ra màn hình
    cout << "Current Path: " << path << endl;
}

// Hàm liệt kê danh sách tệp tin và thư mục con bên trong vị trí hiện tại (ls - List)
void FileExplorer::ls() {
    // Lấy đứa con đầu tiên của thư mục hiện tại để bắt đầu duyệt
    Node* temp = current->firstChild;
    // Nếu không có đứa con nào (temp bằng nullptr) thì báo thư mục trống
    if (!temp) {
        cout << "(Empty)" << endl;
        return;
    }
    // Vòng lặp duyệt qua danh sách liên kết các con nằm cùng hàng (anh em)
    while (temp) {
        // Nếu nút này là thư mục (isFolder == true) thì in chữ [DIR] kèm tên
        if (temp->isFolder) cout << "[DIR]  " << temp->name << endl;
        // Nếu là tệp tin thì in chữ [FILE] kèm tên và dung lượng bytes
        else cout << "[FILE] " << temp->name << " (" << temp->size << " bytes)" << endl;
        // Chuyển sang đứa em kế tiếp trong danh sách
        temp = temp->nextSibling;
    }
}

// Hàm tạo thư mục mới (mkdir - Make Directory)
void FileExplorer::mkdir(string name) {
    // Cấp phát vùng nhớ cho một nút mới: đặt tên, định nghĩa là thư mục (true), size = 0
    Node* newNode = new Node(name, true, 0);
    // Đặt thư mục hiện tại (current) làm cha của thư mục mới tạo
    newNode->parent = current;
    
    // Đưa nút mới vào đầu danh sách con bằng cách cho "em" của nó trỏ tới con đầu cũ
    newNode->nextSibling = current->firstChild;
    // Cập nhật lại: nút mới này chính thức trở thành con đầu tiên của thư mục hiện tại
    current->firstChild = newNode;
    // In thông báo tạo thư mục thành công
    cout << "Folder created: " << name << endl;
}

// Hàm tạo tệp tin mới (touch)
void FileExplorer::touch(string name, int size) {
    // Cấp phát nút mới: đặt tên, định nghĩa là file (false), truyền dung lượng size vào
    Node* newNode = new Node(name, false, size);
    // Đặt thư mục hiện tại làm cha của file mới này
    newNode->parent = current;
    
    // Kỹ thuật chèn vào đầu danh sách liên kết: "em" của file mới trỏ tới con đầu cũ
    newNode->nextSibling = current->firstChild;
    // Cập nhật file mới này trở thành con đầu tiên của thư mục hiện tại
    current->firstChild = newNode;
    // In thông báo tạo tệp tin thành công
    cout << "File created: " << name << endl;
}

// Hàm xóa thư mục hoặc tệp tin (rm - Remove)
void FileExplorer::rm(string name) {
    // Con trỏ temp xuất phát từ đứa con đầu tiên để đi tìm nút cần xóa
    Node* temp = current->firstChild;
    // Con trỏ prev dùng để lưu nút đứng ngay trước temp (phục vụ việc nối lại liên kết)
    Node* prev = nullptr;

    // Vòng lặp chạy tìm nút: dừng lại khi hết danh sách hoặc tìm thấy nút trùng tên
    while (temp != nullptr && temp->name != name) {
        // Lưu nút hiện tại vào prev trước khi bước tiếp
        prev = temp;
        // Chuyển temp sang nút kế tiếp
        temp = temp->nextSibling;
    }

    // Nếu duyệt hết danh sách mà temp vẫn bằng nullptr nghĩa là không tìm thấy tên cần xóa
    if (temp == nullptr) {
        cout << "Error: '" << name << "' not found." << endl;
        return;
    }

    // Nếu nút cần xóa nằm ngay đầu danh sách (prev vẫn bằng nullptr)
    if (prev == nullptr) current->firstChild = temp->nextSibling; // Cho con đầu trỏ thẳng tới nút tiếp theo
    // Nếu nút cần xóa nằm ở giữa hoặc cuối: nối nút đứng trước bỏ qua nút temp
    else prev->nextSibling = temp->nextSibling;

    // Gọi hàm clearTree để giải phóng vùng nhớ của nút temp và toàn bộ nhánh con của nó (nếu có)
    clearTree(temp);
    // In thông báo xóa thành công
    cout << "Deleted: " << name << endl;
}

// Hàm đổi tên file hoặc folder
void FileExplorer::renameNode(string oldName, string newName) {
    // Bắt đầu tìm từ đứa con đầu tiên của thư mục hiện tại
    Node* temp = current->firstChild;
    // Vòng lặp quét qua danh sách các con
    while (temp) {
        // Nếu thấy nút nào có tên trùng với tên cũ cần đổi
        if (temp->name == oldName) {
            // Thay đổi biến name của nút đó thành tên mới
            temp->name = newName;
            cout << "Renamed '" << oldName << "' to '" << newName << "'" << endl;
            return; // Xong việc thì kết thúc hàm luôn
        }
        // Nếu không trùng thì chuyển sang nút tiếp theo
        temp = temp->nextSibling;
    }
    // Nếu chạy hết vòng lặp mà không return chứng tỏ không tìm thấy tên cũ
    cout << "Error: '" << oldName << "' not found." << endl;
}

// Hàm chuyển đổi thư mục (cd - Change Directory)
void FileExplorer::cd(string name) {
    // Trường hợp lệnh "cd .." (quay lại thư mục cha)
    if (name == "..") {
        // Nếu thư mục hiện tại có thư mục cha (tức là không phải đang ở root)
        if (current->parent != nullptr) {
            // Đẩy thư mục hiện tại vào ngăn xếp Lùi (historyBack) trước khi đi
            historyBack.push(current);
            // Xóa sạch ngăn xếp Tiến (historyForward) vì lịch sử đã rẽ sang nhánh mới
            while (!historyForward.empty()) historyForward.pop();
            // Cập nhật vị trí hiện tại nhảy lên thư mục cha
            current = current->parent;
        }
        return; // Kết thúc hàm
    }

    // Trường hợp "cd + tên_thư_mục" (đi vào trong một thư mục con)
    Node* temp = current->firstChild;
    // Vòng lặp tìm thư mục con có tên trùng khớp
    while (temp) {
        // Điều kiện: Tên phải trùng và nút đó phải là Thư mục (isFolder == true)
        if (temp->name == name && temp->isFolder) {
            // Đẩy vị trí hiện tại vào ngăn xếp Lùi (historyBack)
            historyBack.push(current);
            // Xóa sạch ngăn xếp Tiến (historyForward)
            while (!historyForward.empty()) historyForward.pop();
            // Cập nhật vị trí hiện tại nhảy vào thư mục con temp vừa tìm thấy
            current = temp;
            return; // Kết thúc hàm
        }
        // Chuyển sang nút kế tiếp nếu chưa khớp điều kiện
        temp = temp->nextSibling;
    }
    // Báo lỗi nếu gõ sai tên thư mục hoặc gõ nhầm tên file
    cout << "Error: Directory '" << name << "' not found." << endl;
}

// Hàm lùi lại thư mục trước đó (Lệnh Back - giống mũi tên bên trái của Windows Explorer)
void FileExplorer::back() {
    // Nếu ngăn xếp lưu lịch sử lùi đang trống thì báo lỗi không lùi được nữa
    if (historyBack.empty()) {
        cout << "No history to go back." << endl;
        return;
    }
    // Đẩy thư mục đang đứng hiện tại vào ngăn xếp Tiến (historyForward)
    historyForward.push(current);
    // Cập nhật thư mục hiện tại lấy từ đỉnh của ngăn xếp Lùi (nút gần nhất vừa đi qua)
    current = historyBack.top();
    // Xóa nút đó ra khỏi ngăn xếp Lùi sau khi đã lấy xong
    historyBack.pop();
    // Gọi hàm in đường dẫn mới ra để người dùng nhìn thấy vị trí hiện tại
    pwd();
}

// Hàm tiến về thư mục vừa lùi (Lệnh Forward - giống mũi tên bên phải của Windows Explorer)
void FileExplorer::forward() {
    // Nếu ngăn xếp lưu lịch sử tiến đang trống thì báo lỗi không tiến được
    if (historyForward.empty()) {
        cout << "No forward history." << endl;
        return;
    }
    // Đẩy thư mục hiện tại vào lại ngăn xếp Lùi (historyBack)
    historyBack.push(current);
    // Cập nhật thư mục hiện tại lấy từ đỉnh của ngăn xếp Tiến
    current = historyForward.top();
    // Xóa nút đó ra khỏi ngăn xếp Tiến
    historyForward.pop();
    // In đường dẫn hiện tại ra màn hình
    pwd();
}

// Hàm tìm kiếm tệp/thư mục trên toàn bộ hệ thống bằng thuật toán Tìm kiếm theo chiều rộng (BFS)
void FileExplorer::searchBFS(string name) {
    // Khởi tạo một Hàng đợi (Queue) chứa các con trỏ quản lý Node
    queue<Node*> q;
    // Bỏ nút gốc (root) vào hàng đợi để bắt đầu quét từ tầng cao nhất
    q.push(root);
    // Biến cờ đánh dấu, ban đầu giả định là chưa tìm thấy (false)
    bool found = false;

    // Vòng lặp chạy liên tục cho đến khi kiểm tra hết sạch các nút trong hàng đợi
    while (!q.empty()) {
        // Lấy nút nằm ở đầu hàng đợi ra xem xét
        Node* curr = q.front();
        // Xóa nút đó khỏi hàng đợi sau khi đã lấy ra
        q.pop();

        // Nếu phát hiện tên của nút này trùng khớp với tên cần tìm
        if (curr->name == name) {
            cout << "Found: ";
            Node* temp = curr;
            string path = "";
            // Thuật toán lần ngược từ nút tìm thấy lên cha của nó để xây dựng đường dẫn tuyệt đối
            while (temp) { path = "/" + temp->name + path; temp = temp->parent; }
            // In đường dẫn kèm theo loại nút đó là [DIR] hay [FILE]
            cout << path << (curr->isFolder ? " [DIR]" : " [FILE]") << endl;
            // Đổi cờ đánh dấu thành true vì đã tìm thấy ít nhất 1 kết quả
            found = true;
        }

        // Đưa tất cả các nút con trực tiếp của nút curr hiện tại vào hàng đợi để chờ quét ở tầng tiếp theo
        Node* child = curr->firstChild;
        while (child) {
            q.push(child); // Đẩy con vào queue
            child = child->nextSibling; // Chuyển sang các anh em của đứa con đó
        }
    }
    // Nếu kết thúc duyệt toàn bộ cây mà cờ found vẫn là false thì báo không tìm thấy
    if (!found) cout << "Not found: " << name << endl;
}

// Hàm đệ quy tính toán dung lượng theo thứ tự Duyệt sau (Post-order Traversal)
int FileExplorer::calculateSizeRec(Node* node) {
    // Nếu nút không tồn tại (nullptr) thì dung lượng bằng 0
    if (!node) return 0;
    // Nếu nút này là Tệp tin (không phải folder) thì trả về đúng dung lượng của file đó luôn
    if (!node->isFolder) return node->size;
    
    // Nếu là thư mục, khởi tạo biến tổng total = 0
    int total = 0;
    // Lấy đứa con đầu tiên của thư mục này
    Node* child = node->firstChild;
    // Vòng lặp đệ quy đi sâu xuống tính dung lượng của từng nhánh con bên dưới
    while (child) {
        total += calculateSizeRec(child); // Cộng dồn kết quả đệ quy của các con vào total
        child = child->nextSibling; // Chuyển sang đứa con tiếp theo cùng cấp
    }
    // Trả về tổng dung lượng của toàn bộ thư mục
    return total;
}

// Hàm giao tiếp công khai để gọi tính năng tính kích thước thư mục hiện tại
void FileExplorer::totalSize() {
    // In ra kết quả bằng cách truyền thư mục đang đứng (current) vào hàm đệ quy ở trên
    cout << "Total size of current directory: " << calculateSizeRec(current) << " bytes" << endl;
}

// Hàm đệ quy vẽ cây thư mục dưới dạng ký tự vẽ màn hình (ASCII Tree)
void FileExplorer::printTreeRec(Node* node, string prefix, bool isLast) {
    // Nếu nút rỗng thì dừng
    if (!node) return;
    // In các ký tự đường nối (prefix) kết hợp ký tự góc nhánh (└── nếu là con cuối, ├── nếu còn con phía sau) kèm tên nút
    cout << prefix << (isLast ? "└── " : "├── ") << node->name;
    // Nếu nút là file thì in thêm dung lượng dạng (150b) kế bên tên file
    if (!node->isFolder) cout << " (" << node->size << "b)";
    cout << endl; // Xuống dòng cho nút tiếp theo

    // Tiếp tục vẽ các con của nút hiện tại
    Node* child = node->firstChild;
    while (child) {
        // Gọi đệ quy: Nếu nút hiện tại là cuối cùng thì nối thêm khoảng trống "    ", ngược lại nối thanh dọc "│   "
        printTreeRec(child, prefix + (isLast ? "    " : "│   "), child->nextSibling == nullptr);
        child = child->nextSibling; // Chuyển sang nút anh em kế bên
    }
}

// Hàm giao tiếp để bắt đầu vẽ cây tính từ vị trí đang đứng hiện tại
void FileExplorer::tree() {
    // In tên của thư mục hiện tại làm gốc của sơ đồ
    cout << current->name << endl;
    // Lấy đứa con đầu tiên
    Node* child = current->firstChild;
    while (child) {
        // Truyền tham số kiểm tra xem đứa con này có phải là phần tử cuối cùng hàng không (child->nextSibling == nullptr)
        printTreeRec(child, "", child->nextSibling == nullptr);
        child = child->nextSibling;
    }
}

// Hàm đệ quy lưu cấu trúc cây ra file văn bản bằng thứ tự Duyệt trước (Pre-order Traversal)
void FileExplorer::saveRec(Node* node, ofstream& out, int depth) {
    // Nếu nút rỗng thì dừng không ghi
    if (!node) return;
    // Ghi dữ liệu của nút cha hiện tại vào file theo định dạng phẳng phân tách bằng dấu gạch đứng '|': Độ sâu|Thư mục hay không|Kích thước|Tên
    out << depth << "|" << node->isFolder << "|" << node->size << "|" << node->name << "\n";
    
    // Sau khi ghi cha, lập tức đi sâu xuống ghi các nút con trực thuộc
    Node* child = node->firstChild;
    while (child) {
        // Gọi đệ quy cho con và tăng độ sâu (depth) lên 1 đơn vị
        saveRec(child, out, depth + 1); 
        child = child->nextSibling; // Chuyển sang con tiếp theo
    }
}

// Hàm mở file và kích hoạt quá trình lưu cấu trúc cây hệ thống
void FileExplorer::saveToFile(string filename) {
    // Mở luồng ghi file luồng đầu ra (ofstream) với tên file truyền vào
    ofstream out(filename);
    // Nếu không mở được file (lỗi ổ đĩa, quyền truy cập...) thì báo lỗi và dừng
    if (!out) { cout << "Error opening file!" << endl; return; }
    // Gọi hàm đệ quy lưu bắt đầu từ gốc cao nhất (root) với độ sâu ban đầu là 0
    saveRec(root, out, 0);
    // Đóng file sau khi hoàn thành ghi dữ liệu
    out.close();
    cout << "Saved to " << filename << endl;
}

// Hàm đọc file văn bản và dựng lại toàn bộ cây thư mục vào bộ nhớ
void FileExplorer::loadFromFile(string filename) {
    // Mở luồng đọc file đầu vào (ifstream) với tên file cấu trúc đã lưu trước đó
    ifstream in(filename);
    // Nếu file không tồn tại hoặc lỗi không mở được thì báo lỗi và dừng hàm
    if (!in) { cout << "Error: File not found!" << endl; return; }

    // Xóa toàn bộ cấu trúc cây cũ đang chạy trong RAM để chuẩn bị nạp cây mới
    clearTree(root);
    // Biến dòng văn bản để đọc từng hàng một từ file
    string line;
    // Mảng động (vector) đóng vai trò theo dõi con trỏ quản lý của từng độ sâu (tầng) để biết nút nào là cha của nút nào
    vector<Node*> depthTracker; 

    // Vòng lặp đọc tịnh tiến từng dòng một cho đến hết file văn bản
    while (getline(in, line)) {
        // Dùng stringstream để bóc tách, cắt chuỗi dữ liệu dựa trên ký tự phân tách '|'
        stringstream ss(line);
        string item;
        int depth, size; bool isFolder; string name;

        // Cắt lấy đoạn đầu tiên chuyển sang số nguyên để lấy thông tin độ sâu (depth)
        getline(ss, item, '|'); depth = stoi(item);
        // Cắt đoạn tiếp theo chuyển sang số kiểu logic để lấy thông tin kiểu nút (isFolder)
        getline(ss, item, '|'); isFolder = stoi(item);
        // Cắt đoạn thứ 3 chuyển sang số nguyên để lấy thông tin kích thước (size)
        getline(ss, item, '|'); size = stoi(item);
        // Đoạn cuối cùng chính là chuỗi tên của file/folder (name)
        getline(ss, name);

        // Tạo mới một nút Node trong bộ nhớ RAM dựa trên các thông số vừa bóc tách được
        Node* n = new Node(name, isFolder, size);
        
        // Nếu độ sâu bằng 0, đây chính là nút gốc cao nhất (root)
        if (depth == 0) {
            root = n; // Gán nút mới này làm root hệ thống
            current = root; // Đặt vị trí đứng mặc định tại root luôn
            depthTracker.push_back(root); // Đẩy root vào vị trí đầu tiên của mảng theo dõi tầng (vị trí tầng 0)
        }
        // Nếu độ sâu lớn hơn 0 (là các thư mục con hoặc file nằm bên trong)
        else {
            // Nút cha của nút hiện tại chắc chắn nằm ở tầng ngay phía trên nó: (depth - 1)
            Node* parent = depthTracker[depth - 1];
            // Thiết lập con trỏ quản lý cha cho nút mới
            n->parent = parent;
            // Thực hiện chèn nút mới này vào đầu danh sách con trực thuộc của nút cha
            n->nextSibling = parent->firstChild;
            parent->firstChild = n;
            
            // Cập nhật mảng theo dõi tầng: Nếu vị trí tầng này đã tồn tại nút cũ thì ghi đè nút mới này vào đại diện cho tầng đó
            if (depthTracker.size() > depth) depthTracker[depth] = n;
            // Nếu đây là lần đầu tiên đi sâu xuống tầng này thì đẩy nút mới vào cuối mảng vector
            else depthTracker.push_back(n);
        }
    }
    // Sau khi nạp xong cây mới thành công, tiến hành xóa sạch 2 Stack lịch sử di chuyển cũ để tránh xung đột con trỏ sai lệch địa chỉ
    while (!historyBack.empty()) historyBack.pop();
    while (!historyForward.empty()) historyForward.pop();
    // In thông báo nạp cấu trúc hệ thống tệp tin hoàn thành
    cout << "Loaded from " << filename << endl;
}
