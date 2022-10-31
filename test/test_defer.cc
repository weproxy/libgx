//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"

// test_defer ...
void test_defer() {
    Defer defer;

    DEFER(GX_LOGD("A exit"));
    defer([] { GX_LOGD("A0"); });
    defer([] { GX_LOGD("A1"); });

    {
        DEFER(std::cout << "B exit" << std::endl);
        defer([] { GX_LOGD("B0"); });
        defer([] { GX_LOGD("B1"); });
    }

    for (int i = 0; i < 2; i++) {
        DEFER(std::cout << "C" << i << " exit" << std::endl);
        defer([i]() { GX_LOGD("C" << i); });
    }
}

// main ...
GXTEST_main(argc, argv) {
    test_defer();
    return 0;
}
