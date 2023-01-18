-- to test the game on my cellphone

target("skfantasy")
  set_kind("binary")
  add_files("src/*.cpp")
  add_links("ncurses")

