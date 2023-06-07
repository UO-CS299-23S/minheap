"""Per documentation at
https://setuptools.pypa.io/en/latest/userguide/ext_modules.html

"""
from setuptools import setup, Extension


setup(
    name='minheap',
    version='1.0',
    description='A simple C extension module for Python',
    ext_modules=[Extension('minheap', sources=['src/minheap_python.c', 'src/minheap.c'])]
)
