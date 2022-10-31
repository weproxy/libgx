function all_tests()
    local res = {}
    for _, x in ipairs(os.files("unitest_*.cc")) do
        local item = {}
        local s = path.filename(x)
        table.insert(item, s:sub(1, #s - 3))       -- target
        table.insert(item, path.relative(x, "."))  -- source
        table.insert(res, item)
    end
    return res
end

for _, test in ipairs(all_tests()) do
    target(test[1])
        if test[1] == "stack" then
            set_symbols("debug")    -- dbg symbols
            set_optimize("none")
        end
        set_kind("binary")
        set_default(false)
        add_deps("libco")
        add_deps("libgx")
        add_files(test[2])
    target_end()
end
