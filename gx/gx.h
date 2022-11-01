//
// weproxy@foxmail.com 2022/10/03
//

#pragma once

#include "builtin/builtin.h"

////////////////////////////////////////////////////////////////////////////////
//
#ifndef _TCLEAN_
#define _TCLEAN_ "\033[0m"
#define _TWEAK_ "\033[2m"
#define _TULINE_ "\033[4m"

#define _TBLACK_ "\033[30m"
#define _TRED_ "\033[31m"
#define _TGREEN_ "\033[32m"
#define _TYELLOW_ "\033[33m"
#define _TBLUE_ "\033[34m"
#define _TMAGENTA_ "\033[35m"
#define _TCYAN_ "\033[36m"
#define _TWHITE_ "\033[37m"
#endif

// _GX_LOG ...
#define _GX_LOG(tag, color, ...)                                                    \
    do {                                                                            \
        std::ostringstream _ss_;                                                    \
        _ss_ << _TCLEAN_ _TWEAK_ << __FILE__ << ":" << __LINE__ << " " << _TCLEAN_; \
        _ss_ << tag << color << __VA_ARGS__ << _TCLEAN_ << std::endl;               \
        std::cout << _ss_.str();                                                    \
    } while (0)

#define GX_LOGD(...) _GX_LOG("[D] ", _TWHITE_, __VA_ARGS__)
#define GX_LOGI(...) _GX_LOG("[I] ", _TGREEN_, __VA_ARGS__)
#define GX_LOGW(...) _GX_LOG("[W] ", _TYELLOW_, __VA_ARGS__)
#define GX_LOGE(...) _GX_LOG("[E] ", _TRED_, __VA_ARGS__)
#define GX_LOGV(...) _GX_LOG("[V] ", _TCYAN_ _TWEAK_, __VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
// _GX_main ...
#define _GX_main(gxfn, argc, argv)     \
    int gxfn(int argc, char* argv[]);  \
    int main(int argc, char* argv[]) { \
        int r;                         \
        gx::sync::WaitGroup wg(1);     \
        gx::go([&]() {                 \
            DEFER(wg.Done());          \
            r = gxfn(argc, argv);      \
        });                            \
        wg.Wait();                     \
        return r;                      \
    }                                  \
    int gxfn(int argc, char* argv[])

#define GX_main(argc, argv) _GX_main(_gx_main, argc, argv)
#define GXTEST_main(argc, argv) _GX_main(_gxtest_main, argc, argv)
#define GXUNITEST_main(argc, argv) _GX_main(_gxunitest_main, argc, argv)
