//
// weproxy@foxmail.com 2022/10/31
//

#include "gx/strings/strings.h"
#include "gx_test.h"

void test_strings() {
    string s = " av XX av ";
    GX_LOGD("s =" << s << ";");

    GX_LOGD("strings::TrimLeft(s, \" \\t\") =" << strings::TrimLeft(s, " \t") << ";");
    GX_LOGD("strings::TrimRight(s, \" \\r\\n\") =" << strings::TrimRight(s, " \r\n") << ";");
    GX_LOGD("strings::TrimSpace(s) =" << strings::TrimSpace(s) << ";");
    GX_LOGD("strings::Trim(s, \" \") =" << strings::Trim(s, " ") << ";");
    GX_LOGD("strings::Count(s, \"av\") =" << strings::Count(s, "av") << ";");
    GX_LOGD("strings::Index(s, \"av\") =" << strings::Index(s, "av") << ";");
    GX_LOGD("strings::LastIndex(s, \"av\") =" << strings::LastIndex(s, "av") << ";");
    GX_LOGD("strings::TrimPrefix(s, \" av \") =" << strings::TrimPrefix(s, " av ") << ";");
    GX_LOGD("strings::TrimSuffix(s, \" av \") =" << strings::TrimSuffix(s, " av ") << ";");

    auto v = strings::Split(s, "XX");
    std::ostringstream ss;
    ss << "{";
    bool b = 0;
    for (auto& c : v) {
        if (!b) {
            b = 1;
        } else {
            ss << ", ";
        }
        ss << c;
    }
    ss << "}";

    GX_LOGD("strings::Split(s, \"XX\") =" << v << ";");
}

// main ...
GXTEST_main(argc, argv) {
    test_strings();
    return 0;
}
