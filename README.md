# 📁 Giới Thiệu Dự Án: TRÌNH QUẢN LÝ FILE

---

## 1. 🎯 Tổng Quan Dự Án & Mục Tiêu Thiết Kế

**Mini File Explorer** là một ứng dụng giả lập **hệ thống quản lý tập tin và thư mục** hoạt động trực tiếp trên **giao diện dòng lệnh (CLI)**.

* **Bối cảnh bài toán:** Trong các hệ điều hành thực tế (như Windows, Linux), hệ thống file luôn được tổ chức theo **mô hình cây phân cấp**. Việc quản lý hàng triệu tập tin yêu cầu các thao tác như tìm kiếm, điều hướng và thêm/xóa phải diễn ra với **tốc độ tối ưu** và **tốn ít tài nguyên** nhất.
* **Mục tiêu của ứng dụng:** Dự án này được viết ra nhằm tái hiện lại cách thức hoạt động của một hệ điều hành thu nhỏ. Điểm đặc biệt là ứng dụng **hoàn toàn tự xây dựng (tự code tay) các cấu trúc dữ liệu nền tảng** mà không dựa dẫm vào bất kỳ thư viện container có sẵn nào của C++ (như `std::vector`, `std::stack`, `std::queue`). Qua đó, giúp tối ưu hóa **hiệu năng xử lý** tại từng nút (Node) trong hệ thống.

---

## 🛠️ 2. Phân Tích Logic Cấu Trúc Dữ Liệu & Thuật Toán

Sự thành công của ứng dụng đến từ việc đặt đúng **cấu trúc dữ liệu** vào đúng bài toán cần giải quyết. Mối quan hệ logic giữa các thành phần được thiết kế như sau:

* 🌳 **Mô phỏng cây thư mục bằng Cây n-phân (N-ary Tree):** Vì một thư mục có thể chứa vô số thư mục con và file, cấu trúc **Cây** là lựa chọn duy nhất phản ánh chính xác tính chất phân cấp này. Mỗi **Node** trên cây sẽ đại diện cho một **File** hoặc một **Folder**.
* 🔗 **Tối ưu hóa bộ nhớ bằng Danh sách liên kết (Linked List):** Thay vì dùng mảng co giãn (Vector) để lưu danh sách con bên trong thư mục, dự án sử dụng hai con trỏ cốt lõi là **`firstChild` (con đầu tiên)** và **`nextSibling` (anh em kế cận)**.
* *Logic xử lý:* Khi bạn tạo thêm 1 file hoặc xóa 1 folder, hệ thống chỉ cần **thay đổi liên kết con trỏ** với chi phí cực thấp ($O(1)$), hoàn toàn **không tốn chi phí cấp phát lại bộ nhớ** hay dịch chuyển vùng nhớ như mảng tĩnh hay mảng động.


* ⏳ **Quản lý lịch sử di chuyển bằng Ngăn xếp (Stack):** Tính năng Quay lại (**Back**) và Tiến về trước (**Forward**) hoạt động dựa trên cơ chế **LIFO (Vào sau - Ra trước)**.
* *Logic xử lý:* Khi người dùng gõ `cd` để vào thư mục mới, thư mục cũ sẽ được "đẩy" vào **Stack Back**. Khi nhấn lệnh quay lại, hệ thống lấy ngay phần tử trên cùng ra. Thao tác này diễn ra **ngay lập tức** mà không cần duyệt lại từ đầu cây.


* 🔍 **Tìm kiếm tập tin nhanh bằng Hàng đợi và Duyệt chiều rộng (Queue & BFS):** Khi người dùng cần tìm một file theo tên nhưng không nhớ rõ vị trí, thuật toán **BFS** sẽ quét qua tất cả các file/folder ở **cùng cấp độ hiện tại** trước khi đi sâu xuống các tầng thấp hơn.
* *Logic xử lý:* Việc sử dụng **Queue (FIFO)** đảm bảo thứ tự tìm kiếm công bằng và giúp **tìm ra các file nằm ở gần vị trí hiện tại** của người dùng sớm nhất mà không bới sâu vào các nhánh xa lạ không liên quan.


* 🧮 **Tính tổng dung lượng bằng Duyệt cây sau (Post-order Traversal):** Một thư mục không tự có dung lượng cố định, dung lượng của nó bằng **tổng dung lượng các file bên trong** cộng với **dung lượng của các thư mục con** thuộc về nó.
* *Logic xử lý:* Thuật toán **duyệt sau (Trái -> Phải -> Gốc)** sẽ đi xuống tận cùng của các nhánh con, tính toán dung lượng của các tệp tin nhỏ nhất trước, sau đó **cộng dồn ngược lên trên** để đưa ra con số chính xác cho thư mục cha.



---

## 🗺️ 3. Bản Đồ Tính Năng & Kịch Bản Kiểm Thử (Test Cases)

Hệ thống được chia làm hai chế độ vận hành rõ rệt nhằm đảm bảo **tính thực tiễn** và **khả năng kiểm thử tự động**.

### 💻 3.1. Các nhóm tính năng tương tác người dùng

* **Nhóm Quản trị hệ thống:** Tạo mới thư mục/file (`mkdir`, `touch`), xóa bỏ hoàn toàn một nhánh cây (`rm`), đổi tên phần tử (`rename`).
* **Nhóm Điều hướng không gian:** Duyệt danh sách mục con (`ls`), chuyển đổi thư mục (`cd`), hiển thị đường dẫn tuyệt đối từ gốc (`pwd`). Đặc biệt là khả năng hiển thị toàn bộ cây dưới dạng **đồ họa ký tự ASCII trực quan** (giống lệnh `tree`).
* **Nhóm Hệ thống (I/O Serialization):** Lưu cấu trúc cây thành file văn bản `.txt` và đọc ngược lại file đó để **tái dựng lại toàn bộ cây vào bộ nhớ RAM** khi khởi động lại ứng dụng.

### 🧪 3.2. Logic vận hành của 5 Kịch bản Kiểm thử Tự động (Automation Test)

Để chứng minh các cấu trúc dữ liệu tự viết hoạt động **chính xác 100%**, file `test.cpp` sẽ chạy tự động qua **5 bước logic** nghiêm ngặt:

* 🔹 **Kịch bản 1 (Kiểm thử Linked List):** Hệ thống tự động tạo hàng loạt file và thư mục, sau đó gọi lệnh `ls` để xác thực xem các con trỏ `nextSibling` có **liên kết đúng thứ tự** và không làm sót phần tử nào.
* 🔹 **Kịch bản 2 (Kiểm thử Con trỏ Ngược):** Cho hệ thống `cd` sâu qua nhiều tầng thư mục, sau đó gọi `pwd`. Nếu đường dẫn in ra chính xác, chứng tỏ **con trỏ `parent` ngược lên nút cha** hoạt động hoàn hảo.
* 🔹 **Kịch bản 3 (Kiểm thử Double-Stack):** Thực hiện một chuỗi di chuyển liên tục: A -> B -> C -> D. Sau đó giả lập gọi `back()` 2 lần và `forward()` 1 lần, rồi đối chiếu vị trí hiện tại để kiểm tra **tính toàn vẹn của lịch sử**.
* 🔹 **Kịch bản 4 (Kiểm thử BFS & Đệ quy):** Giấu một file tên là `secret.txt` ở một nhánh rất sâu. Chạy lệnh tìm kiếm để xem **Queue** có tìm ra đúng file đó không, đồng thời chạy hàm duyệt **Post-order** kiểm tra xem tổng dung lượng hiển thị có khớp với thực tế hay không.
* 🔹 **Kịch bản 5 (Kiểm thử Đóng/Mở dữ liệu):** Xuất toàn bộ cây ra file `test_tree.txt`. Dùng hàm hủy (destructor) **giải phóng hoàn toàn vùng nhớ trên RAM**, sau đó nạp lại dữ liệu từ file để chứng minh hệ thống có thể **khôi phục nguyên vẹn 100%** cấu trúc ban đầu.
