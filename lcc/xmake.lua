add_rules("mode.debug", "mode.release")


target("lucky")
    set_kind("binary")
    set_languages("cxx20")
    add_includedirs("src/public/")
    add_includedirs("src")
    add_files("src/**.cc")
