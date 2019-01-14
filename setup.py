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
    name='pyG3log',
    version='1.0.4',
    author='Amey Narkhede',
    author_email='ameynarkhede03.com',
    description='python wrapper around C++ spdlog logging library (https://github.com/bodgergely/pyspdlog)',
    license='Unlicensed',
    long_description='python wrapper (https://github.com/KjellKod/g3log) around C++ G3log (https://github.com/KjellKod/g3log) logging library.',
    setup_requires=['pytest-runner'],
    install_requires=['pybind11>=2.2'],
    tests_require=['pytest'],
    data_files=include_dir_files('pyg3log'),
    ext_modules=[
        Extension(
            'pyg3log',
            ['src/pyg3log.cpp'],
            include_dirs=[
                'g3log/include/',
                get_pybind_include(),
                get_pybind_include(user=True)
            ],
            libraries=['stdc++'],
            extra_compile_args=["-std=c++11", "-v"],
            language='c++11'
        )
    ],
    zip_safe=False,
)

