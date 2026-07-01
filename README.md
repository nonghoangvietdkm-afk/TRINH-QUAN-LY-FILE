📁 Mini File Explorer (CLI)
Mini File Explorer là một ứng dụng giao diện dòng lệnh (CLI) mô phỏng trực quan hệ thống quản lý tập tin và thư mục dưới dạng cây phân cấp. Dự án được xây dựng dựa trên sự kết hợp tối ưu của các cấu trúc dữ liệu cốt lõi nhằm giải quyết triệt để các bài toán thực tế như quản lý lịch sử, tìm kiếm tối ưu và tuần tự hóa dữ liệu (Serialization).

🛠️ Kiến Trúc Cấu Trúc Dữ Liệu & Thuật Toán
Ứng dụng hoàn toàn không sử dụng các thư viện container có sẵn (như std::vector, std::stack, std::queue) mà tự hiện thực các cấu trúc dữ liệu (CTDL) để tối ưu hóa hiệu năng và bộ nhớ:

Tree (N-ary Tree): Mô phỏng toàn bộ hệ thống file/thư mục phân cấp. Mỗi thư mục đóng vai trò là một nút (Node) có thể chứa nhiều thư mục con và tập tin khác nhau.

Linked List (firstChild & nextSibling): Thay vì dùng mảng, danh sách các file/folder con bên trong một thư mục cha được quản lý bằng cơ chế Danh sách liên kết. Mô hình này giúp tối ưu hóa việc thêm/xóa phần tử với độ phức tạp O(1) sau khi tìm thấy vị trí, hoàn toàn không tốn chi phí dịch chuyển vùng nhớ như mảng tĩnh hay mảng động.

Stack (Cơ chế LIFO): Quản lý tính năng lịch sử điều hướng (Back/Forward). Khi người dùng thay đổi thư mục, trạng thái cũ được đẩy vào Stack, cho phép quay lại đúng thư mục vừa truy cập một cách chính xác.

Queue (Cơ chế FIFO): Triển khai thuật toán tìm kiếm BFS (Breadth-First Search). Hàng đợi giúp duyệt qua tất cả các thư mục cùng cấp trước khi đi sâu xuống các cấp tiếp theo, tối ưu hơn cho việc tìm kiếm các tập tin ở gần vị trí hiện tại.

Post-order Traversal (Duyệt cây sau): Được sử dụng để tính toán chính xác tổng dung lượng của một thư mục (Dung lượng thư mục cha = Tổng dung lượng các file nội tại + tổng dung lượng được tính đệ quy từ các thư mục con bên trong).

✨ Các Tính Năng Cốt Lõi
🖥️ Trực quan hóa: Hiển thị cây thư mục dưới dạng đồ họa ASCII trực quan và sinh động (tương tự lệnh tree trên Linux/Windows).

📁 Quản lý tệp tin: Tạo mới (mkdir, touch), xóa bỏ (rm), và đổi tên (rename) linh hoạt cho cả file và folder.

🧭 Điều hướng hệ thống: Di chuyển và quản lý vị trí hiện tại (cd, ls, pwd) thông qua liên kết con trỏ parent.

⏳ Lịch sử duyệt mục: Quay lại (Back) hoặc tiến tới (Forward) trong lịch sử di chuyển nhờ hệ thống Double-Stack.

🔍 Tìm kiếm thông minh: Quét tìm tập tin ẩn sâu trong hệ thống bằng thuật toán duyệt theo chiều rộng BFS.

💾 I/O Serialization: Xuất toàn bộ cấu trúc cây thư mục hiện tại ra file .txt và tái tạo (đọc) lại nguyên vẹn cấu trúc cây khi khởi động lại ứng dụng.

📂 Cấu Trúc Thư Mục Dự Án
Plaintext
mini-file-explorer/
├── src/
│   ├── main.cpp         # Menu điều khiển chính và vòng lặp tương tác người dùng (CLI)
│   ├── structures.h     # Định nghĩa các Struct (Node, Stack, Queue) & mẫu hàm
│   └── functions.cpp    # Cài đặt chi tiết các hàm xử lý logic hệ thống
└── tests/
    └── test.cpp         # File chạy kiểm thử tự động (Automation Test Suite)
🧪 Hệ Thống Kiểm Thử Tự Động (5 Test Cases)
Ứng dụng tích hợp sẵn script kiểm thử tự động trong tests/test.cpp nhằm xác thực độ ổn định và tính chính xác của các cấu trúc dữ liệu:

Test 1: Cấu trúc Linked List
Tạo các thư mục (docs, images) và file (notes.txt), sau đó gọi lệnh ls để kiểm tra tính chính xác của cấu trúc Linked List trong thư mục hiện tại.

Test 2: Con trỏ Parent & Điều hướng
Di chuyển sâu vào cây thư mục bằng lệnh cd và in đường dẫn tuyệt đối bằng pwd để xác thực liên kết ngược lên nút cha.

Test 3: Lịch sử Đôi (Double-Stack)
Thực hiện chuỗi thao tác điều hướng phức tạp, kiểm tra trạng thái lịch sử khi gọi back() và forward().

Test 4: BFS & Post-order Traversal
Sử dụng thuật toán tìm kiếm BFS (Queue) để quét tìm một file nằm ẩn sâu, đồng thời tính tổng dung lượng thư mục bằng Post-order.

Test 5: Serialization I/O
Kiểm tra tính năng bằng cách xuất cấu trúc cây ra file test_tree.txt, giải phóng bộ nhớ cây cũ, sau đó nạp lại dữ liệu từ file để khôi phục nguyên vẹn cấu trúc ban đầu.

🚀 Hướng Dẫn Biên Dịch Và Chạy Ứng Dụng
Đảm bảo máy tính của bạn đã cài đặt trình biên dịch hỗ trợ chuẩn C++17 trở lên (ví dụ: GCC 7.0+, Clang 5.0+, MSVC 2017+).

1. Chạy ứng dụng chính (Chế độ tương tác CLI)
Biên dịch các file mã nguồn trong thư mục src và khởi chạy chương trình:
