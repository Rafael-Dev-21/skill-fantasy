add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
  add_packages("pdcurses")
else
  add_requires("ncurses")
  add_packages("ncurses")
end

add_requires("flecs")
add_packages("flecs")

target("skfantasy")
  set_kind("binary")
  add_files("src/**.c")
  set_languages("c99")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)

