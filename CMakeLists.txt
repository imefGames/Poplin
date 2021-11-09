cmake_minimum_required (VERSION 3.8)

project("Poplin")

option(POPLIN_COMPILE_WITH_EDITOR "Compile project with the editor" OFF)

add_subdirectory("Poplin")
if (POPLIN_COMPILE_WITH_EDITOR)
    add_subdirectory("Weaver")
endif()
add_subdirectory("Sandbox")