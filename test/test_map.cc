//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"

#define PRINT_MAP(s) GX_LOGD(#s "=" << s);

// test_map ...
void test_map() {
    map<string, int> m1 = {
        {"a", 1},
        {"b", 2},
        {"c", 3},
    };
    PRINT_MAP(m1);

    map<int, string> m2 = {
        {1, "a"},
        {2, "b"},
        {3, "c"},
    };
    PRINT_MAP(m2);
}

// main ...
GXTEST_main(argc, argv) {
    test_map();
    return 0;
}
