
add_languages('cpp', required : true, native : false)

src = [
  'main.cpp',
  'portal-test-qt.h',
  'portal-test-qt.cpp',
]

prep = qt5.preprocess(
  moc_headers : 'portal-test-qt.h',
  moc_extra_arguments: ['-DMAKES_MY_MOC_HEADER_COMPILE'],
  ui_files : 'portal-test-qt.ui',
  dependencies: libportal_qt5_dep,
)

executable('portal-test-qt5',
  [src, prep],
  include_directories: [top_inc, libportal_inc],
  dependencies: [libportal_qt5_dep],
  cpp_args : '-std=c++11',
  install : true,
)
