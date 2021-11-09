cmake_minimum_required (VERSION 3.8)

include_directories("${CMAKE_SOURCE_DIR}/Poplin/include")
include_directories(${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/include)
include_directories(${CMAKE_SOURCE_DIR}/external/entt/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/include)
include_directories(${CMAKE_SOURCE_DIR}/external/glm/include)
include_directories(${CMAKE_SOURCE_DIR}/external/imgui-1.82/include)
include_directories(${CMAKE_SOURCE_DIR}/external/json)

file(GLOB_RECURSE POPLIN_SOURCE_FILES "*.h" "*.cpp" "*.hpp")
file(GLOB IMGUI_SOURCE_FILES "../external/imgui-1.82/include/ImGui/*.cpp")

if (POPLIN_COMPILE_WITH_EDITOR)
	add_library(Poplin_EditorMode ${POPLIN_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

	target_link_libraries(Poplin_EditorMode opengl32)
	target_link_libraries(Poplin_EditorMode ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib)
	target_link_libraries(Poplin_EditorMode ${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.lib)
	target_link_libraries(Poplin_EditorMode ${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/build/bin/Debug/box2d.lib)
	set_target_properties(Poplin_EditorMode PROPERTIES COMPILE_DEFINITIONS "POPLIN_EDITOR")

	set_property(TARGET Poplin_EditorMode PROPERTY CXX_STANDARD 17)
else()
	add_library(Poplin ${POPLIN_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

	target_link_libraries(Poplin opengl32)
	target_link_libraries(Poplin ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib)
	target_link_libraries(Poplin ${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.lib)
	target_link_libraries(Poplin ${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/build/bin/Debug/box2d.lib)

	set_property(TARGET Poplin PROPERTY CXX_STANDARD 17)
endif()