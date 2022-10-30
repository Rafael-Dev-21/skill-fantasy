if is_plat("windows") then
	add_require("pdcurses")
end

target("skfantasy")
	set_kind("binary")
	add_files("src/*.c")
	add_includedirs("$(projectdir)/include")
	if is_plat("windows") then
		add_installfiles("$(projectdir)/pdcurses.dll")
		add_deps("pdcurses")
		add_links("pdcurses")
	else
		add_links("ncurses")
	end

	add_links("m")
