//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "def.h"
#include "xx.h"

////////////////////////////////////////////////////////////////////////////////
//
// override std::ostream <<
namespace std {
#if 0
// to_string ...
template <typename T, typename std::enable_if<gx::xx::has_string<T>::value, int>::type = 0>
string to_string(T t) {
    return gx::xx::to_string(t);
}
#endif

// << byte
inline std::ostream& operator<<(std::ostream& s, unsigned char c) { return gx::_out_item(s, c); }

// << char
inline std::ostream& operator<<(std::ostream& s, char c) { return operator<<(s, (unsigned char)c); };

// if has .String()
// if has .operator string()
// if has ->String()
// if has ->operator string()
template <typename T, typename std::enable_if<gx::xx::has_string<T>::value, int>::type = 0>
std::ostream& operator<<(std::ostream& s, T t) {
    return s << gx::xx::to_string(t);
};

}  // namespace std

// override std::ostream <<
#define GX_DEC_OSTREAM_REF(Obj) \
    inline std::ostream& operator<<(std::ostream& out, const Obj obj) { return out << obj.String(); }

// override std::ostream <<
#define GX_DEC_OSTREAM_PTR(Obj) \
    inline std::ostream& operator<<(std::ostream& out, const Obj obj) { return out << (obj ? obj->String() : "<nil>"); }

#define GX_SS(...)               \
    [&] {                        \
        std::ostringstream _ss_; \
        _ss_ << __VA_ARGS__;     \
        return _ss_.str();       \
    }()

////////////////////////////////////////////////////////////////////////////////
//
namespace gx {
// tostr ...
template <typename... T>
string tostr(T&&... t) {
    std::ostringstream _ss_;
    xx::out(_ss_, std::forward<T>(t)...);
    return _ss_.str();
}

// print ...
template <typename... T>
void print(T&&... t) {
    std::ostringstream _ss_;
    xx::out(_ss_, std::forward<T>(t)...);
    std::cout << _ss_.str();
}

// println ...
template <typename... T>
void println(T&&... t) {
    std::ostringstream _ss_;
    xx::out(_ss_, std::forward<T>(t)...);
    _ss_ << std::endl;
    std::cout << _ss_.str();
}

// panic ...
template <typename... T>
void panic(T&&... t) {
    std::ostringstream _ss_;
    xx::out(_ss_, std::forward<T>(t)...);
    std::cout << _ss_.str();
    throw(_ss_);
}

}  // namespace gx

////////////////////////////////////////////////////////////////////////////////
// override std::ostream <<
namespace std {
template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::Vec<T>& t) {
    int i = 0;
    s << "[";
    for (auto& c : t) {
        if (i++) {
            s << ", ";
        }
        gx::_out_item(s, c);
    }
    return s << "]";
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::VecRef<T>& t) {
    return s << *t;
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::Set<T>& t) {
    int i = 0;
    s << "{";
    for (auto& c : t) {
        if (i++) {
            s << ", ";
        }
        gx::_out_item(s, c);
    }
    return s << "}";
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::SetRef<T>& t) {
    return s << *t;
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::List<T>& t) {
    int i = 0;
    s << "{";
    for (auto& c : t) {
        if (i++) {
            s << ", ";
        }
        gx::_out_item(s, c);
    }
    return s << "}";
}

template <typename T>
std::ostream& operator<<(std::ostream& s, const gx::ListRef<T>& t) {
    return s << *t;
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& s, const gx::Map<K, V>& t) {
    int i = 0;
    s << "{";
    for (auto& c : t) {
        if (i++) {
            s << ", ";
        }
        gx::_out_item(s, c.first) << ":";
        gx::_out_item(s, c.second);
    }
    return s << "}";
}

template <typename K, typename V>
std::ostream& operator<<(std::ostream& s, const gx::MapRef<K, V>& t) {
    return s << *t;
}
}  // namespace std
