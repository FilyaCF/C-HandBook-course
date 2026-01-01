#include <iostream>
#include <vector>

template<typename T>
class Table {
private:
    size_t columns, rows;
    std::vector<std::vector<T>> data;
public:
    Table(const size_t rows, const size_t columns):
        columns(columns),
        rows(rows)
    {
        data.assign(rows, std::vector<T>(columns));
    }

    const std::vector<T>& operator[](const size_t r) const {
        return data[r];
    }

    std::vector<T>& operator[](const size_t r) {
        return data[r];
    }

    void resize(const size_t rows, const size_t columns) {
        this->rows = rows;
        this->columns = columns;
        data.resize(rows);
        for (auto& row : data) {
            row.resize(columns);
        }
    }

    std::pair<size_t, size_t> size() const {
        return std::make_pair(rows, columns);
    }
};

int main() {
    // 1. Создаём таблицу int 3x2
    Table<int> table(3, 2);

    // 2. Проверяем size()
    auto sz = table.size();
    std::cout << "Размер: " << sz.first << " x " << sz.second << '\n';

    // 3. Заполняем значениями через operator[]
    table[0][0] = 10;
    table[0][1] = 20;
    table[1][0] = 30;
    table[1][1] = 40;
    table[2][0] = 50;
    table[2][1] = 60;

    // 4. Выводим через const operator[]
    const Table<int>& const_table = table; // делаем константную ссылку
    for (size_t i = 0; i < const_table.size().first; ++i) {
        for (size_t j = 0; j < const_table.size().second; ++j) {
            std::cout << const_table[i][j] << ' ';
        }
        std::cout << '\n';
    }

    // 5. Изменяем размер — увеличиваем до 4x3
    table.resize(4, 3);

    // 6. Проверяем, что старые данные сохранились
    std::cout << "\nПосле resize(4,3):\n";
    for (size_t i = 0; i < table.size().first; ++i) {
        for (size_t j = 0; j < table.size().second; ++j) {
            if (i < 3 && j < 2) {
                std::cout << table[i][j] << ' '; // должно быть 10,20,30,40,50,60
            } else {
                std::cout << '.' << ' '; // новые ячейки — по умолчанию (0 для int)
            }
        }
        std::cout << '\n';
    }

    // 7. Проверка изменения через non-const operator[]
    table[3][2] = 999;
    std::cout << "\nУстановили table[3][2] = 999\n";
    std::cout << "table[3][2] = " << table[3][2] << '\n';

    // 8. Проверка размера после resize
    sz = table.size();
    std::cout << "Текущий размер: " << sz.first << " x " << sz.second << '\n';

    return 0;
}