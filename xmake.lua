add_rules("mode.debug", "mode.release")

package("mingw-std-threads")
    add_deps("cmake")
    set_sourcedir(path.join(os.scriptdir(), "mingw-std-threads"))
    on_install(function (package)
        local configs = {}
        table.insert(configs, "-DMINGW_STDTHREADS_GENERATE_STDHEADERS=ON")
        import("package.tools.cmake").install(package, configs)
    end)
package_end()
    

if is_plat("windows") or is_plat("mingw") then
	add_requires("pdcurses")
    add_requires("mingw-std-threads")
end

target("skfantasy")
	set_kind("binary")
	add_files("src/**.cpp")
	add_includedirs("include")
	if is_plat("windows") or is_plat("mingw") then
		add_packages("pdcurses", "mingw-std-threads")
        add_ldflags("-static-libgcc", "-static-libstdc++")
	else
		add_links("ncurses")
	end
