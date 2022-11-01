//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"

#define PRINT_SLICE(s) GX_LOGD("len(" #s ")=" << len(s) << ", " #s "=" << s);

// test_slice ...
void test_slice() {
    byte n1 = '\n', n2 = '\r', n3 = ' ';
    int n4 = -2;
    GX_LOGD("n1=" << n1);
    GX_LOGD("n2=" << n2);
    GX_LOGD("n3=" << n3);
    GX_LOGD("n4=" << n4);

    bytez<> s1 = make<byte>(0, 100);
    bytez<> s2 = append(s1, '$', 'b', 'c', 'x', 'y', 'z');
    bytez<> s3 = {4, 5, '6', '&', '8', '9'};
    // bytez<> s3 = {'4'};
    // PRINT_SLICE(s3);
    bytez<> s4 = s3(2, 3);
    bytez<> s5 = append(s4, 'e', 'f');
    bytez<> s6 = s5;
    copy(s6, s2);

    PRINT_SLICE(s1);
    PRINT_SLICE(s2);
    PRINT_SLICE(s3);
    PRINT_SLICE(s4);
    PRINT_SLICE(s5);
    PRINT_SLICE(s6);

    bytez<> bs("ssss");
    PRINT_SLICE(bs);

    stringz<> ss = {"aaa", "bbb", "ccc"};
    PRINT_SLICE(ss);
}

// main ...
GXTEST_main(argc, argv) {
    test_slice();
    return 0;
}
