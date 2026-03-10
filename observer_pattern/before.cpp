/*Nhược điểm

- Engine phụ thuộc trực tiếp vào UI

- Muốn thêm tính năng mới → phải sửa Engine

- Khó mở rộng
*/

#include <iostream>
#include <string>

// Các thành phần giao diện

class ImageView {
public:
    void Refesh() {
        std::cout << "ImageView: Cập nhật hiển thị ảnh\n";
    }
};

class ProgressBar {
public:
    void Update(int percent) {
        std::cout << "ProgressBar: " << percent << "% hoàn thành\n";
    }
};

class LogSystem {
public:
    void Write(const std::string& msg) {
        std::cout << "Log: " << msg << "\n";
    }
};

// Engine xử lý ảnh SAR
class ProcessingEngine {
private:
    ImageView* image_view;
    ProgressBar* progress_bar;
    LogSystem* log_system;

public:
    ProcessingEngine(ImageView* iv,
                     ProgressBar* pb,
                     LogSystem* log)
        : image_view(iv), progress_bar(pb), log_system(log) {}

    void processTile(int percent) {
        std::cout << "Đang xử lý tile...\n";

        // ❌ Gọi trực tiếp từng thành phần
        image_view->Refesh();
        progress_bar->Update(percent);
        log_system->Write("Đã xử lý xong một tile");
    }
};

int main() {
    ImageView iv;
    ProgressBar pb;
    LogSystem log;

    ProcessingEngine engine(&iv, &pb, &log);
    engine.processTile(50);

    return 0;
}