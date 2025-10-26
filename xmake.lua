add_rules("mode.debug", "mode.release")

set_languages("gnu23")
set_warnings("allextra", "all", "pedantic", "error")

add_includedirs("include", "src")

if is_plat("linux", "bsd", "macosx")
then
  add_requires("ncurses")
else
  add_requires("pdcurses")
end

target("noise")
  set_kind("static")
  add_files("src/noise/math.c", "src/noise/noise.c")

target("skfantasy")
  set_kind("binary")
  add_files("src/game/*.c", "src/creatures/*.c", "src/modes/*.c", "src/curses/*.c")
  add_deps("noise")
  if is_plat ("linux", "bsd", "macosx")
  then
    add_packages("ncurses")
  else
    add_packages("pdcurses")
  end
  if is_plat("mingw")
  then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)

