add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
  add_packages("pdcurses")
else
  add_requires("ncurses")
  add_packages("ncurses")
end


target("skfantasy")
  set_kind("binary")
  set_warnings("all", "pedantic", "allextra", "error")
  add_files("src/*.c", "src/creatures/*.c", "src/modes/*.c")
  add_includedirs("include")
  set_languages("c23")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  after_build(function(target)
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
