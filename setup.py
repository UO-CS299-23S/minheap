from setuptools import setup, Extension

extension_mod = Extension("minheap", sources=["minheap.c"])

setup(
    name="minheap",
    version="1.0",
    ext_modules=[extension_mod],
)
