#include <cstddef>
#include <vector>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <cassert>

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    bool Empty() const;

    size_t Size() const;

    void Clear();

    const T& operator [] (size_t i) const;

    T& operator [] (size_t i);

    const T& At(size_t i) const;  // throws std::out_of_range on incorrect index

    T& At(size_t i);  // throws std::out_of_range on incorrect index

    const T& Front() const;

    T& Front();

    const T& Back() const;

    T& Back();

    void PushFront(const T& elem);

    void PushBack(const T& elem);
};

template<typename T>
bool Deque<T>::Empty() const {
    return !this->Size();
}  

template<typename T>
size_t Deque<T>::Size() const {
    return head.size() + tail.size();
}

template<typename T>
void Deque<T>::Clear() {
    head.clear();
    tail.clear();
}

template<typename T>
const T& Deque<T>::operator[](size_t i) const {
    return (i >= tail.size() ? head[i - tail.size()] : tail[tail.size() - i - 1]);
}

template<typename T>
T& Deque<T>::operator[](size_t i) {
    return (i >= tail.size() ? head[i - tail.size()] : tail[tail.size() - i - 1]);
}

template<typename T>
const T& Deque<T>::At(size_t i) const {
    if (i >= this->Size() || i < 0) {
        throw std::out_of_range("");
    }
    return (i >= tail.size() ? head[i - tail.size()] : tail[i]);
}

template<typename T>
T& Deque<T>::At(size_t i) {
    if (i >= this->Size() || i < 0) {
        throw std::out_of_range("");
    }
    return (i >= tail.size() ? head[i - tail.size()] : tail[i]);
}

template<typename T>
const T& Deque<T>::Front() const {
    return (tail.size() ? tail.back() : head[0]);
}

template<typename T>
T& Deque<T>::Front() {
    return (tail.size() ? tail.back() : head[0]);
}

template<typename T>
const T& Deque<T>::Back() const {
    return (head.size() ? head.back() : tail[0]);
}

template<typename T>
T& Deque<T>::Back() {
    return (head.size() ? head.back() : tail[0]);
}

template<typename T>
void Deque<T>::PushBack(const T& elem) {
    head.push_back(elem);
}

template<typename T>
void Deque<T>::PushFront(const T& elem) {
    tail.push_back(elem);
}

int main() {
    std::cout << "🧪 Начинаем тестирование Deque...\n";

    // 1. Пустой дек
    Deque<int> d;
    assert(d.Empty());
    assert(d.Size() == 0);
    std::cout << "✅ Пустой дек: Empty() = true, Size() = 0\n";

    // 2. PushBack и PushFront
    d.PushBack(10);
    assert(!d.Empty());
    assert(d.Size() == 1);
    assert(d.Front() == 10);
    assert(d.Back() == 10);
    std::cout << "✅ PushBack(10): Front = Back = 10\n";

    d.PushFront(5);
    assert(d.Size() == 2);
    assert(d.Front() == 5);
    assert(d.Back() == 10);
    std::cout << "✅ PushFront(5): Front = 5, Back = 10\n";

    d.PushBack(20);
    assert(d.Size() == 3);
    assert(d.Front() == 5);
    assert(d.Back() == 20);
    std::cout << "✅ PushBack(20): Front = 5, Back = 20\n";

    // 3. operator[] и At
    assert(d[0] == 5);
    assert(d[1] == 10);
    assert(d[2] == 20);
    std::cout << "✅ operator[]: d[0]=5, d[1]=10, d[2]=20\n";

    // Проверка неконстантного доступа
    d[0] = 1;
    d[1] = 2;
    d[2] = 3;
    assert(d.Front() == 1);
    assert(d.Back() == 3);
    std::cout << "✅ Неконстантный operator[] работает\n";

    // 4. At — проверка исключений
    bool throws_on_bad_index = false;
    try {
        d.At(100);
    } catch (const std::out_of_range&) {
        throws_on_bad_index = true;
    }
    assert(throws_on_bad_index);
    std::cout << "✅ At() выбрасывает std::out_of_range при выходе за границы\n";

    // Проверка At в нормальных условиях
    assert(d.At(0) == 1);
    assert(d.At(1) == 2);
    assert(d.At(2) == 3);
    d.At(0) = 100;
    assert(d.Front() == 100);
    std::cout << "✅ At() работает корректно\n";

    // 5. Front() и Back() — неконстантные версии
    d.Front() = 999;
    d.Back() = 888;
    assert(d[0] == 999);
    assert(d[2] == 888);
    std::cout << "✅ Неконстантные Front()/Back() работают\n";

    // 6. Clear
    d.Clear();
    assert(d.Empty());
    assert(d.Size() == 0);
    std::cout << "✅ Clear() работает\n";

    // 7. Большой тест: много PushFront/PushBack
    for (int i = 0; i < 1000; ++i) {
        d.PushBack(i);
    }
    for (int i = -1; i >= -500; --i) {
        d.PushFront(i);
    }
    assert(d.Size() == 1500);
    assert(d.Front() == -500);
    assert(d.Back() == 999);
    assert(d[0] == -500);
    assert(d[499] == -1);
    assert(d[500] == 0);
    assert(d[1499] == 999);
    std::cout << "✅ Большой тест: 1500 элементов, индексы корректны\n";

    // 8. Const-корректность (если компилируется — значит, всё ок)
    const Deque<int>& cd = d;
    assert(cd[0] == -500);
    assert(cd.Front() == -500);
    assert(cd.Back() == 999);
    std::cout << "✅ Const-методы работают\n";

    std::cout << "\n🎉 Все тесты пройдены успешно!\n";
    return 0;
}