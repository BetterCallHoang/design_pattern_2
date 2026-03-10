/*
- Tạo ra một file 1 Logger duy nhất
- Mọi nơi dùng chung*/

#include <iostream>
#include <string>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>

// Logger sử dụng Singleton Pattern
class Logger {
public:
    // Xóa constructor public để không cho tạo từ bên ngoài
    Logger(const Logger&) = delete;            // Cấm copy
    Logger& operator=(const Logger&) = delete; // Cấm gán

    // Hàm truy cập duy nhất đến instance
    static Logger& GetInstance() {
        // Static local variable
        static Logger instance;
        return instance;
    }

    void Log(const std::string& message) {
        std::lock_guard <std::mutex> lock(mutex_); // Tạo mutex để tránh 2 thread cùng ghi vào một thời điểm
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);
        file_ << std::ctime(&time) << message << std::endl;
    }

private:
    // Constructor private để không ai tạo được trực tiếp
    Logger() {
        file_.open("Logger.txt", std::ios::app);
        if(!file_) {
            throw std::runtime_error("Cannot open Log file");
        } 
        std::cout << "Logger được tạo duy nhất một lần" << std::endl;
    }
    ~Logger() {
        file_.close();
    }
private:
    std::ofstream file_;
    std::mutex mutex_;
};

// Module xử lý ảnh
class ImageProcessor {
public:
    void Process() {
        // Lấy Logger chung
        Logger::GetInstance().Log("[Image Processor] Bắt đầu xử lý ảnh");
    }
};

// Module hiệu chỉnh
class CalibrationModule {
public:
    void Calibrate() {
        // Dùng cùng một Logger
        Logger::GetInstance().Log("[Calibrate] Bắt đầu hiệu chỉnh");
    }
};

int main() {
    ImageProcessor p;
    CalibrationModule c;

    p.Process();
    c.Calibrate();

    return 0;
}