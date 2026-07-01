#ifndef STRUCTURES_H // Lệnh tiền xử lý: Kiểm tra xem file này đã được định nghĩa chưa (tránh lỗi định nghĩa trùng lặp)
#define STRUCTURES_H // Nếu chưa, tiến hành định nghĩa mã nhận diện STRUCTURES_H cho file này

#include <string>    // Khai báo thư viện sử dụng kiểu chuỗi ký tự (string) để lưu tên file/folder
#include <iostream>  // Khai báo thư viện xuất nhập dữ liệu chuẩn (cout, cin, endl)
#include <stack>     // Khai báo thư viện Ngăn xếp (Stack) để quản lý lịch sử Back/Forward
#include <queue>     // Khai báo thư viện Hàng đợi (Queue) để dùng cho thuật toán tìm kiếm BFS
#include <fstream>   // Khai báo thư viện đọc/ghi file lưu trữ dữ liệu (ifstream, ofstream)
#include <sstream>   // Khai báo thư viện xử lý chuỗi luồng (stringstream) để cắt và phân tách dòng văn bản
#include <vector>    // Khai báo thư viện Mảng động (Vector) để hỗ trợ khôi phục cây từ file văn bản

using namespace std; // Sử dụng không gian tên chuẩn để không cần gõ chữ "std::" trước string, cout, stack...

// Cấu trúc Node kết hợp Cây tổng quát (N-ary Tree) và Danh sách liên kết (Linked List)
// Mô hình biểu diễn theo cơ chế: Con đầu tiên - Anh em kế cận (Left Child - Right Sibling)
struct Node {
    string name;       // Biến lưu tên của tệp tin hoặc thư mục (ví dụ: "docs", "notes.txt")
    bool isFolder;     // Biến logic: true nếu nút này là Thư mục, false nếu nút này là Tệp tin
    int size;          // Biến lưu dung lượng của tệp tin (đơn vị bytes), nếu là thư mục ban đầu sẽ là 0
    Node* parent;      // Con trỏ quản lý, trỏ ngược lên thư mục cha chứa nút hiện tại
    Node* firstChild;  // Con trỏ trỏ đến đứa con đầu tiên nằm bên trong thư mục này
    Node* nextSibling; // Con trỏ trỏ đến nút anh em đứng ngay kế bên nó (nằm cùng hàng trong cùng thư mục cha)

    // Hàm khởi tạo nhanh một Node mới (Constructor của struct)
    Node(string n, bool folder, int s = 0)
        // Gán các giá trị truyền vào cho biến tương ứng, và mặc định đặt các con trỏ bằng nullptr (rỗng)
        : name(n), isFolder(folder), size(s), parent(nullptr), firstChild(nullptr), nextSibling(nullptr) {
    }
};



// Lớp điều khiển chính cho chương trình quản lý tập tin
class FileExplorer {
private:
    Node* root;                 // Con trỏ quản lý nút gốc cao nhất của toàn hệ thống (thư mục "root")
    Node* current;              // Con trỏ quản lý vị trí thư mục mà người dùng đang đứng làm việc hiện tại
    stack<Node*> historyBack;   // Ngăn xếp lưu lịch sử các thư mục đã đi qua, phục vụ lệnh Quay lại (Back)
    stack<Node*> historyForward;// Ngăn xếp lưu lịch sử các thư mục đã lùi, phục vụ lệnh Tiến lên (Forward)

    // Các hàm trợ giúp (Helper) mang tính chất đệ quy nội bộ bên trong class:
    void printTreeRec(Node* node, string prefix, bool isLast); // Hàm đệ quy để vẽ sơ đồ cây dạng ký tự ASCII
    void clearTree(Node* node);                                // Hàm đệ quy giải phóng toàn bộ vùng nhớ của cây
    int calculateSizeRec(Node* node);                          // Hàm đệ quy tính tổng dung lượng (Duyệt sau - Post-order)
    void saveRec(Node* node, ofstream& out, int depth);        // Hàm đệ quy lưu cây ra file văn bản (Duyệt trước - Pre-order)

public:
    FileExplorer();  // Hàm khởi tạo: Thiết lập cây, tạo thư mục root và đặt vị trí ban đầu
    ~FileExplorer(); // Hàm hủy: Tự động giải phóng toàn bộ bộ nhớ RAM của cây khi tắt chương trình

    // Các tính năng tương tác công khai với người dùng:
    void pwd();        // Hàm in đường dẫn tuyệt đối từ gốc đến thư mục hiện tại (Print Working Directory)
    void ls();         // Hàm liệt kê tất cả tệp tin và thư mục con ở vị trí hiện tại (List)
    void mkdir(string name);                  // Hàm tạo một thư mục mới (Make Directory)
    void touch(string name, int size);        // Hàm tạo một tệp tin mới đi kèm dung lượng truyền vào
    void rm(string name);                     // Hàm xóa một tệp tin hoặc thư mục con dựa theo tên (Remove)
    void renameNode(string oldName, string newName); // Hàm đổi tên tệp tin hoặc thư mục từ tên cũ sang tên mới
    void cd(string name);                     // Hàm chuyển đổi vị trí giữa các thư mục (Change Directory)
    void back();       // Hàm thực hiện quay lại thư mục trước đó bằng Stack lịch sử
    void forward();    // Hàm thực hiện tiến tới thư mục vừa bấm back bằng Stack lịch sử
    void searchBFS(string name);              // Hàm tìm kiếm tệp/thư mục trên toàn bộ hệ thống bằng thuật toán Tìm rộng
    void tree();       // Hàm gọi tính năng in sơ đồ cây trực quan ra màn hình
    void totalSize();  // Hàm gọi tính năng in tổng dung lượng tính toán của thư mục hiện tại
    void saveToFile(string filename);         // Hàm thực hiện mở luồng ghi để xuất toàn bộ cây dữ liệu ra file .txt
    void loadFromFile(string filename);       // Hàm thực hiện mở luồng đọc để nạp và dựng lại cấu trúc cây từ file .txt

    // Hàm bổ trợ công khai phục vụ riêng cho các kịch bản kiểm thử tự động
    string getCurrentName() { return current->name; } // Trả về chuỗi tên của thư mục hiện tại đang đứng
};

#endif // Kết thúc vùng biên dịch điều kiện của file tiêu đề STRUCTURES_H
