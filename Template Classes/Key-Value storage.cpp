#include <unordered_map>
#include <algorithm>

template <typename Key, typename Value>
class KeyValueStorage {
private:
      std::unordered_map<Key, Value> data;

public:
    void Insert(const Key& key, const Value& value) {
        data[key] = value;
    }

    void Remove(const Key& key) {
        data.erase(key);
    }

    bool Find(const Key& key, Value* const value = nullptr) const;
};

template <typename Key, typename Value>
bool KeyValueStorage<Key, Value>::Find(const Key& key, Value* const value) const {
    auto it = data.find(key);
    if (value != nullptr && it != data.end())
        *value = it->second;
    return it != data.end();
};

int main() {
    KeyValueStorage<int, int> st;
    st.Insert(4, 44);
    st.Find(4);
}