--
-- weproxy@foxmail.com 2022/10/03
--

-- target
target("gx")
    set_kind("static")
    add_files("**.cc|**_test.cc|**unused**")
target_end()