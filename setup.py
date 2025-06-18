# setup.py
from setuptools import setup, Extension

# List all source files here
calco_sources = [
    'src/calco_arithmetic.c',
    'src/calco_rounding_exp_log.c',
    'src/calco_trig_hyper.c',
    'src/calco_special_utility.c',
    'src/calco_module.c'
]

calco_module = Extension(
    'calco',
    sources=calco_sources,
    include_dirs=['src'], # Specify the directory where calco.h is located
    extra_compile_args=['-O3', '-std=c99', '-ffast-math'] # -O3 for optimization, -std=c99 for modern C features, -ffast-math for potentially faster but less precise math operations
)

setup(
    name='calco',
    version='1.0.0',
    description='A comprehensive and fast C library for mathematical operations (double precision).',
    ext_modules=[calco_module]
)

