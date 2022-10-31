//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"

// test_chan ...
void test_chan() {
    auto c = makechan<string>(10);

    gx::go([c] {
        c << "A";
        c << "B";
    });

    string a, b;
    c >> a;
    c >> b;
    GX_LOGD("a=" << a << ", b=" << b);
}

// main ...
GXTEST_main(argc, argv) {
    test_chan();
    return 0;
}
