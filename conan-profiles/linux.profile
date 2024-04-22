[settings]
arch=x86_64
build_type=Release
compiler=clang
compiler.cppstd=gnu14
compiler.libcxx=libstdc++11
compiler.version=14
os=Linux

[options]
substrate/*:shared=True
substrate/*:with_tests=False
