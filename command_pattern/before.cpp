/* Vấn đề

- UI gọi trực tiếp zoom(), rotate()

- Không lưu được lịch sử

- Không hỗ trợ Undo/Redo*/

#include <iostream>

// Lớp hiển thị ảnh
class ImageViewport {
private:
    double scale = 1.0;
    double rotation_angle = 0.0;

public:
    void Zoom(double factor) {
        scale *= factor;
        std::cout << "Zoom: scale = " << scale << "\n";
    }

    void Rotate(double angle) {
        rotation_angle += angle;
        std::cout << "Rotate: angle = " << rotation_angle << "\n";
    }
};

int main() {
    ImageViewport viewport;

    // UI gọi trực tiếp
    viewport.Zoom(1.2);
    viewport.Rotate(90);

    // ❌ Không thể undo
    return 0;
}