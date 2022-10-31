--
-- weproxy@foxmail.com 2022/10/03
--

includes("../3rd/coost/src")   -- libco.a

-- target
target("libgx")
    set_kind("static")
    set_basename("gx")
    add_files("**.cc|**_test.cc|**unused**")
    add_deps("libco")
target_end()
