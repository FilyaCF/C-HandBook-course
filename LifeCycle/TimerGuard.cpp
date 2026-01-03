#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

class TimerGuard {
private:
    using time_p = decltype(std::chrono::high_resolution_clock::now());
    time_p start;
    std::string message;
    std::ostream& out;
public:
    TimerGuard(std::string message = "", std::ostream& out = std::cout):
        start(std::chrono::high_resolution_clock::now()),
        message(message),
        out(out){}

    ~TimerGuard() {
        time_p end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = end - start;
        out << std::fixed << message << " " << dur.count() << "\n";
    }
};