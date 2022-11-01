--
-- weproxy@foxmail.com 2022/10/30
--

-- plat
set_config("plat", os.host())

-- project
set_project("gx")

-- set xmake minimum version
set_xmakever("2.3.1")

-- set common flags
set_languages("c++11")
set_warnings("error")

add_includedirs("3rd/coost/include")
add_includedirs("3rd/nlohmann_json/include")

includes("gx")              -- libgx.a
includes("test")            -- test
includes("unitest")         -- unitest
