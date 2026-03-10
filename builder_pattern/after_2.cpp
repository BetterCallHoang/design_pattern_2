// In modern C++
#include <string>


class Computer {
private:
    std::string cpu;
    int ram;

public:
    class Builder {
    private:
        Computer computer;

    public:
        Builder& setCPU(const std::string& c) {
            computer.cpu = c;
            return *this;
        }

        Builder& setRAM(int r) {
            computer.ram = r;
            return *this;
        }

        Computer build() {
            return computer;
        }
    };
};