-- project
set_project('libu')

-- set xmake minimum version
set_xmakever('2.6.1')

-- set project version
set_version('0.0.1')

-- add_build_modes
add_rules('mode.debug')

-- set warning all as error
set_warnings('all')

-- set language: c99
set_languages('c2x', 'c++17')

-- add defines
add_defines('_GNU_SOURCE')
add_defines('__STDC_VERSION__=201710L+1')

if is_mode('debug') then
  add_cflags('-pg')
  add_undefines('NDEBUG')
end

if is_mode('release') then
  add_defines('NDEBUG')
end

-- include project sources
add_includedirs('include/')

add_repositories('RunThem https://github.com/RunThem/My-xmake-repo')
add_requires('mini-unit-test', 'mimalloc')

target('u', function()
  set_kind('static')
  add_files('src/*.c')
  add_packages('mimalloc')
end)

target('demo', function()
  set_kind('binary')
  add_files('demo.c')
  add_deps('u')

  add_packages('mini-unit-test', 'mimalloc')
end)

target('test', function()
  set_kind('binary')
  add_files('test/*.c')
  add_deps('u')

  add_packages('mini-unit-test', 'mimalloc')
end)
