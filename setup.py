from setuptools import setup, Extension

calco_module = Extension(
    "calco",
    sources=["calco.c"],
    extra_compile_args=["-O3"],
)

setup(
    name="calco",
    version="1.0.0",
    description="Fast math library written in C",
    ext_modules=[calco_module],
)
