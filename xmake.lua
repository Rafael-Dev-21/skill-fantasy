add_rules("mode.debug", "mode.release")

target("skfantasy")
	set_kind("binary")
	add_files("src/**.cpp")
	if is_mode("debug") then
		add_defines("DEBUG")
		set_optimize("none")
		set_symbols("debug")
	end
		
	set_languages("c++2b")
	add_links("ncurses", "tinfo")

