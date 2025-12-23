add_rules("mode.debug", "mode.release")

set_languages("c++23")

set_warnings("allextra", "all", "pedantic", "error")

add_includedirs("src")

--set_toolchains("clang")

--[[
if is_plat("linux", "bsd", "macosx")
then
  add_requires("ncurses")
else
  add_requires("pdcurses")
end
]]--

add_requires("raylib")

-- This is needed for termux users and does not affect others
if os.getenv("PREFIX") and os.getenv("PREFIX"):find("com.termux")
then
    add_sysincludedirs("/data/data/com.termux/files/usr/include/c++/v1")
end

target("noise")
  set_kind("static")
  add_files("src/noise/math.c", "src/noise/noise.c")
  target_end()
target("skfantasy")
  set_kind("binary")
  add_files("src/main.cpp")
  --[[
  if is_plat("linux", "bsd", "macosx")
  then
    add_packages("ncurses")
  else
    add_packages("pdcurses")
  end
  if is_plat("mingw")
  then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  ]]--
  add_deps("noise")
  add_packages("raylib")
  add_installfiles("data")
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)");
  end)
