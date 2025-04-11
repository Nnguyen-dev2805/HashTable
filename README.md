# Cấu Trúc Dữ Liệu Bảng Băm (Hash Table)

## Giới Thiệu
Dự án này triển khai hai phương pháp chính để xử lý xung đột trong bảng băm:
1. **Separate Chaining** (Phân Chuỗi Riêng Biệt): Sử dụng danh sách liên kết để lưu trữ các phần tử có cùng chỉ số băm.
2. **Linear Probing** (Dò Tuyến Tính): Sử dụng phương pháp địa chỉ mở để xử lý xung đột bằng cách tìm vị trí trống tiếp theo.

## Cấu Trúc Thư Mục
- **SeparateChainingHashTable**: Chứa mã nguồn cho bảng băm sử dụng phương pháp phân chuỗi riêng biệt.
  - `SeparateChainingHashTable.h`: Định nghĩa và triển khai bảng băm.
  - `Node.h`: Định nghĩa cấu trúc nút trong danh sách liên kết.
  - `main.cpp`: Chương trình chính để kiểm tra bảng băm.
- **LinearProbingHashTable**: Chứa mã nguồn cho bảng băm sử dụng phương pháp dò tuyến tính.
  - `LinearProbingHashTable.h`: Định nghĩa và triển khai bảng băm.
  - `main.cpp`: Chương trình chính để kiểm tra bảng băm.

## Hướng Dẫn Sử Dụng
### 1. Separate Chaining
- Mở file `main.cpp` trong thư mục `SeparateChainingHashTable`.
- Chạy chương trình để kiểm tra các chức năng như thêm, xóa, tìm kiếm và hiển thị bảng băm.

### 2. Linear Probing
- Mở file `main.cpp` trong thư mục `LinearProbingHashTable`.
- Chạy chương trình để kiểm tra các chức năng tương tự với phương pháp dò tuyến tính.

## Các Chức Năng Chính
- **Thêm (Insert)**: Thêm một cặp khóa-giá trị vào bảng băm.
- **Xóa (Remove)**: Xóa một cặp khóa-giá trị khỏi bảng băm.
- **Tìm Kiếm (Search)**: Tìm giá trị dựa trên khóa.
- **Hiển Thị (Display)**: Hiển thị toàn bộ bảng băm.

## Ghi Chú
- Dự án sử dụng template để hỗ trợ các kiểu dữ liệu khác nhau cho khóa và giá trị.
- Các phương pháp xử lý xung đột được triển khai hiệu quả và có khả năng mở rộng.

## Tác Giả
- **Mã số sinh viên**: 23110273
- **Họ và tên**: Trương Nhất Nguyên
