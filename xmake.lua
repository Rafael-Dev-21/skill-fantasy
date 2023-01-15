target("skillfantasy")
	set_kind("binary")
	add_files("src/*.c")
	add_links("ncurses", "tinfo")
