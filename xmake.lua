add_rules("mode.debug", "mode.release")

if is_mode("release") then
  add_requires("pdcurses")
end

target("skfantasy")
  set_kind("binary")
  add_files("src/*.cpp")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libstdc++")
  end
  if is_mode("release") then
    add_packages("pdcurses")
  else
    add_defines("DEBUG")
    add_links("ncurses", "tinfo")
  end
