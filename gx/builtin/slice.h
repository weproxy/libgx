//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "xx.h"

////////////////////////////////////////////////////////////////////////////////
//
namespace gx {
// slice ...
template <typename T = byte>
struct slice {
    int beg_{0}, len_{0};
    VecRef<T> p_{nullptr};

    slice(const void* p = nil){};  // for x = nil
    slice(const slice& r) : beg_(r.beg_), len_(r.len_), p_(r.p_) {}
    slice(slice&& r) : beg_(r.beg_), len_(r.len_), p_(r.p_) { r._reset(); }
    explicit slice(int len, int cap = 0) : len_(len), p_(NewRef<Vec<T>>(len)) {
        if (cap > len) {
            p_->reserve(cap);
        }
    }
    slice(std::initializer_list<T> x) : slice(0, x.size()) {
        p_->insert(p_->begin(), x.begin(), x.end());
        len_ += x.size();
    }

    // operator [i] ...
    T& operator[](int i) { return p_->operator[](beg_ + i); }
    const T& operator[](int i) const { return p_->operator[](beg_ + i); }

    // Sub ...
    slice Sub(int beg, int end = -1) const {
        slice r;
        int begt = beg_ + (beg < 0 ? 0 : beg);
        int lent = beg_ + (end < 0 ? len_ : end) - begt;
        if (lent >= 0 && begt <= (beg_ + len_) && (begt + lent) <= (beg_ + len_)) {
            r.beg_ = begt;
            r.len_ = lent;
            r.p_ = p_;
        }
        return r;
    }

    // operator (beg, end), likes golang [beg:end]
    slice operator()(int beg, int end = -1) const { return Sub(beg, end); }

    // operator =
    slice& operator=(const slice& r) {
        assign(r);
        return *this;
    }

    // // operator =
    // slice& operator=(slice&& r) {
    //     assign(r);
    //     r._reset();
    //     return *this;
    // }

    // bool() ...
    operator bool() const { return !!p_; }

    // for x == nil or x != nil
    bool operator==(const void* p) const { return p == nil && !!p_; }
    bool operator!=(const void* p) const { return p == nil && p_; }

    // data ...
    T* data() { return p_ ? (p_->data() + beg_) : 0; }
    const T* data() const { return p_ ? (p_->data() + beg_) : 0; }

    // T*() ...
    operator T*() { return data(); }
    operator const T*() const { return data(); }

#if 1
   public:  // for slice<byte> <--> string
    // template <typename X = byte, typename std::enable_if<xx::is_same<X, gx::byte>::value, int>::type = 0>
    slice<T>(string&& s) : slice<T>(s.length(), s.length() + 1) {
        memcpy(data(), s.data(), s.length());
        this->operator[](len_) = 0;
    }

    // template <typename X = byte, typename std::enable_if<xx::is_same<X, gx::byte>::value, int>::type = 0>
    slice<T>(const string& s) : slice<T>(s.length(), s.length() + 1) {
        memcpy(data(), s.data(), s.length());
        this->operator[](len_) = 0;
    }

    // template <typename X = byte, typename std::enable_if<xx::is_same<X, gx::byte>::value, int>::type = 0>
    slice<T>(const char* s) : slice<T>((s && s[0]) ? strlen(s) : 0, (s && s[0]) ? (strlen(s) + 1) : 1) {
        if (s && s[0]) {
            memcpy(data(), s, strlen(s));
        }
        this->operator[](len_) = 0;
    }

    // template <typename X = byte, typename std::enable_if<xx::is_same<X, gx::byte>::value, int>::type = 0>
    operator string() {
        return string((char*)data(), len_ * sizeof(T));
    }

    template <typename X = byte, typename std::enable_if<xx::is_same<X, gx::byte>::value, int>::type = 0>
    operator string() const {
        return string((char*)data(), len_ * sizeof(T));
    }
#endif

   public:
    // String ...
    string String() const {
        if (!operator bool() || len_ <= 0) {
            return "[]";
        }

        std::ostringstream ss;
        ss << "[";
        for (int i = beg_; i < (beg_ + len_); i++) {
            if (i != beg_) {
                ss << " ";
            }
            _out_item(ss, p_->operator[](i));
        }
        ss << "]";

        return ss.str();
    }

   public:
    // _create_if_null ...
    void _create_if_null(int len = 0) {
        if (!p_) {
            p_ = NewRef<Vec<T>>(len);
        }
    }

    // assign ...
    void assign(const slice& r) {
        p_ = r.p_;
        beg_ = r.beg_;
        len_ = r.len_;
    }

    // assign ...
    void assign(const T* p, int len) {
        _create_if_null(len);
        p_->insert(p_->begin() + beg_, p, p + len);
        len_ += len;
    }

    // _reset ...
    void _reset() {
        p_ = nullptr;
        beg_ = 0;
        len_ = 0;
    }

   public:
    using iterator = typename Vec<T>::iterator;

    iterator begin() { return p_ ? p_->begin() + beg_ : _nil().begin(); }
    iterator end() { return p_ ? p_->begin() + beg_ + len_ : _nil().end(); }
    const iterator begin() const { return p_ ? p_->begin() + beg_ : _nil().begin(); }
    const iterator end() const { return p_ ? p_->begin() + beg_ + len_ : _nil().end(); }

   private:
    static Vec<T>& _nil() {
        static Vec<T> v;
        return v;
    }
};

// bytez ...
template <typename T = byte>
using bytez = slice<T>;

// stringz ...
template <typename T = string>
using stringz = slice<T>;

////////////////////////////////////////////////////////////////////////////////
// append ...
namespace xx {
template <typename T>
inline void append(slice<T>&) {}

// append ...
template <typename T = byte, typename V = byte, typename... X>
void append(slice<T>& dst, V&& v, X&&... x) {
    // std::cout << "slice::append(v)" << std::endl;
    auto& vec = dst.p_;
    auto it = vec->begin() + dst.beg_ + dst.len_;
    if (it < vec->end()) {
        *it = std::forward<V>(v);
    } else {
        vec->insert(it, std::forward<V>(v));
    }
    dst.len_++;
    append(dst, std::forward<X>(x)...);
}

template <typename T = byte, typename... X>
void append(slice<T>& dst, X&&... x) {
    // std::cout << "slice::append(...)" << std::endl;
    append(dst, std::forward<X>(x)...);
}
}  // namespace xx

////////////////////////////////////////////////////////////////////////////////
//
// make ...
template <typename T = byte>
slice<T> make(int len = 0, int cap = 0) {
    return slice<T>(len, cap);
}

// len ...
inline int len(const string& s) { return s.length(); }

// len ...
template <typename T = byte>
int len(const slice<T>& s) {
    return s.len_;
}

// cap ...
template <typename T = byte>
int cap(const slice<T>& s) {
    return s.p_ ? (s.p_->capacity() - s.beg_ - s.len_) : 0;
}

// append ...
inline bytez<> append(const bytez<>& dst, const string& src) {
    bytez<> s(dst);
    if (!src.empty()) {
        s._create_if_null();
        s.p_->insert(s.p_->begin() + s.beg_ + s.len_, src.begin(), src.end());
        s.len_ += len(src);
    }
    return s;
}

// append ...
template <typename T = byte>
slice<T> append(const slice<T>& dst, const slice<T>& src) {
    slice<T> s(dst);
    if (len(src) > 0) {
        s._create_if_null();
        for (int i = 0; i < len(src); i++) {
            s.p_->insert(s.p_->begin() + s.beg_ + s.len_ + i, src[i]);
        }
        s.len_ += len(src);
    }
    return s;
}

// append ...
template <typename T = byte, typename V = byte, typename... X>
slice<T> append(const slice<T>& dst, const V& v, X&&... x) {
    slice<T> s(dst);
    s._create_if_null();
    xx::append(s, v);
    if (sizeof...(x) > 0) {
        xx::append<T>(s, std::forward<X>(x)...);
    }
    return s;
}

// copy ...
inline int copy(bytez<>& dst, const string& src) {
    int i = 0;
    for (; i < len(dst) && i < len(src); i++) {
        dst[i] = src[i];
    }
    return i;
}

// // copy ...
// inline int copy(bytez<>&& dst, const string& src) {
//     int i = 0;
//     for (; i < len(dst) && i < len(src); i++) {
//         dst[i] = src[i];
//     }
//     return i;
// }

// copy ...
template <typename T = byte>
int copy(slice<T>& dst, const slice<T>& src) {
    int i = 0;
    for (; i < len(dst) && i < len(src); i++) {
        dst[i] = src[i];
    }
    return i;
}

// copy ...
template <typename T = byte>
int copy(slice<T>& dst, const void* src, int n) {
    int i = 0;
    const T* r = (const T*)src;
    for (; i < len(dst) && i < n; i++) {
        dst[i] = r[i];
    }
    return i;
}

// copy ...
template <typename T = byte>
int copy(slice<T>&& dst, const slice<T>& src) {
    int i = 0;
    for (; i < len(dst) && i < len(src); i++) {
        dst[i] = src[i];
    }
    return i;
}

// copy ...
template <typename T = byte>
int copy(slice<T>&& dst, const void* src, int n) {
    int i = 0;
    const T* r = (const T*)src;
    for (; i < len(dst) && i < n; i++) {
        dst[i] = r[i];
    }
    return i;
}

}  // namespace gx
