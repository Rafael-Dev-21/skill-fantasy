add_rules("mode.debug", "mode.release")

if is_plat("windows") or is_plat("mingw") then
	add_requires("pdcurses")
end

target("skfantasy")
	set_kind("binary")
	add_files("src/**.cpp")
	add_includedirs("include")
	if is_plat("windows") or is_plat("mingw") then
		add_packages("pdcurses")
        add_cxxflags("-static-libgcc",
                     "-static-libgcc_s_seh-1",
                     "-static-libstdc++",
                     "-static-libstdc++-6",
                     "-static-libwinpthread",
                     "-static-libwinpthread-1")
	else
		add_links("ncurses")
	end
