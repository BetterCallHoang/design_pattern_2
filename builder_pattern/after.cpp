#include <iostream>
#include <memory>
#include <string>

class Computer {
public:
    std::string cpu;
    int ram;
    std::string gpu;
    int storage;
    bool wifi;

    void show() const {
        std::cout << "CPU: " << cpu << "\n"
                  << "RAM: " << ram << " GB\n"
                  << "GPU: " << gpu << "\n"
                  << "Storage: " << storage << " GB\n"
                  << "WiFi: " << (wifi ? "Yes" : "No") << "\n";
    }
};

// ===== Builder Interface =====
class ComputerBuilder {
public:
    virtual ~ComputerBuilder() = default;

    virtual ComputerBuilder& setCPU(const std::string& cpu) = 0;
    virtual ComputerBuilder& setRAM(int ram) = 0;
    virtual ComputerBuilder& setGPU(const std::string& gpu) = 0;
    virtual ComputerBuilder& setStorage(int storage) = 0;
    virtual ComputerBuilder& enableWiFi(bool wifi) = 0;

    virtual std::unique_ptr<Computer> build() = 0;
};

// ===== Concrete Builder =====
class GamingComputerBuilder : public ComputerBuilder {
private:
    std::unique_ptr<Computer> computer;

public:
    GamingComputerBuilder() {
        computer = std::make_unique<Computer>();
    }

    ComputerBuilder& setCPU(const std::string& cpu) override {
        computer->cpu = cpu;
        return *this;
    }

    ComputerBuilder& setRAM(int ram) override {
        computer->ram = ram;
        return *this;
    }

    ComputerBuilder& setGPU(const std::string& gpu) override {
        computer->gpu = gpu;
        return *this;
    }

    ComputerBuilder& setStorage(int storage) override {
        computer->storage = storage;
        return *this;
    }

    ComputerBuilder& enableWiFi(bool wifi) override {
        computer->wifi = wifi;
        return *this;
    }

    std::unique_ptr<Computer> build() override {
        return std::move(computer);
    }
};

// ===== Client code =====
int main() {
    GamingComputerBuilder builder;

    auto pc = builder
        .setCPU("Intel i9")
        .setRAM(32)
        .setGPU("RTX 4080")
        .setStorage(2000)
        .enableWiFi(true)
        .build();

    pc->show();

    return 0;
}