if is_plat("windows") then
	add_requires("pdcurses")
end

target("skfantasy")
	set_kind("binary")
	add_files("src/*.c")
	add_includedirs("$(projectdir)/include")
	if is_plat("windows") then
		add_packages("pdcurses")
		add_links("pdcurses")
	else
		add_links("ncurses", "m")
	end
