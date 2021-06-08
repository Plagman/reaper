project(
  'reaper',
  ['cpp'],
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
