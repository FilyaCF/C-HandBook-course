#include <iostream>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const = 0;
};

class B : public A {
public:
    B(): A(42){};

    void foo() const override {};

    ~B() = default;
};

int main() {
    B b;
    const A& a = b;
    a.foo();
}