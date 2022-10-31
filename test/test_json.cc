//
// weproxy@foxmail.com 2022/10/31
//

#include "gx/encoding/json/json.h"
#include "gx_test.h"

// auth_t ...
struct auth_t {
    string s5;
    string ss;
};

// server_t ...
struct server_t {
    auth_t auth;
    strvec tcp;
    strvec udp;
    Map<string, strvec> geo;
};

// rule_t ...
struct rule_t {
    strvec host;
    strvec serv;
};

// conf_t ...
struct conf_t {
    server_t server;
    Vec<rule_t> rules;

    // String ...
    string String() const {
        AUTO_R(str, err, gx::json::Marshal(*this));
        return err ? "{}" : str;
    }
    operator string() const { return String(); }

    // Parse ...
    error Parse(const string& js) {
        // parse
        return gx::json::Unmarshal(js, this);
    }

   private:
    Vec<rule_t> dnsRules;
    Vec<rule_t> netRules;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(auth_t, s5, ss)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(server_t, auth, tcp, udp, geo)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(rule_t, host, serv)
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(conf_t, server, rules)

void test_json() {
    conf_t c;

    c.server.auth.s5 = "s5user:s5pass";
    c.server.auth.ss = "ssuser:sspass";

    c.server.tcp.push_back("s5://1.2.3.4");
    c.server.geo["cn"].push_back("s5://1.2.3.4");
    c.server.geo["us"].push_back("s5://1.2.3.4");

    rule_t r;
    r.host.push_back("a.com");
    r.serv.push_back("default");
    c.rules.push_back(r);

    GX_LOGD("org: " << c);

    conf_t cc;
    auto err = cc.Parse(c);
    if (err) {
        GX_LOGE(err);
    } else {
        GX_LOGD("dec: " << c);
    }
}

// main ...
GXTEST_main(argc, argv) {
    test_json();
    return 0;
}
