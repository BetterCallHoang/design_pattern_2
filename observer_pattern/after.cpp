#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

// ===============================
// 1. Observer Interface
// ===============================

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(int percent) = 0;
};

// ===============================
// 2. Subject Interface
// ===============================

class Subject {
public:
    virtual ~Subject() = default;
    virtual void Attach(Observer* obs) = 0;
    virtual void Detach(Observer* obs) = 0;
    virtual void Notify(int percent) = 0;
};

// ===============================
// 3. ProcessingEngine (Subject)
// ===============================

class ProcessingEngine : public Subject {
private:
    std::vector<Observer*> observers;

public:
    void Attach(Observer* obs) override {
        observers.push_back(obs);
    }

    void Detach(Observer* obs) override {
        observers.erase(
            std::remove(observers.begin(), observers.end(), obs),
            observers.end()
        );
    }

    void Notify(int percent) override {
        for (auto obs : observers) {
            obs->Update(percent);
        }
    }

    void ProcessTile(int percent) {
        std::cout << "Đang xử lý tile...\n";

        // Sau khi xử lý xong
        Notify(percent);  // ✅ Thông báo cho tất cả Observer
    }
};

// ===============================
// 4. Concrete Observers
// ===============================

class ImageView : public Observer {
public:
    void Update(int percent) override {
        std::cout << "ImageView: Cập nhật hiển thị ảnh ("
                  << percent << "%)\n";
    }
};

class ProgressBar : public Observer {
public:
    void Update(int percent) override {
        std::cout << "ProgressBar: "
                  << percent << "% hoàn thành\n";
    }
};

class LogSystem : public Observer {
public:
    void Update(int percent) override {
        std::cout << "Log: Đã xử lý xong "
                  << percent << "% dữ liệu\n";
    }
};

// ===============================
// 5. Client
// ===============================

int main() {
    ProcessingEngine engine;

    ImageView image_view;
    ProgressBar progress_bar;
    LogSystem log_system;

    // Đăng ký các observer
    engine.Attach(&image_view);
    engine.Attach(&progress_bar);
    engine.Attach(&log_system);

    engine.ProcessTile(50);

    return 0;
}