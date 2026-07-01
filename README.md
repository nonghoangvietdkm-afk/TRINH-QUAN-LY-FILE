Tên ứng dụng
Mini File Explorer — Ứng dụng mô phỏng hệ thống quản lý tập tin và thư mục dưới dạng cây trên giao diện dòng lệnh (CLI).

Cấu trúc dữ liệu sử dụng
Tree (N-ary): dùng để mô phỏng toàn bộ hệ thống file/thư mục dưới dạng phân cấp vì mỗi thư mục có thể chứa nhiều thư mục con và tập tin khác nhau.
Stack: dùng để quản lý tính năng lịch sử di chuyển (Back/Forward) vì cơ chế LIFO (Last-In-First-Out) cho phép quay lại thư mục vừa truy cập một cách chính xác.
Queue: dùng để triển khai thuật toán tìm kiếm BFS (Breadth-First Search) vì cơ chế FIFO (First-In-First-Out) giúp duyệt qua tất cả các thư mục cùng cấp trước khi đi sâu xuống các cấp tiếp theo.
Linked List: dùng để lưu trữ và quản lý danh sách các file/folder con bên trong một thư mục cha (qua con trỏ firstChild và nextSibling) vì nó giúp tối ưu hóa việc thêm hoặc xóa file mà không tốn chi phí dời ô nhớ như mảng.
Compile và chạy
g++ -std=c++17 src/main.cpp src/functions.cpp -o app && ./app

Để chạy file kiểm thử tự động (5 test cases): g++ -std=c++17 tests/test.cpp src/functions.cpp -o test_app && ./test_app

Chức năng
Hiển thị cây thư mục dưới dạng đồ họa ASCII trực quan (giống lệnh tree).
Tạo mới (mkdir, touch), xóa bỏ (rm), và đổi tên (rename) cho cả folder và file.
Di chuyển và quản lý vị trí hiện tại trong hệ thống thư mục (cd, ls, pwd).
Di chuyển lùi lại (Back) hoặc tiến lên (Forward) trong lịch sử bằng Stack.
Tìm kiếm tập tin hoặc thư mục theo tên bằng thuật toán duyệt theo chiều rộng BFS (Queue).
Tính toán và hiển thị tổng dung lượng của một thư mục bằng thuật toán duyệt cây Post-order traversal.
Lưu toàn bộ cấu trúc cây thư mục ra file .txt và đọc/tái tạo lại cây từ file đó (I/O Serialization).
Test cases
Mô tả 5 test case chính tự động trong file test.cpp:

Test 1: Tạo các thư mục (docs, images) và file (notes.txt), sau đó gọi lệnh ls để kiểm tra tính chính xác của cấu trúc Linked List trong thư mục hiện tại.

Test 2: Di chuyển sâu vào cây thư mục bằng lệnh cd và in đường dẫn tuyệt đối bằng pwd để xác thực liên kết con trỏ parent.

Test 3: Kiểm tra tính chính xác của Stack lịch sử bằng cách thực hiện chuỗi thao tác điều hướng và kiểm tra trạng thái khi gọi back() và forward().

Test 4: Sử dụng thuật toán tìm kiếm BFS (Queue) để quét tìm một file nằm ẩn sâu trong hệ thống, đồng thời tính tổng dung lượng thư mục bằng Post-order traversal.

Test 5: Kiểm tra tính năng I/O bằng cách xuất cấu trúc cây ra file test_tree.txt, giải phóng bộ nhớ cây cũ, sau đó nạp lại dữ liệu từ file để khôi phục nguyên vẹn cấu trúc cây ban đầu.

Cấu trúc file
src/ main.cpp — Menu và điều khiển structures.h — Khai báo struct + nguyên mẫu hàm functions.cpp — Cài đặt chi tiết tests/ test.cpp — Chạy tự động 5 test case chính
