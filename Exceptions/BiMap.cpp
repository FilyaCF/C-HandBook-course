#include <stdexcept>
#include <optional>
#include <memory>
#include <map>

template <typename Key1, typename Key2, typename Value>
class BiMap {
private:
    std::map<Key1, std::shared_ptr<Value>> mp1;
    std::map<Key2, std::shared_ptr<Value>> mp2;
public:
    // Вставить значение, указав один или оба ключа.
    // Генерирует исключение std::invalid_argument("some text") в случае,
    // если оба ключа пусты, либо один из ключей уже имеется в хранилище.
    void Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value);

    // Получить значение по ключу первого типа.
    // Генерирует исключение std::out_of_range("some text")
    // в случае отсутствия ключа (как и функция at в std::map).
    Value& GetByPrimaryKey(const Key1& key);
    const Value& GetByPrimaryKey(const Key1& key) const;

    // Аналогичная функция для ключа второго типа.
    Value& GetBySecondaryKey(const Key2& key);
    const Value& GetBySecondaryKey(const Key2& key) const;
};

template<typename Key1, typename Key2, typename Value>
void BiMap<Key1, Key2, Value>::Insert(const std::optional<Key1>& key1, const std::optional<Key2>& key2, const Value& value) {
    if (!key1.has_value() && !key2.has_value()) {
        throw std::invalid_argument("inv");
    } else if (key1.has_value() && mp1.count(key1.value())) {
        throw std::invalid_argument("inv");
    } else if (key2.has_value() && mp2.count(key2.value())) {
        throw std::invalid_argument("inv");
    } 
    auto ptr = std::make_shared<Value>(value);
    if (key1.has_value()) {
        mp1.insert(std::make_pair(key1.value(), ptr));
    }
    if (key2.has_value()) {
        mp2.insert(std::make_pair(key2.value(), ptr));
    }
}

template<typename Key1, typename Key2, typename Value>
Value& BiMap<Key1, Key2, Value>::GetByPrimaryKey(const Key1& key) {
    return *mp1.at(key);
}

template<typename Key1, typename Key2, typename Value>
const Value& BiMap<Key1, Key2, Value>::GetByPrimaryKey(const Key1& key) const {
    return *mp1.at(key);
}

template<typename Key1, typename Key2, typename Value>
Value& BiMap<Key1, Key2, Value>::GetBySecondaryKey(const Key2& key) {
    return *mp2.at(key);
}

template<typename Key1, typename Key2, typename Value>
const Value& BiMap<Key1, Key2, Value>::GetBySecondaryKey(const Key2& key) const {
    return *mp2.at(key);
}

#include <iostream>
#include <string>
#include <cassert>

// Предполагается, что ваш BiMap уже определён выше или включён через заголовок
// #include "bimap.h"

int main() {
    try {
        BiMap<int, std::string, std::string> students;

        // 1. Вставка с двумя ключами
        students.Insert(123, "alice", "Alice Cooper");
        students.Insert(456, "bob", "Bob Marley");

        // 2. Вставка только с первичным ключом
        students.Insert(789, std::nullopt, "Charlie Brown");

        // 3. Вставка только со вторичным ключом
        students.Insert(std::nullopt, "diana", "Diana Prince");

        // 4. Проверка получения по первичному ключу (non-const)
        assert(students.GetByPrimaryKey(123) == "Alice Cooper");
        students.GetByPrimaryKey(789) = "Charlie Chaplin"; // изменяем
        assert(students.GetByPrimaryKey(789) == "Charlie Chaplin");

        // 5. Проверка получения по вторичному ключу (non-const)
        assert(students.GetBySecondaryKey("bob") == "Bob Marley");
        students.GetBySecondaryKey("diana") = "Wonder Woman";
        assert(students.GetBySecondaryKey("diana") == "Wonder Woman");

        // 6. Проверка const-версий
        const auto& const_map = students;
        assert(const_map.GetByPrimaryKey(123) == "Alice Cooper");
        assert(const_map.GetBySecondaryKey("bob") == "Bob Marley");

        // 7. Попытка вставить с уже существующим первичным ключом → исключение
        try {
            students.Insert(123, "new_alice", "New Alice");
            assert(false && "Expected invalid_argument");
        } catch (const std::invalid_argument&) {
            // OK
        }

        // 8. Попытка вставить с уже существующим вторичным ключом → исключение
        try {
            students.Insert(999, "bob", "Another Bob");
            assert(false && "Expected invalid_argument");
        } catch (const std::invalid_argument&) {
            // OK
        }

        // 9. Попытка вставить с обоими ключами = nullopt → исключение
        try {
            students.Insert(std::nullopt, std::nullopt, "No keys");
            assert(false && "Expected invalid_argument");
        } catch (const std::invalid_argument&) {
            // OK
        }

        // 10. Получение несуществующего первичного ключа → out_of_range
        try {
            (void)students.GetByPrimaryKey(999);
            assert(false && "Expected out_of_range");
        } catch (const std::out_of_range&) {
            // OK
        }

        // 11. Получение несуществующего вторичного ключа → out_of_range
        try {
            (void)students.GetBySecondaryKey("unknown");
            assert(false && "Expected out_of_range");
        } catch (const std::out_of_range&) {
            // OK
        }

        // 12. Проверка, что можно вставить запись, где один ключ уже был использован? → НЕТ!
        // Уже проверено в п.7 и п.8 — дублирование любого ключа запрещено.

        std::cout << "✅ Все тесты пройдены!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "❌ Тест упал с исключением: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}