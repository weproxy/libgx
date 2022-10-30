//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "gx/gx.h"

namespace gx {
namespace hex {

// EncodeToString ...
string EncodeToString(const void* src, size_t len);
inline string EncodeToString(const bytez<>& s) { return EncodeToString(s.data(), len(s)); }
inline string EncodeToString(const string& s) { return EncodeToString(s.data(), len(s)); }

// DecodeString ...
R<bytez<>, error> DecodeString(const string& s);

}  // namespace hex
}  // namespace gx

namespace gx {
namespace unitest {
void test_hex();
}  // namespace unitest
}  // namespace gx
