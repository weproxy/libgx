--
-- weproxy@foxmail.com 2022/10/03
--

-- set xmake minimum version
set_xmakever("2.3.1")

-- set common flags
set_languages("c++11")
set_warnings("error")     -- -Wall

add_includedirs("3rd/coost/include")
add_includedirs("3rd/nlohmann_json/include")

includes("gx")              -- libgx.a
includes("3rd/coost")       -- libco.a
