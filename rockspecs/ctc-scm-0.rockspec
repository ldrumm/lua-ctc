build = {
    modules = {
        ctc = "src/ctc.c",
    },
    type = "builtin",
}

dependencies = {
    "lua >= 5.1",
}

description = {
    summary = "Constant time string comparisons for Lua",
    license = "MIT",
    detailed = [[Safe string comparison to avoid timing attack when comparing cryptographically sensitive string data.
    ]],
    homepage = "https://github.com/ldrumm/lua-ctc",
}

source = {
    url = "https://github.com/ldrumm/lua-ctc/archive/master.zip",
    dir = "lua-ctc-master",
}
