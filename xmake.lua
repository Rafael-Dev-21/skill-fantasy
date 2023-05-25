add_rules("mode.debug", "mode.release")

target("skfantasy")
	set_kind("binary")
	add_files("src/**.c")
	add_includedirs("include")
	add_links("ncurses", "tinfo")
	set_warnings("all", "error")
	if is_plat("linux") then
		set_languages("gnu11")
	else
		set_languages("c11")
	end

