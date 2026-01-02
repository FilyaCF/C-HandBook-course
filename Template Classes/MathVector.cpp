#include <iostream>
#include <vector>

template <typename T>
class MathVector {
 private:
    std::vector<T> data;

 public:
    // Храним в `data` нулевой вектор длины `n`
    MathVector(size_t n) {
        data.resize(n);
    }

    template <typename Iter>
    MathVector(Iter first, Iter last) {
        while (first != last) {
            data.push_back(*first++);
        }
    }

    size_t Dimension() const {
         return data.size();
    }

    T& operator [] (size_t i) {
        return data[i];
    }

    const T& operator [] (size_t i) const {
        return data[i];
    }
};

// Output format: (1, 2, 3, 4, 5)
template <typename T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << v[i];
    }
    out << ')';
    return out;
}

template <typename T>
MathVector<T>& operator *= (MathVector<T>& v, const T& scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i) {
        v[i] *= scalar;
    }
    return v;
}

template <typename T>
MathVector<T> operator * (const MathVector<T>& v, const T& scalar) {
    auto tmp(v);
    tmp *= scalar;
    return tmp;
}

template <typename T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& v) {
    return v * scalar;
}

template <typename T>
MathVector<T>& operator += (MathVector<T>& v1, const MathVector<T>& v2) {
    for (size_t i = 0; i != v1.Dimension(); ++i) {
        v1[i] += v2[i];
    }
    return v1;
}

template <typename T>
MathVector<T> operator + (const MathVector<T>& v1, const MathVector<T>& v2) {
    auto tmp(v1);
    tmp += v2;
    return tmp;
}

#include <iostream>
#include <vector>

// --- ВСТАВЬ СЮДА ВЕСЬ ТВОЙ КОД MathVector + операторы ---

int main() {
    std::cout << "🧪 Тестирование MathVector...\n\n";

    // 1. Конструктор нулевого вектора
    MathVector<double> v1(5);
    std::cout << "v1 (нулевой, размер 5): " << v1 << "\n";
    // Ожидается: (0, 0, 0, 0, 0)

    // 2. Конструктор из итераторов
    std::vector<double> vec = {1, 2, 3, 4};
    MathVector<double> v2(vec.begin(), vec.end());
    std::cout << "v2 (из std::vector): " << v2 << "\n";
    // Ожидается: (1, 2, 3, 4)

    // 3. Работа с operator[]
    v1[0] = 1.5;
    v1[2] = -3.0;
    std::cout << "v1 после изменений: " << v1 << "\n";
    // Ожидается: (1.5, 0, -3, 0, 0)

    // 4. operator *=
    v1 *= 2.0;
    std::cout << "v1 *= 2.0 → " << v1 << "\n";
    // Ожидается: (3, 0, -6, 0, 0)

    // 5. operator * (вектор * скаляр)
    auto v3 = v1 * 0.5;
    std::cout << "v3 = v1 * 0.5 → " << v3 << "\n";
    // Ожидается: (1.5, 0, -3, 0, 0)

    // 6. operator * (скаляр * вектор)
    auto v4 = 3.0 * v2;
    std::cout << "v4 = 3 * v2 → " << v4 << "\n";
    // Ожидается: (3, 6, 9, 12)

    // 7. Проверка Dimension()
    std::cout << "Размер v4: " << v4.Dimension() << "\n"; // 4

    // 8. Тест с разными типами (если T = double, scalar = int — должно работать)
    MathVector<int> v5(3);
    v5[0] = 1; v5[1] = 2; v5[2] = 3;
    auto v6 = v5 * 2; // int как скаляр
    std::cout << "v6 = v5 * 2 (int) → " << v6 << "\n";
    // Ожидается: (2, 4, 6)

    // ========================================================
    // 🔜 Сюда добавишь тесты для += и +, когда реализуешь:
    // ========================================================
    /*
    std::cout << "\n--- Тестирование сложения ---\n";

    MathVector<int> a({1, 2, 3});
    MathVector<int> b({4, 5, 6});

    // operator +=
    a += b;
    std::cout << "a += b → " << a << "\n"; // (5, 7, 9)

    // operator +
    MathVector<int> c = MathVector<int>({1, 1, 1}) + MathVector<int>({2, 2, 2});
    std::cout << "c = [1,1,1] + [2,2,2] → " << c << "\n"; // (3, 3, 3)

    // Разные размеры → должно быть исключение или UB (зависит от реализации)
    // MathVector<int> x(2), y(3);
    // x + y; // ← должно быть запрещено
    */

    std::cout << "\n✅ Базовые операции работают!\n";
    return 0;
}