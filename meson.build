project('skillfantasy', 'cpp')
if host_machine.system() == 'windows'
  add_project_arguments('-DPDC_WIDE', '-DCHTYPE_32=Y', language: ['c', 'cpp'])
  pdcursesdep = dependency('pdcurses')
  executable('skillfantasy', 'src/ui.cxx', 'src/main.cxx', dependencies : pdcursesdep, link_args: ['-static', '-mwindows'])
else
  ncursesdep = dependency('ncurses')
  executable('skillfantasy', 'src/ui.cxx', 'src/main.cxx', dependencies : ncursesdep)
endif
