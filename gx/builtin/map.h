//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

////////////////////////////////////////////////////////////////////////////////
//
namespace gx {
// map ...
template <typename K, typename V>
struct map {
    using Item = typename Map<K, V>::value_type;
    MapRef<K, V> p_{nullptr};

    // map ...
    // map() : p_(NewRef<Map<K, V>>()) {}
    map(const void* p = nil){};  // for X = nil
    map(MapRef<K, V> p) : p_(p) {}
    map(const map& r) : p_(r.p_) {}
    map(map&& r) : p_(r.p_) { r.p_ = nullptr; }

    map(std::initializer_list<Item> x) {
        p_ = NewRef<Map<K, V>>();
        for (const auto& e : x) {
            p_->operator[](e.first) = e.second;
        }
    }

    // operator =
    map& operator=(const map& r) {
        p_ = r.p_;
        return *this;
    }

    // operator =
    map& operator=(map&& r) {
        p_ = r.p_;
        r.p_ = nullptr;
        return *this;
    }

    // *
    Map<K, V>& operator*() { return *p_; }
    const Map<K, V>& operator*() const { return *p_; }

    // ->
    MapRef<K, V>& operator->() { return p_; }
    const MapRef<K, V>& operator->() const { return p_; }

    // [k]
    V& operator[](const K& k) { return p_->operator[](k); }
    const V& operator[](const K& k) const { return p_->operator[](k); }

    // auto [v, ok] = map(key);
    // likes golang:
    //    v, ok := map[key]
    R<V, bool> operator()(const K& k) const {
        if (p_) {
            auto it = p_->find(k);
            if (it != p_->end()) {
                return {it->second, true};
            }
        }
        return {{}, false};
    }

    // Del ...
    void Del(const K& k) const {
        if (p_) {
            p_->erase(k);
        }
    }

    // size ...
    int size() const { return p_ ? p_->size() : 0; }

    // bool() ...
    operator bool() const { return !!p_; }

    // x == nil or x != nil
    bool operator==(const void* p) const { return p == nil && !!p_; }
    bool operator!=(const void* p) const { return p == nil && p_; }

   public:
    // String ...
    string String() const {
        if (size() == 0) {
            return "{}";
        }

        std::ostringstream ss;
        ss << "{";
        int i = 0;
        for (auto& p : *p_) {
            if (i++) {
                ss << ", ";
            }
            _out_item(ss, p.first) << ":";
            _out_item(ss, p.second);
        }
        ss << "}";

        return ss.str();
    }

   public:
    using iterator = typename Map<K, V>::iterator;

    iterator begin() { return p_ ? p_->begin() : _nil().begin(); }
    iterator end() { return p_ ? p_->begin() : _nil().end(); }
    const iterator begin() const { return p_ ? p_->begin() : _nil().begin(); }
    const iterator end() const { return p_ ? p_->begin() : _nil().end(); }

    iterator rbegin() { return p_ ? p_->rbegin() : _nil().rbegin(); }
    iterator rend() { return p_ ? p_->rbegin() : _nil().rend(); }
    const iterator rbegin() const { return p_ ? p_->rbegin() : _nil().rbegin(); }
    const iterator rend() const { return p_ ? p_->rbegin() : _nil().rend(); }

   private:
    static Map<K, V>& _nil() {
        static Map<K, V> v;
        return v;
    }
};

// makemap ...
template <typename K, typename V>
map<K, V> makemap() {
    return map<K, V>(NewRef<Map<K, V>>());
}

template <typename K, typename V>
void delmap(map<K, V>& m, const K& k) {
    m.Del(k);
}

// len ...
template <typename K, typename V>
int len(const map<K, V>& m) {
    return m.size();
}

}  // namespace gx
