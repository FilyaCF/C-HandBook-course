#include <iostream>

class Serializer {
private:
public:
    Serializer() = default;

    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const std::string&) = 0;
    virtual void EndArray() = 0;

    virtual ~Serializer() = default;
};

class JsonSerializer : public Serializer {
private:
    int lastOp = 0;
public:
    JsonSerializer() = default;

    void BeginArray() override {
        if (lastOp) std::cout << ",";
        std::cout << "[";
        lastOp = 0;
    }

    void AddArrayItem(const std::string& item) override {
        if (lastOp) std::cout << ",";
        std::cout << '\"' << item << '\"';
        lastOp = 1;
    }

    void EndArray() override {
        std::cout << "]";
        lastOp = 2;
    }

    ~JsonSerializer() = default;
};

int main() {
    std::string op = "";
    JsonSerializer s;
    while(std::cin >> op) {
        if (op == "BeginArray") {
            s.BeginArray();
        } else if (op == "EndArray") {
            s.EndArray();
        } else {
            std::string item;
            std::cin >> item;
            s.AddArrayItem(item);
        }
    }
}