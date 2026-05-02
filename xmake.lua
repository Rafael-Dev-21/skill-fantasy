add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
  add_packages("pdcurses")
else
  add_requires("ncurses")
  add_packages("ncurses")

  package("guile-3.0")
    add_extsources("pkgconfig::guile-3.0")
  package_end()

  add_requires("guile-3.0")
end


target("skfantasy")
  set_kind("binary")
  add_files("src/**.c")
  add_includedirs("include")
  set_languages("c99")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
    add_packages("guile-3.0")
    add_defines("USE_GUILE")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/scripts", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
  add_syslinks("guile-3.0")

