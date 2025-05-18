cmake_minimum_required(VERSION 3.22)

project(VulkanView)

set(SOURCE_FILES
	src/main.cpp
)

add_executable(VulkanView
    ${SOURCE_FILES}
)

set_target_properties(VulkanView PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_include_directories(VulkanView PRIVATE "glm/")
target_include_directories(VulkanView PRIVATE "glfw-3.4.bin.WIN64/include/")

target_link_libraries(VulkanView PRIVATE ${CMAKE_SOURCE_DIR}/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.lib)

find_package(Vulkan REQUIRED)

target_link_libraries(VulkanView PRIVATE Vulkan::Vulkan)