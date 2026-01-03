#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
class AdvancedVector : public std::vector<T> {
public:
    AdvancedVector() = default;
    template<typename ForwardIt>
    AdvancedVector(ForwardIt first, ForwardIt second):
        std::vector<T>(first, second){};
    AdvancedVector(size_t sz, const T& val):
        std::vector<T>(sz, val){};
    AdvancedVector(std::initializer_list<T>&& lst):
        std::vector<T>(lst){};
    inline const T& operator[](int i) const {
        if (i >= static_cast<int>(this->size()) || i < -static_cast<int>(this->size())) {
            throw std::out_of_range("");
        } 
        if (i >= 0) {
            return std::vector<T>::operator[](i);
        } else {
            return std::vector<T>::operator[](this->size() - i);
        }
    }

    inline T& operator[](int i) {
        if (i >= static_cast<int>(this->size()) || i < -static_cast<int>(this->size())) {
            throw std::out_of_range("");
        } 
        if (i >= 0) {
            return std::vector<T>::operator[](i);
        } else {
            return std::vector<T>::operator[](this->size() + i);
        }
    }
};

#include <iostream>
#include <vector>
#include <stdexcept>
#include <cassert>

// Предполагаем, что ваш класс AdvancedVector уже определён выше

int main() {
    try {
        // Тест 1: Конструктор по умолчанию
        AdvancedVector<int> vec1;
        assert(vec1.empty());
        assert(vec1.size() == 0);

        // Тест 2: push_back
        vec1.push_back(10);
        vec1.push_back(20);
        vec1.push_back(30);
        assert(vec1.size() == 3);
        assert(vec1[0] == 10);
        assert(vec1[1] == 20);
        assert(vec1[2] == 30);

        // Тест 3: Отрицательные индексы
        assert(vec1[-1] == 30);  // последний
        assert(vec1[-2] == 20);  // предпоследний
        assert(vec1[-3] == 10);  // первый

        // Тест 4: Выход за границы (положительный индекс)
        try {
            int x = vec1[5];
            assert(false); // Не должно сработать
        } catch (const std::out_of_range& e) {
            // OK
        }

        // Тест 5: Выход за границы (отрицательный индекс)
        try {
            int x = vec1[-4];
            assert(false); // Не должно сработать
        } catch (const std::out_of_range& e) {
            // OK
        }

        // Тест 6: pop_back
        vec1.pop_back();
        assert(vec1.size() == 2);
        assert(vec1[-1] == 20);

        // Тест 7: Конструктор копирования
        AdvancedVector<int> vec2 = vec1;
        assert(vec2.size() == 2);
        assert(vec2[0] == 10);
        assert(vec2[-1] == 20);

        // Тест 8: Оператор присваивания
        AdvancedVector<int> vec3;
        vec3 = vec1;
        assert(vec3.size() == 2);
        assert(vec3[0] == 10);
        assert(vec3[-1] == 20);

        // Тест 9: Сравнение ==
        AdvancedVector<int> vec4;
        vec4.push_back(10);
        vec4.push_back(20);
        assert(vec1 == vec4);
        assert(!(vec1 != vec4));

        // Тест 10: Сравнение !=
        AdvancedVector<int> vec5;
        vec5.push_back(10);
        vec5.push_back(20);
        vec5.push_back(30);
        assert(vec1 != vec5);

        // Тест 11: Шаблонный конструктор с итераторами
        std::vector<double> std_vec = {1.5, 2.5, 3.5};
        AdvancedVector<double> vec6(std_vec.begin(), std_vec.end());
        assert(vec6.size() == 3);
        assert(vec6[0] == 1.5);
        assert(vec6[-1] == 3.5);

        // Тест 12: Пустой вектор
        AdvancedVector<char> vec7;
        assert(vec7.empty());

        std::cout << "✅ Все тесты пройдены!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "❌ Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}