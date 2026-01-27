project('pdcurses', 'c', version: '3.9')

inc = include_directories('.')

sources = [
  'pdcurses/addch.c', 'pdcurses/addchstr.c', 'pdcurses/addstr.c', 'pdcurses/attr.c',
  'pdcurses/beep.c', 'pdcurses/bkgd.c', 'pdcurses/border.c', 'pdcurses/clear.c',
  'pdcurses/color.c', 'pdcurses/delch.c', 'pdcurses/deleteln.c', 'pdcurses/getch.c',
  'pdcurses/getstr.c', 'pdcurses/getyx.c', 'pdcurses/inch.c', 'pdcurses/inchstr.c',
  'pdcurses/initscr.c', 'pdcurses/inopts.c', 'pdcurses/insch.c', 'pdcurses/insstr.c',
  'pdcurses/instr.c', 'pdcurses/kernel.c', 'pdcurses/keyname.c', 'pdcurses/mouse.c',
  'pdcurses/move.c', 'pdcurses/outopts.c', 'pdcurses/overlay.c', 'pdcurses/pad.c',
  'pdcurses/panel.c', 'pdcurses/printw.c', 'pdcurses/refresh.c', 'pdcurses/scanw.c',
  'pdcurses/scr_dump.c', 'pdcurses/scroll.c', 'pdcurses/slk.c', 'pdcurses/termattr.c',
  'pdcurses/touch.c', 'pdcurses/util.c', 'pdcurses/window.c', 'pdcurses/debug.c',
  # backend
  'wingui/pdcgetsc.c', 'wingui/pdckbd.c', 'wingui/pdcscrn.c', 'wingui/pdcsetsc.c',
  'wingui/pdcutil.c', 'wingui/pdcdisp.c', 'wingui/pdcclip.c'
]

cc = meson.get_compiler('c')
extra_libs = [
  cc.find_library('user32'),
  cc.find_library('gdi32'),
  cc.find_library('comdlg32'),
  cc.find_library('winmm')
]

windows = import('windows')
pdcurses_res = windows.compile_resources(
  'common/pdcurses.rc',
  include_directories: inc
)

pdcurses_lib = static_library('pdcurses',
  sources,
  pdcurses_res,
  include_directories: inc,
  dependencies: extra_libs,
  c_args: ['-DPDC_WIDE', '-DCHTYPE_32=Y']
)

pdcurses_dep = declare_dependency(
  link_with: pdcurses_lib,
  include_directories: inc
)

meson.override_dependency('pdcurses', pdcurses_dep)
