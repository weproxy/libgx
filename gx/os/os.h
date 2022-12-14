//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "gx/io/io.h"

namespace gx {
namespace os {

// ReadAll ...
template <typename Reader, typename std::enable_if<io::xx::has_read<Reader>::value, int>::type = 0>
R<bytez<>, error> ReadAll(Reader r) {
    return io::ReadAll(r);
}

// ReadFile ...
R<bytez<>, error> ReadFile(const string& filename);

// WriteFile ...
error WriteFile(const string& filename, const void* data, size_t size);

}  // namespace os
}  // namespace gx
