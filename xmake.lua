add_rules("mode.debug", "mode.release")

target("skfantasy")
	set_kind("binary")
	add_files("src/**.c")
	add_includedirs("include")
	add_links("ncurses", "tinfo")
	set_warnings("all", "error")
	set_languages("c99")

