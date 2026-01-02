#include <iostream>
#include <vector>

template<typename T>
class Polynomial;

template<typename T>
bool operator==(const Polynomial<T>&, const Polynomial<T>&);

template<typename T>
bool operator==(const Polynomial<T>&, const T&);

template<typename T>
bool operator==(const T&, const Polynomial<T>&);

template<typename T>
bool operator!=(const Polynomial<T>&, const Polynomial<T>&);

template<typename T>
bool operator!=(const Polynomial<T>&, const T&);

template<typename T>
bool operator!=(const T&, const Polynomial<T>&);

template<typename T>
class Polynomial {
private:
    std::vector<T> coefficients;
    static const T zero;

    void Normalize();
public:
    Polynomial() = default;
    Polynomial(const std::vector<T>&);
    Polynomial(const T&);
    template<typename Iter>
    Polynomial(Iter first, Iter second);
    Polynomial(const Polynomial<T>& other);
    Polynomial(Polynomial<T>&& other);
    void operator=(const Polynomial<T>& other);
    void operator=(Polynomial<T>&& other);
    ~Polynomial<T>() = default;

    int Degree() const;

    friend bool operator ==<>(const Polynomial<T>&, const Polynomial<T>&);
    friend bool operator ==<>(const Polynomial<T>&, const T&);
    friend bool operator ==<>(const T&, const Polynomial<T>&);
    friend bool operator !=<>(const Polynomial<T>&, const Polynomial<T>&);
    friend bool operator !=<>(const Polynomial<T>&, const T&);
    friend bool operator !=<>(const T&, const Polynomial<T>&);

    const T& operator [](int i) const;
    T operator()(const T& value) const;

    Polynomial<T>& operator +=(const Polynomial<T>& other);
    Polynomial<T>& operator +=(const T& other);
    Polynomial<T>& operator -=(const Polynomial<T>& other);
    Polynomial<T>& operator -=(const T& other);
    Polynomial<T>& operator *=(const Polynomial<T>& other);
    Polynomial<T>& operator *=(const T& other);

    typename std::vector<T>::const_iterator begin() const;
    typename std::vector<T>::reverse_iterator rbegin();
    typename std::vector<T>::const_iterator end() const;
    typename std::vector<T>::reverse_iterator rend();

    typename std::vector<T>::const_iterator cbegin() const;
    typename std::vector<T>::const_reverse_iterator crbegin() const;
    typename std::vector<T>::const_iterator cend() const;
    typename std::vector<T>::const_reverse_iterator crend() const;
};

template<typename T>
const T Polynomial<T>::zero = T{};

template<typename T>
void Polynomial<T>::Normalize() {
    while(this->coefficients.size() && this->coefficients.back() == T{}) {
        this->coefficients.pop_back();
    }
}

template<typename T>
Polynomial<T>::Polynomial(const std::vector<T>& coef):
    coefficients(coef)
{
    this->Normalize();
};

template<typename T>
Polynomial<T>::Polynomial(const T& coef):
    coefficients({coef})
{
    this->Normalize();
};

template<typename T>
template<typename Iter>
Polynomial<T>::Polynomial(Iter first, Iter second) {
    while(first != second) {
        coefficients.push_back(*first++);
    }
    this->Normalize();
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& other):
    coefficients(other.coefficients)
{
    this->Normalize();
};

template<typename T>
Polynomial<T>::Polynomial(Polynomial<T>&& other):
    coefficients(std::move(other.coefficients))
{
    this->Normalize();
    other.coefficients.clear();  
};

template<typename T>
void Polynomial<T>::operator=(const Polynomial<T>& other) {
    this->coefficients = other.coefficients;
}

template<typename T>
void Polynomial<T>::operator=(Polynomial<T>&& other) {
    this->coefficients = std::move(other.coefficients);
    other.coefficients.clear();
}

template<typename T>
int Polynomial<T>::Degree() const {
    return static_cast<int>(coefficients.size()) - 1;
}

template<typename T>
bool operator ==(const Polynomial<T>& poly1, const Polynomial<T>& poly2) {
    return poly1.coefficients == poly2.coefficients;
}

template<typename T>
bool operator ==(const Polynomial<T>& poly1, const T& poly2) {
    if (poly1.Degree() == -1 && poly2 == T{}) return true;
    return (poly1.Degree() == 0 && poly1[0] == poly2);
}

template<typename T>
bool operator ==(const T& poly1, const Polynomial<T>& poly2) {
    if (poly2.Degree() == -1 && poly1 == T{}) return true;
    return (poly2.Degree() == 0 && poly2[0] == poly1);
}

template<typename T>
bool operator !=(const Polynomial<T>& poly1, const Polynomial<T>& poly2) {
    return !(poly1 == poly2);
}

template<typename T>
bool operator !=(const Polynomial<T>& poly1, const T& poly2) {
    return !(poly1 == poly2);
}

template<typename T>
bool operator !=(const T& poly1, const Polynomial<T>& poly2) {
    return !(poly1 == poly2);
}

template<typename T>
const T& Polynomial<T>::operator[](int i) const {
    if (i < 0 || i > this->Degree()) {
        return Polynomial<T>::zero;
    }
    return coefficients[i];
}

template<typename T>
T Polynomial<T>::operator()(const T& value) const {
    if (this->Degree() == -1) return T{};
    T result = this->coefficients[0], base = value;
    for (auto it = std::next(this->coefficients.begin()); it != this->coefficients.end(); it++) {
        result += *it * base;
        base *= value;
    }
    return result;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& other) {
    this->coefficients.resize(std::max(this->Degree() + 1, other.Degree() + 1));
    for (int i = 0; i <= other.Degree(); i++) {
        this->coefficients[i] += other.coefficients[i];
    }
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const T& other) {
    this->coefficients.resize(std::max(this->Degree() + 1, 1));
    this->coefficients[0] += other;
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& other) {
    this->coefficients.resize(std::max(this->Degree() + 1, other.Degree() + 1));
    for (int i = 0; i <= other.Degree(); i++) {
        this->coefficients[i] -= other.coefficients[i];
    }
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-=(const T& other) {
    this->coefficients.resize(std::max(this->Degree() + 1, 1));
    this->coefficients[0] -= other;
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const Polynomial<T>& other) {
    if (this->Degree() == -1 || other.Degree() == -1) {
        this->coefficients.resize(0);
        return *this;
    }
    std::vector<T> tmp(this->Degree() + other.Degree() + 1);
    for (int i = 0; i <= other.Degree(); i++) {
        for (int j = 0; j <= this->Degree(); j++) {
            tmp[i + j] += this->coefficients[j] * other.coefficients[i];
        }
    }
    this->coefficients = std::move(tmp);
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator*=(const T& other) {
    for (auto& coef : this->coefficients) {
        coef *= other;
    }
    this->Normalize();
    return *this;
}

template<typename T>
Polynomial<T> operator+(const Polynomial<T>& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly1);
    tmp += poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator+(const Polynomial<T>& poly1, const T& poly2) {
    auto tmp(poly1);
    tmp += poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator+(const T& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly2);
    tmp += poly1;
    return tmp;
}

template<typename T>
Polynomial<T> operator-(const Polynomial<T>& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly1);
    tmp -= poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator-(const Polynomial<T>& poly1, const T& poly2) {
    auto tmp(poly1);
    tmp -= poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator-(const T& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly2);
    tmp -= poly1;
    return tmp;
}

template<typename T>
Polynomial<T> operator*(const Polynomial<T>& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly1);
    tmp *= poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator*(const Polynomial<T>& poly1, const T& poly2) {
    auto tmp(poly1);
    tmp *= poly2;
    return tmp;
}

template<typename T>
Polynomial<T> operator*(const T& poly1, const Polynomial<T>& poly2) {
    auto tmp(poly2);
    tmp *= poly1;
    return tmp;
}

template<typename T>
typename std::vector<T>::const_iterator Polynomial<T>::begin() const  {
    return this->cbegin();
}

template<typename T>
typename std::vector<T>::reverse_iterator Polynomial<T>::rbegin() {
    return this->coefficients.rbegin();
}

template<typename T>
typename std::vector<T>::const_iterator Polynomial<T>::end() const {
    return this->cend();
}

template<typename T>
typename std::vector<T>::reverse_iterator Polynomial<T>::rend() {
    return this->coefficients.rend();
}

template<typename T>
typename std::vector<T>::const_iterator Polynomial<T>::cbegin() const {
    return this->coefficients.cbegin();
}

template<typename T>
typename std::vector<T>::const_reverse_iterator Polynomial<T>::crbegin() const {
    return this->coefficients.crbegin();
}

template<typename T>
typename std::vector<T>::const_iterator Polynomial<T>::cend() const {
    return this->coefficients.cend();
}

template<typename T>
typename std::vector<T>::const_reverse_iterator Polynomial<T>::crend() const {
    return this->coefficients.crend();
}

template<typename T>
std::ostream& operator <<(std::ostream& out, const Polynomial<T>& poly) {
    for (auto it = poly.crbegin(); it != poly.crend(); it++) {
        out << *it;
        if (it != std::prev(poly.crend())) out << ' ';
    }
    return out;
} 

#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

// --- ВСТАВЬ СЮДА СВОЙ КЛАСС Polynomial<T> ---

// Вспомогательная функция: проверка вывода
std::string toString(const Polynomial<int>& p) {
    std::ostringstream oss;
    oss << p;
    return oss.str();
}

int main() {
    std::cout << "🧪 Тестирование Polynomial...\n";

    // 1. Конструктор от вектора
    std::vector<int> coeffs = {1, 2, 3}; // 1 + 2x + 3x^2
    Polynomial<int> p1(coeffs);
    std::cout << p1[0] << ' ' << p1[1] << ' ' << p1[2] << '\n';
    assert(p1[0] == 1 && p1[1] == 2 && p1[2] == 3);
    assert(p1.Degree() == 2);
    std::cout << "✅ Конструктор от вектора: " << p1 << "\n";

    // 2. Конструктор от скаляра (константа)
    Polynomial<int> p2(5); // 5
    assert(p2[0] == 5 && p2.Degree() == 0);
    std::cout << "✅ Конструктор от скаляра: " << p2 << "\n";

    // 3. Конструктор от итераторов
    std::vector<int> v = {4, 5};
    Polynomial<int> p3(v.begin(), v.end()); // 4 + 5x
    assert(p3[0] == 4 && p3[1] == 5 && p3.Degree() == 1);
    std::cout << "✅ Конструктор от итераторов: " << p3 << "\n";

    // 4. operator[] — за пределами
    assert(p1[100] == 0); // должно возвращать 0
    std::cout << "✅ operator[] за пределами: p1[100] = " << p1[100] << "\n";

    // 5. Degree() для нулевого многочлена
    Polynomial<int> zero(std::vector<int>{0, 0, 0});
    assert(zero.Degree() == -1);
    std::cout << "✅ Degree() нулевого: " << zero.Degree() << "\n";

    // 6. operator() — вычисление значения
    // p1 = 1 + 2x + 3x^2
    assert(p1(2) == 1 + 2*2 + 3*4); // 1 + 4 + 12 = 17
    std::cout << "✅ p1(2) = " << p1(2) << "\n";

    // 7. Арифметика: +, -, *
    Polynomial<int> sum = p1 + p3; // (1+4) + (2+5)x + 3x^2 = 5 + 7x + 3x^2
    assert(sum[0] == 5 && sum[1] == 7 && sum[2] == 3);
    std::cout << "✅ p1 + p3 = " << sum << "\n";

    Polynomial<int> diff = p1 - p3; // (1-4) + (2-5)x + 3x^2 = -3 -3x + 3x^2
    assert(diff[0] == -3 && diff[1] == -3 && diff[2] == 3);
    std::cout << "✅ p1 - p3 = " << diff << "\n";

    Polynomial<int> prod = p2 * p3; // 5*(4 + 5x) = 20 + 25x
    assert(prod[0] == 20 && prod[1] == 25 && prod.Degree() == 1);
    std::cout << "✅ p2 * p3 = " << prod << "\n";

    // 8. С операторами +=, -=, *=
    Polynomial<int> tmp = p1;
    tmp += p3;
    assert(tmp == sum);
    tmp = p1;
    tmp -= p3;
    assert(tmp == diff);
    tmp = p2;
    tmp *= p3;
    assert(tmp == prod);
    std::cout << "✅ +=, -=, *= работают\n";

    // 9. Сравнение с скаляром
    assert(p2 == 5);
    assert(p2 != 6);
    assert(Polynomial<int>(0) == 0);
    std::cout << "✅ Сравнение с скаляром: p2 == 5 → " << (p2 == 5) << "\n";

    // 10. Вывод: от старшей степени к младшей, через пробел
    // p1 = 1 + 2x + 3x^2 → вывод: "3 2 1"
    assert(toString(p1) == "3 2 1");
    assert(toString(p2) == "5");
    assert(toString(zero) == ""); // или "0"? но по условию — ведущие нули не учитываются
    std::cout << "✅ Вывод: p1 → \"" << p1 << "\"\n";

    // 11. begin(), end() — итерация по коэффициентам (с учётом ведущих нулей)
    // Для p1 = {1,2,3} → итерация: 1, 2, 3 (по возрастанию степени)
    std::vector<int> from_iter(p1.begin(), p1.end());
    assert(from_iter == coeffs);
    std::cout << "✅ Итерация: [";
    for (auto it = p1.begin(); it != p1.end(); ++it) {
        if (it != p1.begin()) std::cout << ", ";
        std::cout << *it;
    }
    std::cout << "] → по возрастанию степени\n";

    // 12. Нулевой многочлен — итерация должна быть пустой
    std::vector<int> zero_iter(zero.begin(), zero.end());
    assert(zero_iter.empty());
    std::cout << "✅ Итерация по нулевому многочлену — пусто\n";

    // 13. Сравнение многочленов
    Polynomial<int> p4({1,2,3});
    assert(p1 == p4);
    assert(p1 != p3);
    std::cout << "✅ Сравнение многочленов работает\n";

    std::cout << "\n🎉 Все тесты пройдены!\n";
    return 0;
}