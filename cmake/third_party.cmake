include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY git@github.com:gabime/spdlog.git
    GIT_TAG        v1.15.3
)
FetchContent_MakeAvailable(spdlog)

# 添加调试信息
get_target_property(SPDLOG_INCLUDE_DIRS spdlog INTERFACE_INCLUDE_DIRECTORIES)
message(STATUS "spdlog include dirs: ${SPDLOG_INCLUDE_DIRS}")