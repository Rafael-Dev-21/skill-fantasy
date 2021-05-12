add_rules("mode.debug", "mode.release")

target("skillfantasy")
	set_kind("binary")
	add_files("src/*.cc")
	set_targetdir(".")
	set_objectdir("obj")
	--> if is platform linux or macosx add ncurses to project
	if is_plat("linux" or "macosx") then
		add_packages("ncurses")
	end
	--> if is platform windows add pcurses
	if is_plat("windows") then
		add_packages("pdcurses")
	end
	if is_mode("debug") then
		add_defines("DEBUG")
	end
	set_languages("c++11")
