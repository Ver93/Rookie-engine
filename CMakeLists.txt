cmake_minimum_required(VERSION 3.16)
project(RookieEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/include)

file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_executable(rookie_engine ${ENGINE_SOURCES})

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

    target_compile_options(rookie_engine PRIVATE
        -Wall -Wextra -Wpedantic
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O3 -march=native -flto -DNDEBUG>
    )

elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")

    target_compile_options(rookie_engine PRIVATE
        /W4
        $<$<CONFIG:Debug>:/Od /Zi>
        $<$<CONFIG:Release>:/Ox /DNDEBUG>
    )

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
