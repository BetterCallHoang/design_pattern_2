/*
Giả sử sau này bạn muốn thêm operation mới:
```
exportToJSON()
```
hoặc
```
computeBoundingBox()
```
Bạn phải sửa tất cả class:

Shape
Circle
Rectangle
Triangle
Polygon

...*/


#include <iostream>
#include <vector>
#include <memory>

class Shape {
public:
    virtual double Area() = 0;
    virtual void Draw() = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double Area() override {
        return 3.14159 * radius * radius;
    }

    void Draw() override {
        std::cout << "Drawing circle radius=" << radius << std::endl;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double Area() override {
        return width * height;
    }

    void Draw() override {
        std::cout << "Drawing rectangle " << width << "x" << height << std::endl;
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));

    for (auto& s : shapes)
        std::cout << "Area: " << s->Area() << std::endl;

    for (auto& s : shapes)
        s->Draw();
}