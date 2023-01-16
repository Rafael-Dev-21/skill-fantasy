if is_plat("mingw") then
  add_requires("pdcurses", {configs = {port = "wincon"}})
end

target("skfantasy")
  set_kind("binary")
  add_files("src/*.cpp")
  if is_plat("mingw") then
    add_packages("pdcurses")
  else
    add_links("ncurses")
  end
