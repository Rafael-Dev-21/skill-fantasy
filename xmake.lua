add_requires("pdcurses")

target("skfantasy")
  set_kind("binary")
  add_files("src/*.cpp")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libstdc++")
  else
    add_links("pdcurses")
  end
