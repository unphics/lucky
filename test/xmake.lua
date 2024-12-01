target("test")
    set_kind("binary")
    add_files("src/*.cpp")
    add_files("../out/asm.s")