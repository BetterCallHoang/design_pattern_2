/* Ý tưởng

- Tạo interface chung

- Proxy đại diện cho object thật

- Chỉ load dữ liệu khi cần truy cập pixel*/
#include <iostream>
#include <memory>
#include <string>

// ===============================
// 1. Interface chung
// ===============================

class ISarProduct {
public:
    virtual ~ISarProduct() = default;

    virtual void ShowMetadata() = 0;
    virtual void GetPixel(int x, int y) = 0;
};

// ===============================
// 2. Object thật (rất nặng)
// ===============================

class SarProduct : public ISarProduct {
private:
    std::string filename;

    void LoadDataFromDisk() {
        std::cout << "Đang tải toàn bộ dữ liệu ảnh SAR từ đĩa...\n";
        std::cout << "Dữ liệu lớn đã được load vào RAM.\n";
    }

public:
    SarProduct(const std::string& file)
        : filename(file)
    {
        LoadDataFromDisk();  // Chỉ load khi được tạo
    }

    void ShowMetadata() override {
        std::cout << "Metadata của file: " << filename << "\n";
    }

    void GetPixel(int x, int y) override {
        std::cout << "Truy cập pixel tại (" << x << ", " << y << ")\n";
    }
};

// ===============================
// 3. Proxy
// ===============================

class SarProductProxy : public ISarProduct {
private:
    std::string filename;

    // Ban đầu chưa có object thật
    std::unique_ptr<SarProduct> real_product;

    // Chỉ load khi cần
    void EnsureLoaded() {
        if (!real_product) {
            std::cout << "[Proxy] Chưa load dữ liệu. Tiến hành load...\n";
            real_product = std::make_unique<SarProduct>(filename);
        }
    }

public:
    SarProductProxy(const std::string& file)
        : filename(file)
    {
        // Không load dữ liệu ở đây
    }

    void ShowMetadata() override {
        // Metadata có thể đọc nhẹ, không cần load toàn bộ
        std::cout << "Metadata (đọc nhanh) của file: "
                  << filename << "\n";
    }

    void GetPixel(int x, int y) override {
        // Chỉ load khi thực sự cần pixel
        EnsureLoaded();
        real_product->GetPixel(x, y);
    }
};

// ===============================
// 4. Client
// ===============================

int main() {
    std::unique_ptr<ISarProduct> product =
        std::make_unique<SarProductProxy>("sentinel1.dat");

    std::cout << "Chỉ xem metadata:\n";
    product->ShowMetadata();  // Không load dữ liệu

    std::cout << "\nTruy cập pixel:\n";
    product->GetPixel(100, 200);  // Lúc này mới load

    return 0;
}