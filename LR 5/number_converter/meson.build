project('number_converter', 'c',
  version : '0.1',
  default_options : ['warning_level=3', 'c_std=c11'])

executable('number_converter',
           'src/main.c', 'src/converter.c', 'src/validator.c', 'src/ui_handler.c',
           c_args : ['-DDEBUG'],
           include_directories : include_directories('include'),
           install : false)