cmake_minimum_required(VERSION 3.22)

project(VulkanView)

set(SOURCE_FILES
	src/engine/Main.cpp
	src/engine/Engine.cpp
    src/vulkan/VulkanApp.cpp
    src/vulkan/Shader.cpp
    src/vulkan/VertexBuffer.cpp
)

set(HEADER_FILES
    headers/engine/Engine.h
    headers/vulkan/VulkanApp.h
    headers/vulkan/Shader.h
    headers/vulkan/VertexBuffer.h
)

set(SHADER_SOURCES
    src/shaders/shader.vert
    src/shaders/shader.frag
)

find_package(Vulkan REQUIRED COMPONENTS glslc)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

if (NOT glslc_executable)
    message(FATAL_ERROR "glslc not found. Please ensure the Vulkan SDK is installed and configured correctly.")
endif()

set(COMPILED_SHADERS)

foreach(SHADER_SRC ${SHADER_SOURCES})
    get_filename_component(SHADER_FULL_NAME "${SHADER_SRC}" NAME)

    set(ABSOLUTE_SHADER_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_SRC}")

    set(SPIRV_OUT "${CMAKE_CURRENT_BINARY_DIR}/shaders/${SHADER_FULL_NAME}.spv")

    set(SHADER_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")
    file(MAKE_DIRECTORY "${SHADER_BUILD_DIR}")

    add_custom_command(
        OUTPUT ${SPIRV_OUT}
        COMMAND ${glslc_executable} ${ABSOLUTE_SHADER_SRC} -o ${SPIRV_OUT}
        DEPENDS ${ABSOLUTE_SHADER_SRC}
        COMMENT "Compiling shader: ${ABSOLUTE_SHADER_SRC} -> ${SPIRV_OUT}"
    )
    list(APPEND COMPILED_SHADERS ${SPIRV_OUT})
endforeach()

add_executable(VulkanView
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "src" FILES
    ${SOURCE_FILES}
)

source_group(TREE ${CMAKE_SOURCE_DIR}/headers PREFIX "headers" FILES
    ${HEADER_FILES}
)

target_include_directories(VulkanView PRIVATE "${CMAKE_SOURCE_DIR}/headers/")


add_custom_target(VulkanShaders ALL DEPENDS ${COMPILED_SHADERS} SOURCES ${SHADER_SOURCES} "src/engine/Engine.cpp" "src/vulkan/VulkanApp.cpp" "headers/vulkan/VulkanApp.h")
add_dependencies(VulkanView VulkanShaders)

set_target_properties(VulkanView PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(VulkanView PRIVATE "glm/")
target_include_directories(VulkanView PRIVATE "glfw-3.4.bin.WIN64/include/")

target_link_libraries(VulkanView PRIVATE ${CMAKE_SOURCE_DIR}/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.lib)

target_link_libraries(VulkanView PRIVATE Vulkan::Vulkan)

add_custom_command(TARGET VulkanView POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:VulkanView>/shaders/"

    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${COMPILED_SHADERS} $<TARGET_FILE_DIR:VulkanView>/shaders/
    COMMENT "Copying compiled shaders to executable directory"
)
