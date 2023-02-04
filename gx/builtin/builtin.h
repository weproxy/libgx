//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include <stdint.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <sstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
//
namespace gx {
// int ...
typedef int8_t int8;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef uint32_t uint;
typedef uint8_t byte;

typedef int32 rune;
}  // namespace gx

// gx_TodoErr ...
#define gx_TodoErr() fmt::Errorf("<TODO> %s:%d %s", __FILE__, __LINE__, __FUNCTION__)

////////////////////////////////////////////////////////////////////////////////
namespace gx {
// _out_item ...
inline std::ostream& _out_item(std::ostream& s, unsigned char c) {
    char b[8];
    if (' ' <= c && c <= '~') {
        ::snprintf(b, sizeof(b), "'%c'", (char)c);
    } else if (c == '\n') {
        ::snprintf(b, sizeof(b), "'\\n'");
    } else if (c == '\r') {
        ::snprintf(b, sizeof(b), "'\\r'");
    } else if (c == '\t') {
        ::snprintf(b, sizeof(b), "'\\t'");
    } else {
        ::snprintf(b, sizeof(b), "%d", c);
    }
    return s << (const char*)b;
}

// _out_item ...
inline std::ostream& _out_item(std::ostream& s, char c) { return _out_item(s, (unsigned char)c); }

// _out_item ...
inline std::ostream& _out_item(std::ostream& s, const std::string& t) { return s << "\"" << t << "\""; }

// _out ...
template <typename T>
std::ostream& _out_item(std::ostream& s, const T& t) {
    return s << t;
}
}  // namespace gx

#include "autor.h"
#include "chan.h"
#include "def.h"
#include "defer.h"
#include "go.h"
#include "map.h"
#include "slice.h"
#include "util.h"
