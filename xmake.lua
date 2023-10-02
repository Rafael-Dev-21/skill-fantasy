add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
end

target("skfantasy")
  set_kind("binary")
  add_files("src/**.cpp")
  add_includedirs("include")
  set_languages("c++11")
  if is_plat ("windows") or is_plat("mingw") then
    add_packages("pdcurses")
    add_includedirs("mingw-std-threads")
    add_ldflags("-static-libgcc", "-static-libstdc++")
  else
    add_links("ncurses")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(buildir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(buildir)/$(plat)/$(arch)/$(mode)")
  end)
