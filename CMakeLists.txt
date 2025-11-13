cmake_minimum_required(VERSION 4.0)
project(WorldBoundaryPatch)

set(CMAKE_CXX_STANDARD 20)


add_library(WorldBoundaryPatch SHARED
        src/Image.cpp
        src/WorldBoundaryPatch.cpp)


add_subdirectory(deps/Dobby)

target_link_libraries(WorldBoundaryPatch dobby)