add_rules("mode.debug", "mode.release")

set_policy("build.ccache", false)

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
end

target("skfantasy")
  set_kind("binary")
  add_files("src/**.c")
  add_includedirs("include")
  set_languages("c11")
  if is_plat ("windows") or is_plat("mingw") then
    add_packages("pdcurses")
  else
    add_links("ncursesw", "tinfo", "m")
  end
  if is_plat("mingw") then
    add_ldflags("-static-libgcc")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(buildir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(buildir)/$(plat)/$(arch)/$(mode)")
  end)
