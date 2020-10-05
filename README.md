# Game Console rắn săn mồi 2.0

- Demo: <https://youtu.be/T7vTSeiKzMs/>

# Mô tả

- Game được viết bằng ngôn ngữ lập trình C.
- Sử dụng thư viện bên ngoài `console.h` (đã đính kèm trong file).
- Chỉ sử dụng bàn phím để tương tác.

# Tính năng

- [x] Play /Pause /Reset khi đang chơi.
- [x] Lưu Top 5 điểm cao và tên người chơi.
- [x] Âm thanh sống động.
- [x] Có nhiều chế độ và mức độ cho người chơi thử sức.

# Cài đặt

Tải hết các file về cùng 1 folder

- **Run**: Chạy file `TrainCproject.exe`.
- **Compile**: Tạo project ở cùng folder với các file của game rồi thêm file `trainCproject.c` và `console.h` vào project.

1. Dev-C++: Right click vào project -> Menu project -> project options > parameters và điền `-lwinmm` vào cột LINKER section (cái này để devC có thể phát audio) -> F11 (compile & run).

2. Visual Studio: Chỉnh chế độ Debug x86 -> Ctr + F5 (start without debugging).

Nếu chạy file .exe mà báo lỗi thiếu/ lỗi file thì vào <https://www.dll-files.com/>
tải file mình thiếu/ lỗi rồi đưa file đó (sau khi giải nén) vào C:\Windows\System32 và vào chung forder với file .exe.

# License & copyright

© Trần Trung Kiên - Hồ Linh Chi - Hoàng Phi Hải, FPT University TP.HCM
Licensed under the [MIT LICENSE](LICENSE).
