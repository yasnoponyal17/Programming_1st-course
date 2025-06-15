project('number_converter', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

executable('number_converter',
           'main.c', 'converter.c', 'validator.c', 'ui_handler.c',
           c_args: ['-DDEBUG'],
           install : false)