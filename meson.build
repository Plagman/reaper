project(
  'reaper',
  ['cpp'],
  meson_version: '>=0.54.0',
  default_options: ['warning_level=2'],
)

thread_dep = dependency('threads')

executable(
    'reaper',
    'reaper.cpp',
    install: true,
	dependencies : [
        thread_dep
    ],
)
