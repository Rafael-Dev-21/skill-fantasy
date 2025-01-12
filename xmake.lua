add_rules("mode.debug", "mode.release")

set_policy("build.ccache", false)

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
else
  add_requires("ncurses")
end
add_requires("lua")

target("skfantasy")
  set_kind("binary")
  add_files("src/**.c")
  add_includedirs("include")
  set_languages("c99")
  add_packages("lua")
  add_ldflags("-fPIE -pie")
  if is_plat ("windows") or is_plat("mingw") then
    add_packages("pdcurses")
  else
    add_packages("ncurses")
  end
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(buildir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(buildir)/$(plat)/$(arch)/$(mode)")
  end)

