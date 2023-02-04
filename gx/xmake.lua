--
-- weproxy@foxmail.com 2022/10/03
--

includes("../3rd/coost/src")   -- libco.a

-- target
target("libgx")
    set_kind("static")
    set_basename("gx")
    add_files("**.cc|**_test.cc|**unused**")
    add_files("**.cpp|**_test.cpp|**unused**")
    add_files("**.cxx|**_test.cxx|**unused**")
    add_deps("libco")
target_end()
