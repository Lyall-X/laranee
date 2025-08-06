# documents https://cmake.org/documentation
cmake_minimum_required(VERSION 3.4.1)
project(laranee CXX)

# c++ version required
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_FLAGS "${CXX_FLAGS} -fsanitize=address -fsanitize=leak -fsanitize-recover=address -fno-omit-frame-pointer")

# build message output
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# suffix to debug library version automatically
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_INSTALL_MESSAGE NEVER)

# set install path
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)

# cmake module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(func)
include(third_party)
include(install_bin)

set(CXX_FLAG_LIST
    "-Wno-deprecated"
    "-Werror"
    "-Wall"
    "-Wno-unused-function"
    "-Wno-unused-result"
    "-Wno-misleading-indentation"
    "-fopenmp"
)
string(REPLACE ";" " " CXX_FLAGS "${CXX_FLAG_LIST}")
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS} -O0 -g -ggdb")                            # Debug
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS} -O2 -DNDEBUG")                          # Release
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CXX_FLAGS} -O2 -g -DNDEBUG")                # RelWithDebInfo

include_directories(
    laranee
)

add_subdirectory(laranee)
add_subdirectory(src)
add_subdirectory(test)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")