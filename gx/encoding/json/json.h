//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "gx/errors/errors.h"

// switch off exceptions
#define JSON_TRY_USER if (true)
#define JSON_CATCH_USER(exception) if (false)
#define JSON_THROW_USER(exception) std::abort()
#include "nlohmann/json.hpp"

namespace gx {
namespace json {

// J ...
using J = nlohmann::json;

// Parse ...
inline R<J, error> Parse(const string& s) {
    try {
        auto j = J::parse(s);
        return {j, nil};
    } catch (J::exception& e) {
        return {nil, errors::New(e.what())};
    } catch (std::exception& e) {
        return {nil, errors::New(e.what())};
    } catch (...) {
        return {nil, errors::New("parse fail")};
    }
}

// Marshal ...
template <typename T>
R<string, error> Marshal(T& v) {
    try {
        J j = v;
        auto s = j.dump();
        return {s, nil};
    } catch (J::exception& e) {
        return {{}, errors::New(e.what())};
    } catch (std::exception& e) {
        return {{}, errors::New(e.what())};
    } catch (...) {
        return {{}, errors::New("parse fail")};
    }
}

// Unmarshal ...
template <typename T>
error Unmarshal(const string& s, T* v) {
    try {
        auto j = J::parse(s);
        *v = j.get<T>();
        return nil;
    } catch (J::exception& e) {
        return errors::New(e.what());
    } catch (std::exception& e) {
        return errors::New(e.what());
    } catch (...) {
        return errors::New("parse fail");
    }
}

// Get safe get
inline J Get(const J& j, const string& k) {
    if (j.find(k) != j.end()) {
        return j[k];
    }
    return J();
}

}  // namespace json
}  // namespace gx
