from setuptools import setup, Extension

reg_extension = Extension(
    name="reg_wrapper",
    sources=["src/wrapper/reg_wrapper.c", "src/regression/reg.c"],
    include_dirs=["src/regression"],
)

setup(
    name="reg_wrapper",
    version="0.1",
    ext_modules=[reg_extension],
)
