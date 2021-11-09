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


if (POPLIN_COMPILE_WITH_EDITOR)
    add_executable(PoplinSandbox_EditorMode ${POPLIN_SANDBOX_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

    target_link_libraries(PoplinSandbox_EditorMode Poplin_EditorMode PoplinWeaver opengl32)
    target_link_libraries(PoplinSandbox_EditorMode ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib)
    target_link_libraries(PoplinSandbox_EditorMode ${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.lib)
    target_link_libraries(PoplinSandbox_EditorMode ${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/build/bin/Debug/box2d.lib)
    set_target_properties(PoplinSandbox_EditorMode PROPERTIES COMPILE_DEFINITIONS "POPLIN_EDITOR")

    set_property(TARGET PoplinSandbox_EditorMode PROPERTY CXX_STANDARD 17)

    add_custom_command(TARGET PoplinSandbox_EditorMode POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		    "${CMAKE_SOURCE_DIR}/external/glew-2.1.0/bin/Release/x64/"
		    $<TARGET_FILE_DIR:PoplinSandbox_EditorMode>)

    add_custom_command(TARGET PoplinSandbox_EditorMode POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy
		    "${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.dll"
		    $<TARGET_FILE_DIR:PoplinSandbox_EditorMode>)

else()
    add_executable(PoplinSandbox ${POPLIN_SANDBOX_SOURCE_FILES} ${IMGUI_SOURCE_FILES})

    target_link_libraries(PoplinSandbox Poplin opengl32)
    target_link_libraries(PoplinSandbox ${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64/glew32.lib)
    target_link_libraries(PoplinSandbox ${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.lib)
    target_link_libraries(PoplinSandbox ${CMAKE_SOURCE_DIR}/external/box2d-2.4.1/build/bin/Debug/box2d.lib)

    set_property(TARGET PoplinSandbox PROPERTY CXX_STANDARD 17)

    add_custom_command(TARGET PoplinSandbox POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy_directory
		    "${CMAKE_SOURCE_DIR}/external/glew-2.1.0/bin/Release/x64/"
		    $<TARGET_FILE_DIR:PoplinSandbox>)

    add_custom_command(TARGET PoplinSandbox POST_BUILD
		    COMMAND ${CMAKE_COMMAND} -E copy
		    "${CMAKE_SOURCE_DIR}/external/glfw-3.3.3/lib-vc2017/glfw3.dll"
		    $<TARGET_FILE_DIR:PoplinSandbox>)
endif()