#include <iostream>
#include <deque>
#include <exception>
#include <list>

template<typename T, typename Container = std::deque<T>>
class Queue {
private:
    Container data;
public:
    Queue() = default;

    const T& front() const {
        if (data.empty()) {
            throw std::out_of_range("Empty queue!");
        }
        return data.front();
    }

    T& front() {
        if (data.empty()) {
            throw std::out_of_range("Empty queue!");
        }
        return data.front();
    }

    void pop() {
        if (data.empty()) {
            throw std::out_of_range("Empty queue!");
        }
        data.pop_front();
    }

    void push(const T& item) {
        data.push_back(item);
    }

    size_t size() const {
        return data.size();
    }

    bool empty() const {
        return !size();
    }

    typename Container::iterator begin() {
        return data.begin();
    }

    typename Container::iterator end() {
        return data.end();
    }

    template<typename T2, typename Container2>
    bool operator ==(Queue<T2, Container2>& other) {
        if (other.size() != this->size() || !std::is_same_v<T, T2>) {
            return false;
        }
        auto it1 = this->begin();
        auto it2 = other.begin();
        while(it1 != this->end()) {
            if (*it1++ != *it2++) return false;
        }
        return true;
    }

    template<typename T2, typename Container2>
    bool operator !=(Queue<T2, Container2>& other) {
        return !(*this == other);
    }
};

int main() {
    // 1. Пустая очередь
    Queue<int> q1;
    std::cout << "q1.empty(): " << q1.empty() << '\n';  // должно быть 1
    std::cout << "q1.size(): " << q1.size() << '\n';    // 0

    // 2. Добавляем элементы
    q1.push(10);
    q1.push(20);
    q1.push(30);

    std::cout << "q1.front(): " << q1.front() << '\n';  // 10
    std::cout << "q1.size(): " << q1.size() << '\n';    // 3

    // 3. Меняем front через неконстантную версию
    Queue<int>& q1_ref = q1;
    q1_ref.front() = 999; // меняем значение в начале очереди
    std::cout << "q1.front() после изменения: " << q1.front() << '\n'; // 999

    // 4. pop()
    q1.pop();
    std::cout << "После pop(): q1.front() = " << q1.front() << '\n'; // 20
    std::cout << "q1.size(): " << q1.size() << '\n'; // 2

    // 5. Создадим вторую очередь
    Queue<int> q2;
    q2.push(999);
    q2.push(20);
    q2.push(30);

    // 6. Оператор == — должны быть равны?
    std::cout << "\nq1 == q2: " << (q1 == q2) << '\n'; // должно быть 1 (если содержимое одинаково)

    // 7. Изменим q2
    q2.pop();
    q2.push(99); // теперь q2: [20, 30, 99]

    std::cout << "q1 == q2: " << (q1 == q2) << '\n'; // должно быть 0

    // 8. Оператор !=
    std::cout << "q1 != q2: " << (q1 != q2) << '\n'; // должно быть 1

    // 9. Проверка с другим контейнером (например, vector)
    Queue<int, std::list<int>> q3;
    q3.push(999);
    q3.push(20);
    q3.push(30);

    // ❗️ Это важно: если ты НЕ определил operator== между Queue<int, deque> и Queue<int, vector>,
    // то это вызовет ошибку компиляции — и это правильно!
    // Если ты *сделал* такой оператор — он должен работать по значению.
    // Но стандарт требует, чтобы Queue был обёрткой над контейнером — значит, тип контейнера — часть типа.
    // Поэтому: Queue<int, deque> ≠ Queue<int, vector> — даже если данные одинаковы.

    // Попробуйте раскомментировать, если хочешь проверить:
    // std::cout << "q2 == q3: " << (q2 == q3) << '\n'; // ← ошибка, если не определено!

    // 10. Проверка с разными типами элементов (должна быть ошибка!)
    Queue<long long> q4;
    q4.push(999LL);
    q4.push(20LL);
    q4.push(30LL);

    // ❗️ Если у тебя есть operator== между Queue<int> и Queue<long long> — это баг.
    // Компилятор должен выдать ошибку!
    // Раскомментируй, чтобы проверить:
    // std::cout << "q2 == q4: " << (q2 == q4) << '\n'; // ← ОШИБКА КОМПИЛЯЦИИ — нормально!

    // 11. Проверка пустых очередей
    Queue<std::string> empty1, empty2;
    std::cout << "\nempty1 == empty2: " << (empty1 == empty2) << '\n'; // 1
    std::cout << "empty1 != empty2: " << (empty1 != empty2) << '\n'; // 0

    // 12. Добавим одинаковые строки
    empty1.push("hello");
    empty2.push("hello");

    std::cout << "empty1 == empty2: " << (empty1 == empty2) << '\n'; // 1

    // 13. Проверка front() на пустой очереди (если не бросает исключение — не страшно, но лучше проверять empty())
    // Queue<int> q_empty;
    // int x = q_empty.front(); // UB или исключение — зависит от реализации

    std::cout << "\n✅ Все тесты пройдены!" << std::endl;

    return 0;
}