import os
import platform
import sys

import sysconfig
from setuptools import setup
from setuptools.extension import Extension

class get_pybind_include(object):
    def __init__(self, user=False):
        self.user = user

    def __str__(self):
        import pybind11
        return pybind11.get_include(self.user)


def include_dir_files(folder):
    from os import walk
    files = []
    for (dirpath, _, filenames) in walk(folder):
        for fn in filenames:
            if os.path.splitext(fn)[1] in {'.h', '.cc', '.cpp', '.hpp'}:
                files.append(os.path.join(dirpath, fn))
    return files



setup(
    name='pyg3log',
    version='1.0.0',
    author='Amey Narkhede',
    author_email='ameynarkhede02.com',
    description='python wrapper around C++ g3log logging library https://github.com/KjellKod/g3log',
    license='Unlicensed',
    long_description='python wrapper (https://github.com/GreyDireWolf/pyg3log) around C++ G3log (https://github.com/KjellKod/g3log) logging library along with partial sink support (https://github.com/KjellKod/g3sinks).',
    #setup_requires=['pytest-runner'],
    install_requires=['pybind11>=2.2'],
    #tests_require=['pytest'],
    data_files=include_dir_files('pyg3log'),
    ext_modules=[
        Extension(
            'pyg3log',
            ['src/pyg3log.cpp'],
            include_dirs=[
                get_pybind_include(),
                get_pybind_include(user=True),
                '/usr/local/lib',
            ],
            libraries=['stdc++','g3logger','g3logrotate'],
            extra_compile_args=["-std=c++14", "-v","-fPIC"],
            language='c++14',
        )
    ],
    zip_safe=False,
)

