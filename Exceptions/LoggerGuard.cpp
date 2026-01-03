#include <iostream>
#include <string>
#include <exception>

class LoggerGuard {
private:
    std::string message;
public:
    LoggerGuard(std::string message):
        message(message){}
    
    ~LoggerGuard() {
        std::cout << message;
    }
};

int SomeFunction() {return 0;}

int SomeOtherFunction() {throw std::exception();}

int FinalFunction() {throw std::exception();}

int Function() {
    LoggerGuard logger("Function completed");

    int value = 1;
    try {
        value = SomeFunction();
        if (value == 0) {
            return value;
        }

        value = SomeOtherFunction();
        if (value == 0) {
            return value;
        }

        value = FinalFunction();  // might throw an exception
    } catch (...) {
        throw;  // throws the exception further.
    }

    return value;
}

int main() {
    Function();
}