//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"
#include "gx/encoding/hex/hex.h"

void test_hex() {
    const string s = "hello";
    GX_LOGD("s =" << s);

    string s1 = hex::EncodeToString(s);
    GX_LOGD("hex::EncodeToString(s) =" << s1);

    AUTO_R(s2, err, hex::DecodeString(s1));
    if (err) {
        GX_LOGD("hex::DecodeString(s1) err: " << err);
    } else {
        GX_LOGD("hex::DecodeString(s1) =" << string(s2));
    }
}

// main ...
GXTEST_main(argc, argv) {
    test_hex();
    return 0;
}
