#!/bin/bash
# set yourself compiler: 
#   clang mini version is 16.x;
#   gcc mini version is 11.x;
# ********************************************************************
export CXX="clang++"
export CC="clang"
# ********************************************************************

set -e
trap 'echo -e "\\e[31m \"${BASH_COMMAND}\" command failed, error code: $?\\e[0m"' ERR

if [ -z "$1" ]; then 
    set -- "Debug"
fi

# BUILD_TYPE=Debug, Release or RelWithDebInfo ...
BUILD_TYPE=$1
cmake -B build -G Ninja \
      -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
      -DCMAKE_C_COMPILER=${CC} \
      -DCMAKE_CXX_COMPILER=${CXX}

cmake --build build --parallel $(nproc)
cmake --build build --target install

echo -e "\\e[34m build type:\t$1 \\e[0m"
echo -e "\\e[34m Compiler:\tCXX=${CXX},\tCC=${CC}\\e[0m"
echo -e "\\e[34m build dir:\tbuild\\e[0m"
echo -e "\\e[34m output dir:\tbin\\e[0m"
echo -e "\\e[32m build finish.\\e[0m"
