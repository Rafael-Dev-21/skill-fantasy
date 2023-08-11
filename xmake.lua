add_rules("mode.debug", "mode.release")

if is_plat("windows") then
	add_require("pdcurses")
end

target("skfantasy")
	set_kind("binary")
	add_files("src/**.cpp")
	add_includedirs("include")
	if is_plat("windows") then
		add_packages("pdcurses")
	else
		add_links("ncurses")
	end
