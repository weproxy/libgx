//
// weproxy@foxmail.com 2022/10/03
//

#include "fmt.h"

#include "gx/errors/errors.h"

namespace gx {
namespace fmt {

#ifdef _WIN32
int vasprintf(char** ptr, const char* format, va_list ap) {
    int len = _vscprintf_p(format, ap) + 1;
    *ptr = (char*)malloc(len * sizeof(char));
    if (!ptr) {
        return -1;
    }
    return _vsprintf_p(*ptr, len, format, ap);
}
#endif

// format ...
static string format(const char* fmt, va_list& ap) {
    string s;

    char* ptr = 0;
    int len = vasprintf(&ptr, fmt, ap);
    if (ptr) {
        s.assign(ptr, len);
        std::free(ptr);
    }

    return s;
}

// Sprintf ...
string Sprintf(const char* fmt, ...) {
    if (!fmt || !fmt[0]) {
        return "";
    }

    va_list ap;
    va_start(ap, fmt);
    string s = format(fmt, ap);
    va_end(ap);

    return s;
}

// Errorf ...
error Errorf(const char* fmt, ...) {
    if (!fmt || !fmt[0]) {
        return errors::New("error");
    }

    va_list ap;
    va_start(ap, fmt);
    string s = format(fmt, ap);
    va_end(ap);

    return errors::New(s);
}

}  // namespace fmt
}  // namespace gx
