if is_plat("windows") or is_plat("mingw") then
	add_requires("pdcurses")
end

target("skfantasy")
	add_files("src/*.c")
	add_includedirs("$(projectdir)/include")
	if is_plat("windows") or is_plat("mingw") then
		add_installfiles("$(projectdir)/pdcurses.dll")
		add_deps("pdcurses")
		add_links("pdcurses")
	else
		add_links("ncurses")
	end
	add_links("m")
