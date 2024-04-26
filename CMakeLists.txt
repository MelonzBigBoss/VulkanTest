cmake_minimum_required(VERSION 3.29)

set(CMAKE_CXX_STANDARD 23)

project(VulkanTest)

include_directories(include/glm)

file(GLOB files CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")

add_executable(VulkanTest "${files}")

if (WIN32) 
set( GLFW_INSTALL OFF CACHE BOOL "GLFW lib only" )
add_subdirectory(include/glfw-3.4)

target_include_directories(${PROJECT_NAME} PRIVATE include/glm-1.0.1-light)

find_package(Vulkan REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)

ELSE()
target_link_libraries(VulkanTest PRIVATE glfw vulkan)
ENDIF()

