add_rules("mode.debug", "mode.release")

target("skfantasy")
  set_kind("binary")
  add_files(
    "../common/game.c",
    "../common/memory.c",
    "../common/chain.c",
    "../common/model.c",
    "../common/render.c",
    "../common/surface.c",
    "../common/obj_pose.c")
  add_includedirs("../common")
  set_languages("c99")
 if is_plat("mingw") or is_plat("windows") then
    add_ldflags("-mwindows")
    add_links("kernel32", "user32", "gdi32");
    add_files("win32-main.c")
  else
    add_links("X11")
    add_files("x11-main.c")
  end
  after_build(function(target)
    os.cp("$(projectdir)/../../data", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
