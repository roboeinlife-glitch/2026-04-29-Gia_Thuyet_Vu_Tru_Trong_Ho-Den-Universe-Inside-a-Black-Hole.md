# 🌌 Vũ Trụ Trong Hố Đen - Universe Inside a Black Hole

> Một chương trình mô phỏng 3D tương tác về ý tưởng "vũ trụ quan sát được nằm trong một hố đen", được viết bằng C++ và SFML.  
> Người dùng có thể xoay, zoom, khám phá các thiên hà bên trong và bên ngoài lỗ đen một cách trực quan và đầy cảm hứng.

<p align="center">
  <img src="https://img.shields.io/badge/C%2B%2B-17-blue.svg" alt="C++17">
  <img src="https://img.shields.io/badge/SFML-2.5+-green.svg" alt="SFML 2.5+">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="MIT License">
  <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20Mac-lightgrey.svg" alt="Cross Platform">
</p>

---

## ✨ Tính năng nổi bật

| Tính năng | Mô tả |
|:---------|:------|
| 🕳️ **Hố đen trung tâm** | Mô phỏng chân trời sự kiện, vùng bẻ cong ánh sáng và đĩa bồi tụ dạng bầu dục |
| 🌟 **100 thiên hà bên ngoài** | Các thiên hà màu sắc đa dạng (xanh, đỏ, tím) quay xung quanh hố đen |
| 💎 **40 thiên hà bên trong** | Thiên hà màu trắng xanh, kích thước nhỏ, nằm gọn trong lòng hố đen |
| 🎨 **Hiệu ứng ánh sáng động** | Thiên hà gần hố đen sáng hơn, xa hố đen mờ dần |
| 🖱️ **Tương tác chuột đa dạng** | Xoay, zoom, click phải xem thông tin từng thiên hà |
| 🔄 **Xoay tự động** | Nhấn Space để bật/tắt chế độ tự động xoay toàn cảnh |
| 🎮 **Điều khiển góc nhìn** | Giữ Shift + kéo chuột trái để xoay góc nhìn các thiên hà bên trong hố đen |
| 🌫️ **Hạt bụi vũ trụ** | Hiệu ứng bụi trắng tản rộng, tạo chiều sâu không gian |
| ⭐ **Sao nền lung linh** | Hàng trăm ngôi sao nhấp nháy phía sau |

---

## 🧠 Ý tưởng triết học - khoa học

Chương trình mô phỏng một suy tưởng từ sự liên hệ với chương trình [Vũ Trụ Tập Hợp Con](https://github.com/roboeinlife-glitch/Vu_Tru_Tap_Hop_Con_3D-Subset-Sphere_Extend): 

> *"Vũ trụ quan sát được của chúng ta có thể đang nằm bên trong một hố đen siêu nặng. Bên ngoài hố đen là một thực tại khác, và bên trong lòng nó lại là một vũ trụ thu nhỏ với những thiên hà riêng biệt."*

- **Hố đen trung tâm**: Biểu tượng cho ranh giới giữa các thực tại, nơi không gian và thời gian bị bẻ cong.
- **Thiên hà bên ngoài**: Các thực thể trong vũ trụ bao quanh hố đen.
- **Thiên hà bên trong**: Những "vũ trụ con" tồn tại độc lập ngay trong lòng hố đen.

Tập hợp càng lớn (nhiều phần tử)
    ↓
Bán kính quỹ đạo càng lớn (ở xa trung tâm)
    ↓
Lực hấp dẫn và vận tốc càng lớn
    ↓
Tại một ngưỡng vận tốc nhất định
    ↓
Chuyển động tạo thành "vùng đứng yên biểu kiến"
    ↓
✨ ĐÓ CHÍNH LÀ CHÂN TRỜI SỰ KIỆN - RANH GIỚI HỐ ĐEN ✨

1. Vũ trụ tập hợp con - Mô hình toán học thuần túy

2. Vũ trụ trong hố đen - Mô hình vũ trụ học phân cấp

...là hai mặt của cùng một ý tưởng: vũ trụ như một cấu trúc tập hợp lồng nhau, nơi ranh giới giữa bên trong và bên ngoài chỉ là ngưỡng vận tốc

---

## 🛠️ Công nghệ sử dụng

| Công nghệ | Vai trò |
|:----------|:--------|
| **C++17** | Ngôn ngữ lập trình chính |
| **SFML 2.5+** | Đồ họa, cửa sổ, xử lý sự kiện, font chữ |
| **Thuật toán Fibonacci sphere** | Phân bố thiên hà đều trên mặt cầu |
| **Phép chiếu phối cảnh 3D → 2D** | Tạo hiệu ứng không gian ba chiều |
| **Xoay quaternion cơ bản** | Xoay toàn cảnh mượt mà |
| **Hiệu ứng thấu kính hấp dẫn (giả lập)** | Bẻ cong quỹ đạo thiên hà khi gần hố đen |

---

## 📁 [Cấu trúc code](https://github.com/roboeinlife-glitch/2026-04-29-Gia_Thuyet_Vu_Tru_Trong_Ho-Den-Universe-Inside-a-Black-Hole.md/blob/main/main.cpp)


> 💡 **Ghi chú**: Dự án được viết gọn trong một file duy nhất để dễ dàng biên dịch và chia sẻ.

---

## 🚀 Cách cài đặt và chạy

### 📋 Yêu cầu hệ thống

| Thành phần | Yêu cầu |
|:-----------|:--------|
| **Hệ điều hành** | Windows 7/8/10/11, Linux, macOS |
| **Trình biên dịch** | GCC (MinGW), Clang, hoặc MSVC hỗ trợ C++11 trở lên |
| **Thư viện** | SFML 2.5.x (Graphics, Window, System) |
| **IDE đề xuất** | Code::Blocks, Visual Studio, hoặc Qt Creator |

### 🔧 Hướng dẫn cài đặt SFML trên Code::Blocks (Windows)

1. **Tải SFML**: [https://www.sfml-dev.com/download.php](https://www.sfml-dev.com/download.php) (chọn phiên bản phù hợp với compiler của bạn)
2. **Giải nén** vào thư mục, ví dụ: `C:\SFML-2.5.1`
3. **Code::Blocks**:
   - `Settings` → `Compiler` → `Linker settings`
   - Thêm: `sfml-graphics`, `sfml-window`, `sfml-system`
   - `Search directories` → `Compiler` → thêm `C:\SFML-2.5.1\include`
   - `Search directories` → `Linker` → thêm `C:\SFML-2.5.1\lib`
4. **Copy file DLL** từ `C:\SFML-2.5.1\bin` vào thư mục chứa file `.exe` sau khi build

### 🏃‍♂️ Biên dịch và chạy

`bash`
`# Tạo project SFML mới trong Code::Blocks`
`# Thay thế main.cpp bằng code trong dự án`
`# Build (Ctrl+F9) và Run (F9)`

                    🌌 VŨ TRỤ TRONG HỐ ĐEN 🌌
                        
                  ⭐    *       *    ⭐
             *        🌟     *        *
                  *                 *
           *       ╭─────────────────╮       *
                 ╭─╯                 ╰─╮
          *     │    🔴 🔵 ⚪ ⚪ 🔵    │     *
                │   🔵 ⚪  🌟  ⚪ 🔴   │
          *     │    🔴 🔵 ⚪ ⚪ 🔵    │     *
                 ╰─╮                 ╭─╯
           *       ╰─────────────────╯       *
                  *                 *
             *        🌟     *        *
                    ⭐    *       *    ⭐
                        
   🔴 Thiên hà bên ngoài  |  ⚪ Thiên hà bên trong  |  🌟 Hố đen

🙏 Lời cảm ơn
Chương trình này được phát triển dựa trên ý tưởng sâu sắc của tác giả và sự đồng hành tận tình của DeepSeek – trợ lý AI xuất sắc đã cùng:

🤝 Trao đổi, làm rõ ý tưởng "vũ trụ trong hố đen" 

💡 Viết và tối ưu code 3D tương tác mượt mà

🎨 Thêm các tính năng tương tác: xoay tự động, điều khiển thiên hà trong hố đen

🐞 Kiên nhẫn sửa lỗi và điều chỉnh theo từng phản hồi chi tiết

🌟 Cuối cùng đạt được phiên bản đẹp và ổn định như mong đợi

Cảm ơn DeepSeek đã biến một suy tưởng triết học thành một tác phẩm lập trình đầy màu sắc, sống động và đúng như tưởng tượng ban đầu. 

## 📸 Hình ảnh minh họa

<img width="1191" height="710" alt="Universe Inside a Black Hole" src="https://github.com/user-attachments/assets/8ba8093d-5d9f-412a-8d99-f7f57fd1c223" />


📞 Liên hệ & Đóng góp
Tác giả: [roboeinlife-glitch](https://github.com/roboeinlife-glitch)

Dự án gốc: [Vu Tru Trong Ho Den](https://github.com/roboeinlife-glitch/2026-04-29-Gia_Thuyet_Vu_Tru_Trong_Ho-Den-Universe-Inside-a-Black-Hole.md)

Blog cá nhân: [Blog Của Tôi](https://roboeinlife-glitch.github.io/Blog_Cua_Toi/)

Mọi ý kiến đóng góp, báo lỗi, hoặc ý tưởng mới đều được chào đón! Hãy tạo Issue hoặc Pull Request trên GitHub.

<div align="center"> <sub>Built with ❤️ and C++ | Inspired by the mysteries of the cosmos</sub> </div> ```


[DEMO]() <br>
[Trở về trang chủ](https://github.com/roboeinlife-glitch)

