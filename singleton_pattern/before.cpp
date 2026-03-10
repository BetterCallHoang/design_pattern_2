/*Vấn đề:

- Mỗi module tự tạo Logger

- Có nhiều instance khác nhau

- Log không tập trung
--> Có thể tạo ra nhiều file Log 
*/
#include <iostream>
#include <string>

// Lớp Logger bình thường
class Logger {
public:
    Logger() {
        std::cout << "Logger được tạo\n";
    }

    void Log(const std::string& message) {
        std::cout << "[Log] " << message << std::endl;
    }
};

// Module xử lý ảnh
class ImageProcessor {
private:
    Logger logger;  // Mỗi module có Logger riêng

public:
    void Process() {
        logger.Log("Bắt đầu xử lý ảnh");
    }
};

// Module hiệu chỉnh
class CalibrationModule {
private:
    Logger logger;  // Lại tạo thêm một Logger khác

public:
    void Calibrate() {
        logger.Log("Bắt đầu hiệu chỉnh");
    }
};

int main() {
    ImageProcessor p;
    CalibrationModule c;

    p.Process();
    c.Calibrate();

    return 0;
}