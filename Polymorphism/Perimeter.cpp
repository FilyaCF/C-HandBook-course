#include <iostream>
#include <vector>
#include <iostream>

class Figure {
private:
public:
    Figure() = default;

    virtual int Perimeter() const = 0;

    virtual ~Figure() = default;
};

class Triangle : public Figure {
private:
    int a, b, c;
public:
    Triangle(int a = 0, int b = 0, int c = 0):
        a(a),
        b(b),
        c(c){}
    
    int Perimeter() const override {
        return a + b + c;
    }

    ~Triangle() = default;
};

class Rectangle : public Figure {
private:
    int64_t a, b;
public:
    Rectangle(int64_t a = 0, int64_t b = 0):
        a(a),
        b(b){}
    
    int Perimeter() const override {
        return 2 * (a + b);
    }

    ~Rectangle() = default;
};

int main() {
    std::vector<Figure*> figures;

    std::string type;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }
}