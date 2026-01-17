add_rules("mode.debug", "mode.release")

target("skfantasy")
  set_kind("binary")
  add_files("src/game.c", "src/lut.c", "src/memory.c")
  set_languages("c99")
 if is_plat("mingw") or is_plat("windows") then
    add_ldflags("-mwindows")
    add_links("kernel32", "user32", "gdi32");
    add_files("src/win32-main.c")
  else
    add_links("X11")
    add_files("src/x11-main.c")
  end
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
