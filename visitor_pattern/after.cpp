#include <iostream>
#include <vector>
#include <memory>

class Circle;
class Rectangle;

// Visitor interface
class ShapeVisitor {
public:
    virtual void Visit(Circle& circle) = 0;
    virtual void Visit(Rectangle& rect) = 0;
    virtual ~ShapeVisitor() = default;
};

// Element interface
class Shape {
public:
    virtual void Accept(ShapeVisitor& Visitor) = 0;
    virtual ~Shape() = default;
};

// ===== Concrete Elements =====

class Circle : public Shape {
public:
    double radius;

    Circle(double r) : radius(r) {}

    void Accept(ShapeVisitor& Visitor) override {
        Visitor.Visit(*this);
    }
};

class Rectangle : public Shape {
public:
    double width;
    double height;

    Rectangle(double w, double h) : width(w), height(h) {}

    void Accept(ShapeVisitor& Visitor) override {
        Visitor.Visit(*this);
    }
};

// ===== Concrete Visitors =====

// Visitor tính diện tích
class AreaVisitor : public ShapeVisitor {
public:
    void Visit(Circle& circle) override {
        double area = 3.14159 * circle.radius * circle.radius;
        std::cout << "Circle area: " << area << std::endl;
    }

    void Visit(Rectangle& rect) override {
        double area = rect.width * rect.height;
        std::cout << "Rectangle area: " << area << std::endl;
    }
};

// Visitor vẽ shape
class DrawVisitor : public ShapeVisitor {
public:
    void Visit(Circle& circle) override {
        std::cout << "Drawing circle radius=" << circle.radius << std::endl;
    }

    void Visit(Rectangle& rect) override {
        std::cout << "Drawing rectangle " 
                  << rect.width << "x" << rect.height << std::endl;
    }
};

// ===== Client =====

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));

    AreaVisitor area_visitor;
    DrawVisitor draw_visitor;

    std::cout << "Compute area\n";
    for (auto& s : shapes)
        s->Accept(area_visitor);

    std::cout << "\nDraw shapes\n";
    for (auto& s : shapes)
        s->Accept(draw_visitor);

    return 0;
}