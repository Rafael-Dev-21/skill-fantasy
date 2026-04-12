add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
  add_packages("pdcurses")
else
  add_requires("ncurses")
  add_packages("ncurses")
end

set_languages("c99")

target("core")
  set_kind("static")
  add_files("src/noise.c", "src/util.c")

target("skfantasy")
  set_kind("binary")
  add_files("src/main.c")
  add_deps("core")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
target_end()
