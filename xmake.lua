-- project
set_project('libu')

-- set xmake minimum version
set_xmakever('2.6.1')

-- set project version
set_version('0.0.1')

-- set warning all as error
-- set_warnings('all', 'error')

-- set language: c99
set_languages('c2x', 'c++17')

-- add_build_modes
add_rules('mode.release', 'mode.debug')

-- add defines
add_defines('_GNU_SOURCE')
add_defines('__STDC_VERSION__=201710L+1')

if is_mode('debug') then
  add_cflags(
    '-Wstrict-prototypes',
    '-Wmissing-prototypes',
    '-Wpointer-arith',
    '-Wno-uninitialized',
    '-Wreturn-type',
    '-Wwrite-strings',
    '-Wswitch',
    '-Wshadow',
    '-Wunreachable-code',
    '-Wunused',
    '-Wcast-qual',
    '-pedantic'
  )
  add_cflags('-pg')
  add_undefines('NDEBUG')
elseif is_mode('release') then
  add_defines('NDEBUG')
end

-- include project sources
add_includedirs('include/')

target('u', function()
  set_kind('static')
  add_files('src/*.c')
end)

target('demo', function()
  set_kind('binary')
  add_files('demo.c')
  add_deps('u')
end)
