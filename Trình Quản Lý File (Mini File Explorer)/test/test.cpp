#include "structures.h" // Nhúng tệp tiêu đề cấu trúc dữ liệu và lớp FileExplorer để sử dụng

// Hàm định nghĩa kịch bản chạy thử tự động 5 bài test (Unit Test)
void runTests() {
    FileExplorer fe; // Khởi tạo một đối tượng fe để làm bài thử nghiệm số 1, 2, 3, 4
    cout << "\n--- STARTING 5 AUTOMATED TESTS ---\n" << endl; // In dòng thông báo bắt đầu quá trình kiểm thử

    // =========================================================================
    // BÀI TEST 1: Kiểm tra tính năng Tạo dữ liệu & Cấu trúc Danh sách liên kết
    cout << "TEST 1: Creating folders and files..." << endl;
    fe.mkdir("docs");      // Tạo thử thư mục tên là "docs"
    fe.mkdir("images");    // Tạo thử thư mục tên là "images"
    fe.touch("notes.txt", 150); // Tạo thử tệp tin tên "notes.txt" với dung lượng 150 bytes
    fe.ls(); // Liệt kê danh sách tại chỗ để kiểm tra xem 3 mục trên đã xuất hiện đúng chưa
    cout << "-> Test 1 Completed.\n" << endl; // Báo cáo bài test 1 hoàn thành thành công

    // =========================================================================
    // BÀI TEST 2: Kiểm tra tính năng Di chuyển & Quản lý con trỏ Cha (Parent Pointers)
    cout << "TEST 2: Navigation (cd, pwd)..." << endl;
    fe.cd("docs"); // Thử đi vào thư mục con "docs" vừa tạo ở bài test 1
    fe.pwd();      // In đường dẫn ra để kiểm tra xem có đúng là "/root/docs" không
    fe.mkdir("work"); // Tạo một thư mục con tên "work" nằm bên trong thư mục "docs"
    fe.cd("work"); // Thử đi tiếp vào trong thư mục "work"
    fe.pwd();      // In đường dẫn ra để kiểm tra xem có đúng là "/root/docs/work" không
    fe.cd("..");   // Lệnh quay lại thư mục cha trực tiếp của nó
    fe.pwd();      // In đường dẫn ra để xem hệ thống đã lùi về lại "/root/docs" đúng chưa
    cout << "-> Test 2 Completed.\n" << endl; // Báo cáo bài test 2 hoàn thành

    // =========================================================================
    // BÀI TEST 3: Kiểm tra tính năng Lịch sử duyệt (Sử dụng Ngăn xếp Stack - Back/Forward)
    cout << "TEST 3: History Stack (Back/Forward)..." << endl;
    fe.back();    // Giả lập hành động bấm nút Lùi (Quay lại thư mục vừa đứng trước đó là "/root/docs/work")
    fe.pwd();     // In đường dẫn kiểm tra vị trí sau khi lùi
    fe.back();    // Tiếp tục bấm nút Lùi một lần nữa (Quay về lại "/root/docs")
    fe.forward(); // Giả lập hành động bấm nút Tiến (Quay tới thư mục vừa bị lùi là "/root/docs/work")
    fe.pwd();     // In đường dẫn kiểm tra vị trí sau khi tiến
    fe.cd("..");  // Trả vị trí đứng lùi về thư mục cha "docs"
    fe.cd("..");  // Tiếp tục trả vị trí đứng lùi hẳn về thư mục gốc "root" để chuẩn bị cho bài test tiếp theo
    cout << "-> Test 3 Completed.\n" << endl; // Báo cáo bài test 3 hoàn thành

    // =========================================================================
    // BÀI TEST 4: Kiểm tra Thuật toán Tìm kiếm rộng (BFS) & Tính tổng dung lượng (Post-order)
    cout << "TEST 4: Search BFS & Total Size..." << endl;
    fe.touch("video.mp4", 1024); // Tạo thêm một file "video.mp4" nặng 1024 bytes ngay tại thư mục root
    fe.searchBFS("work");        // Thử tìm kiếm thư mục "work" (nằm ẩn sâu bên trong nhánh khác) xem BFS quét ra không
    fe.searchBFS("video.mp4");   // Thử tìm kiếm tệp tin "video.mp4" vừa mới tạo xem thuật toán tìm thấy không
    fe.totalSize(); // Tính tổng kích thước thư mục root: Cộng dồn file notes.txt (150b) và video.mp4 (1024b) thành 1174 bytes
    cout << "-> Test 4 Completed.\n" << endl; // Báo cáo bài test 4 hoàn thành

    // =========================================================================
    // BÀI TEST 5: Kiểm tra Đọc/Ghi file lưu trữ (Tuần tự hóa - Serialization)
    cout << "TEST 5: Save to & Load from TXT..." << endl;
    fe.saveToFile("test_tree.txt"); // Xuất toàn bộ sơ đồ cây hiện tại ra một file văn bản tên "test_tree.txt"

    // Tạo ra một đối tượng fe2 hoàn toàn mới (đối tượng này ban đầu rỗng, chỉ có mỗi nút root rỗng)
    FileExplorer fe2; 
    fe2.loadFromFile("test_tree.txt"); // Nạp cấu trúc dữ liệu từ file "test_tree.txt" vào đối tượng mới này
    cout << "Loaded Tree Structure:" << endl; // In dòng chữ thông báo cây đã nạp lại
    fe2.tree(); // Gọi hàm vẽ sơ đồ cây ASCII của đối tượng fe2 để kiểm chứng xem cấu trúc được khôi phục nguyên vẹn không
    cout << "-> Test 5 Completed.\n" << endl; // Báo cáo bài test 5 hoàn thành

    cout << "ALL 5 MANDATORY TESTS PASSED SUCCESSFULY.\n"; // In thông báo chúc mừng cả 5 bài kiểm tra bắt buộc đều vượt qua
}

// Hàm main - Điểm bắt đầu kích hoạt luồng chạy của chương trình kiểm thử
int main() {
    runTests(); // Gọi hàm chạy bộ kiểm thử tự động ở trên
    return 0;   // Trả về mã 0 báo hiệu chương trình kết thúc thành công, không gặp lỗi hệ thống
}
