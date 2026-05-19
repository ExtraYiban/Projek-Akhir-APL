set_project("Sistem-Penyewaan-iPhone")
set_version("1.0.0")
set_languages("c++17")

add_requires("tabulate")

if is_mode("debug") then
    add_defines("DEBUG")
    set_symbols("debug")
end

target("app")
    set_kind("binary")
    add_includedirs("includes")
    add_files("main.cpp", "modules/*.cpp", "utils/*.cpp")
    add_packages("tabulate")
    set_targetdir("bin")
    set_rundir(".")
