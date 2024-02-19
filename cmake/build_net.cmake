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
add_subdirectory(test)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")
message("CMAKE_CXX_FLAGS_RELWITHDEBINFO is ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("CMAKE_CXX_FLAGS_MINSIZEREL is ${CMAKE_CXX_FLAGS_MINSIZEREL}")