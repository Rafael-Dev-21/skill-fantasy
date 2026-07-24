add_rules("mode.debug", "mode.release")

if is_plat("windows") or is_plat("mingw") then
  add_requires("pdcurses")
else
  add_requires("ncurses")

  package("guile-3.0")
    add_extsources("pkgconfig::guile-3.0")
  package_end()

  add_requires("guile-3.0")

  add_requires("ftxui", "entt")
end

target("world-fw")
  set_kind("static")
  add_includedirs("include")
  add_files("src/util.c", "src/data.cpp", "src/noise.c", "src/creature.cpp", "src/world.cpp", "src/creatures/*.cpp", "src/move.c")
  add_packages("ftxui")
  add_packages("entt")

target("benchmark")
  set_kind("binary")
  add_includedirs("include")
  set_languages("cxx20")
  add_files("tests/benchmark.cpp")
  add_deps("world-fw")
  add_packages("ftxui")
  add_packages("entt")

target("main-cpp")
  set_kind("static")
  add_files("src/*.cpp", "src/modes/*.cpp", "src/creatures/*.cpp")
  add_includedirs("include")
  set_languages("cxx23")
  add_packages("ftxui", "entt")
  if not is_plat("mingw") then
--[[    add_defines("USE_GUILE")
    add_files("src/api/guile_api.c")]]--
  end

  on_load(function(target)
    local content = io.readfile("version.txt")
    if content then
      content = content:trim()
      local tag = "VERSION=\""
      tag = tag..content
      tag = tag.."\""
      target:add("defines", tag)
    end
  end)

target("skfantasy")
  set_kind("binary")
  add_files("src/*.c")
  add_includedirs("include")
  set_languages("c99", "cxx23")
  add_deps("main-cpp")
  add_packages("ftxui")
  add_packages("entt")
  
  if is_plat("mingw") then
    --add_packages("pdcurses")
    add_ldflags("-static-libgcc", "-static-libc++")
  else
    --add_packages("ncurses")
    --[[
    add_packages("guile-3.0")
    add_defines("USE_GUILE")
    add_files("src/api/guile_api.c")
    ]]--
  end
  
  after_build(function(target)
    os.cp("$(projectdir)/data", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/scripts", "$(builddir)/$(plat)/$(arch)/$(mode)")
    os.cp("$(projectdir)/version.txt", "$(builddir)/$(plat)/$(arch)/$(mode)")
  end)
