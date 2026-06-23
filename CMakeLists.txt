cmake_minimum_required(VERSION 3.15)

project(VersionControlSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(

    VersionControlSystem

    src/main.cpp

    src/TreeNode.cpp
    src/VersionIndex.cpp

    src/PointerIndexMap.cpp
    src/FileRegistry.cpp

    src/FileVersion.cpp

    src/CommandProcessor.cpp
)
