//
// weproxy@foxmail.com 2022/10/31
//

#include "gx_test.h"
#include "gx/net/url/url.h"

void test_url() {
    const char* rawURL = "https://user:pass@host.com:8909/a/b?p1=a&p2=b#1234";

    AUTO_R(uri, err, url::Parse(rawURL));
    if (err) {
        GX_LOGE("err: " << err);
        return;
    }

    GX_LOGD("raw: " << rawURL);
    GX_LOGD("uri: " << uri);
}

// main ...
GXTEST_main(argc, argv) {
    test_url();
    return 0;
}
