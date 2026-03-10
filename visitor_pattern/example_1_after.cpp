#include <iostream>
#include <vector>
#include <memory>

class Circle;
class Rectangle;

// Visitor interface
class ShapeVisitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rect) = 0;
    virtual ~ShapeVisitor() = default;
};

// Element interface
class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
    virtual ~Shape() = default;
};

// ===== Concrete Elements =====

class Circle : public Shape {
public:
    double radius;

    Circle(double r) : radius(r) {}

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

class Rectangle : public Shape {
public:
    double width;
    double height;

    Rectangle(double w, double h) : width(w), height(h) {}

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
};

// ===== Concrete Visitors =====

// Visitor tính diện tích
class AreaVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14159 * circle.radius * circle.radius;
        std::cout << "Circle area: " << area << std::endl;
    }

    void visit(Rectangle& rect) override {
        double area = rect.width * rect.height;
        std::cout << "Rectangle area: " << area << std::endl;
    }
};

// Visitor vẽ shape
class DrawVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        std::cout << "Drawing circle radius=" << circle.radius << std::endl;
    }

    void visit(Rectangle& rect) override {
        std::cout << "Drawing rectangle " 
                  << rect.width << "x" << rect.height << std::endl;
    }
};

// ===== Client =====

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));

    AreaVisitor areaVisitor;
    DrawVisitor drawVisitor;

    std::cout << "Compute area\n";
    for (auto& s : shapes)
        s->accept(areaVisitor);

    std::cout << "\nDraw shapes\n";
    for (auto& s : shapes)
        s->accept(drawVisitor);

    return 0;
}