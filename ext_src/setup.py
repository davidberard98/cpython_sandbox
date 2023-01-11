from distutils.core import setup, Extension

module_dberard = Extension('dberard', sources=['dberardmodule.c'])

setup(name='CPythonExtensionSandbox',
      version='1.0',
      description='Demo package',
      ext_modules=[module_dberard])
