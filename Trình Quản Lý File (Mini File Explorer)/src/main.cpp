#include "structures.h" // Nhúng tệp tiêu đề chứa cấu trúc dữ liệu Node và lớp FileExplorer vào để sử dụng

// Hàm hiển thị bảng menu chức năng ra màn hình cho người dùng lựa chọn
void displayMenu() {
    cout << "\n=== MINI FILE EXPLORER ===" << endl; // In tiêu đề chương trình
    cout << "1. ls       - List contents" << endl; // Menu lựa chọn 1: Liệt kê danh sách file/folder con
    cout << "2. pwd      - Print working directory" << endl; // Menu lựa chọn 2: In đường dẫn hiện tại
    cout << "3. tree     - Print ASCII tree" << endl; // Menu lựa chọn 3: Vẽ sơ đồ cây thư mục trực quan
    cout << "4. cd       - Change directory" << endl; // Menu lựa chọn 4: Di chuyển thư mục
    cout << "5. mkdir    - Create folder" << endl; // Menu lựa chọn 5: Tạo thư mục mới
    cout << "6. touch    - Create file" << endl; // Menu lựa chọn 6: Tạo tệp tin mới
    cout << "7. rm       - Delete file/folder" << endl; // Menu lựa chọn 7: Xóa file hoặc folder
    cout << "8. rename   - Rename file/folder" << endl; // Menu lựa chọn 8: Đổi tên file hoặc folder
    cout << "9. back     - Go back (History)" << endl; // Menu lựa chọn 9: Quay lại thư mục trước (Lùi)
    cout << "10. forward - Go forward (History)" << endl; // Menu lựa chọn 10: Tiến về thư mục vừa lùi
    cout << "11. search  - Find file/folder by name (BFS)" << endl; // Menu lựa chọn 11: Tìm kiếm bằng thuật toán tìm rộng
    cout << "12. size    - Calculate total size (Post-order)" << endl; // Menu lựa chọn 12: Tính tổng kích thước bằng duyệt sau
    cout << "13. save    - Save tree to TXT" << endl; // Menu lựa chọn 13: Lưu dữ liệu ra file văn bản .txt
    cout << "14. load    - Load tree from TXT" << endl; // Menu lựa chọn 14: Đọc dữ liệu từ file văn bản .txt
    cout << "0. exit     - Quit application" << endl; // Menu lựa chọn 0: Thoát ứng dụng
    cout << "==========================" << endl; // In đường kẻ phân cách bảng menu
    cout << "Enter command number: "; // In thông báo nhắc người dùng nhập số lệnh muốn chọn
}

// Hàm main - Điểm bắt đầu khởi chạy của toàn bộ chương trình C++
int main() {
    FileExplorer fe; // Khởi tạo một đối tượng fe thuộc lớp FileExplorer (kích hoạt Constructor tạo gốc root)
    int choice; // Biến lưu số lệnh mà người dùng chọn nhập từ bàn phím
    string input1, input2; // Hai biến chuỗi tạm để nhận dữ liệu nhập vào (như tên file, tên folder)
    int size; // Biến nguyên tạm để nhận dữ liệu kích thước tệp tin khi người dùng tạo file

    // Vòng lặp vô hạn để chương trình chạy liên tục cho đến khi người dùng chủ động chọn thoát (nhập số 0)
    while (true) {
        displayMenu(); // Gọi hàm hiển thị menu chức năng ở trên ra màn hình
        cin >> choice; // Đợi và nhận số lệnh do người dùng nhập vào biến choice

        // Cấu trúc rẽ nhánh để xử lý hành động tương ứng với số lệnh người dùng đã chọn
        switch (choice) {
        case 1: 
            fe.ls(); // Nếu chọn 1, gọi hàm ls() để xem danh sách file/folder tại vị trí hiện tại
            break;   // Thoát khỏi khối lệnh switch để quay lại vòng lặp while
        case 2: 
            fe.pwd(); // Nếu chọn 2, gọi hàm pwd() để in ra đường dẫn tuyệt đối của thư mục đang đứng
            break;
        case 3: 
            fe.tree(); // Nếu chọn 3, gọi hàm tree() để in sơ đồ đồ họa cây thư mục dạng văn bản ASCII
            break;
        case 4:
            cout << "Enter folder name (or '..'): "; cin >> input1; // Nhắc và nhận tên thư mục muốn chuyển tới
            fe.cd(input1); // Gọi hàm cd() truyền vào tên thư mục (hoặc ".." để quay lên thư mục cha)
            break;
        case 5:
            cout << "Enter folder name: "; cin >> input1; // Nhắc và nhận tên thư mục mới muốn tạo
            fe.mkdir(input1); // Gọi hàm mkdir() để tạo mới một thư mục con
            break;
        case 6:
            cout << "Enter file name: "; cin >> input1; // Nhắc và nhận tên file mới muốn tạo
            cout << "Enter file size: "; cin >> size;   // Nhắc và nhận dung lượng (bytes) của file đó
            fe.touch(input1, size); // Gọi hàm touch() truyền tên và kích thước để tạo tệp tin mới
            break;
        case 7:
            cout << "Enter name to delete: "; cin >> input1; // Nhắc và nhận tên phần tử cần xóa khỏi hệ thống
            fe.rm(input1); // Gọi hàm rm() để xóa file hoặc folder con có tên tương ứng
            break;
        case 8:
            cout << "Old name: "; cin >> input1; // Nhắc và nhận tên cũ của file/folder cần đổi
            cout << "New name: "; cin >> input2; // Nhắc và nhận tên mới muốn thay đổi thành
            fe.renameNode(input1, input2); // Gọi hàm renameNode() để tiến hành cập nhật lại tên nút dữ liệu
            break;
        case 9: 
            fe.back(); // Nếu chọn 9, gọi hàm back() để quay lại vị trí thư mục trong lịch sử ngăn xếp (Stack)
            break;
        case 10: 
            fe.forward(); // Nếu chọn 10, gọi hàm forward() để đi tiếp tới vị trí thư mục đã lùi trước đó
            break;
        case 11:
            cout << "Enter name to search: "; cin >> input1; // Nhắc và nhận tên file hoặc folder cần tìm kiếm
            fe.searchBFS(input1); // Gọi hàm searchBFS() để quét toàn bộ cây tìm kiếm theo chiều rộng
            break;
        case 12: 
            fe.totalSize(); // Nếu chọn 12, gọi hàm totalSize() để tính tổng dung lượng thư mục hiện tại
            break;
        case 13:
            cout << "Filename to save (e.g., data.txt): "; cin >> input1; // Nhắc và nhận tên file .txt muốn xuất ra
            fe.saveToFile(input1); // Gọi hàm saveToFile() để thực hiện tuần tự hóa cấu trúc cây lưu xuống ổ đĩa
            break;
        case 14:
            cout << "Filename to load: "; cin >> input1; // Nhắc và nhận tên file .txt chứa dữ liệu cũ muốn nạp lại
            fe.loadFromFile(input1); // Gọi hàm loadFromFile() để giải tuần tự hóa, dựng lại cây vào bộ nhớ RAM
            break;
        case 0: 
            return 0; // Nếu chọn 0, kết thúc hàm main ngay lập tức, đóng ứng dụng thành công
        default: 
            cout << "Invalid choice." << endl; // Nếu nhập một số nằm ngoài danh sách từ 0-14, thông báo lựa chọn không hợp lệ
        }
    }
    return 0; // Trả về mã 0 khi kết thúc hàm main (dòng mã dự phòng chuẩn mực của ngôn ngữ C++)
}
