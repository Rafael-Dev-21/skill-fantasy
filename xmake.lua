add_rules("mode.debug", "mode.release")

if is_plat ("windows") or is_plat("mingw") then
  add_requires("pdcurses")
  add_packages("pdcurses")
else
  add_requires("ncurses")
  add_packages("ncurses")
end

set_languages("c99")

target("core")
  set_kind("static")
  add_files("src/noise.c", "src/util.c")

target("skfantasy")
  set_kind("binary")
  add_files("src/main.c")
  add_deps("core")
  if is_plat("mingw") then
    add_ldflags("-static-libgcc", "-static-libc++")
  end
  --[[
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
  ]]--
target_end()

for i, num in ipairs({"1", "2", "3"}) do
  target("oldard"..num)
    set_kind("binary")
    add_files("oldard"..num.."/*.c")
  target_end()
end
