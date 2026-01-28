project('skillfantasy', 'cpp',
  default_options: ['cpp_std=c++23'])

srcs = [ 'src/ui.cxx', 'src/XorShift.cxx', 'src/main.cxx' ]

if host_machine.system() == 'windows'
  add_project_arguments('-DPDC_WIDE', '-DCHTYPE_32=Y', language: ['c', 'cpp'])
  pdcursesdep = dependency('pdcurses')
  executable('skillfantasy', srcs, dependencies : pdcursesdep, link_args: ['-static', '-mwindows'])
else
  ncursesdep = dependency('ncurses')
  executable('skillfantasy', srcs, dependencies : ncursesdep)
endif
