cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_SOURCE_DIR}/Poplin/include")
include_directories(${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/include)
include_directories(${CMAKE_SOURCE_DIR}/external/entt/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glm/include)
include_directories(${CMAKE_SOURCE_DIR}/external/imgui-1.82/include)
include_directories(${CMAKE_SOURCE_DIR}/external/json)

file(GLOB_RECURSE POPLIN_SANDBOX_SOURCE_FILES "*.h" "*.cpp" "*.hpp")
file(GLOB IMGUI_SOURCE_FILES "../external/imgui-1.82/include/ImGui/*.cpp")
add_library(PoplinWeaver ${POPLIN_SANDBOX_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

target_link_libraries(PoplinWeaver Poplin_EditorMode opengl32)
target_link_libraries(PoplinWeaver ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib)
target_link_libraries(PoplinWeaver ${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.lib)
target_link_libraries(PoplinWeaver ${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/build/bin/Debug/box2d.lib)

set_property(TARGET PoplinWeaver PROPERTY CXX_STANDARD 17)