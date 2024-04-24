cmake_minimum_required(VERSION 3.29)

project(VulkanTest)

file(GLOB files CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(VulkanTest "${files}")

target_link_libraries(VulkanTest PRIVATE glfw vulkan)
