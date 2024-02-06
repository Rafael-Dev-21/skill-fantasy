add_rules("mode.debug", "mode.release")

set_policy("build.ccache", false)

if is_plat ("windows") then
  add_requires("pdcurses")
end

target("skfantasy")
  set_kind("binary")
  add_files("src/**.cpp")
  add_includedirs("include")
  set_languages("c++11")
  if is_plat ("windows") then
    add_packages("pdcurses")
  else
    add_links("ncursesw", "tinfo")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(buildir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(buildir)/$(plat)/$(arch)/$(mode)")
  end)
