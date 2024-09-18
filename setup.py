from setuptools import setup, Extension

setup(
    name="tensor-snow",
    version="0.1",
    description="A Python library for tensor operations using C++",
    packages=["tensor"],
    package_dir={"tensor": "t-snow/tensor"},
    ext_modules=[Extension(
        "tensor_lib", 
        sources=["src/tensor.cpp"], 
        include_dirs=["headers"], 
        extra_compile_args=["-fPIC"],
        extra_link_args=["-shared"],
    )],
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.6',
)
