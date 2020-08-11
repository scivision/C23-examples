project('vc11', 'c', default_options : ['c_std=c11'])

cc = meson.get_compiler('c')

os = host_machine.system()
is_windows = os == 'windows'


subdir('c99')

subdir('c11')
