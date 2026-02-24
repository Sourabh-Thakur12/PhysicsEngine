cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

project(physicsEngine)
set(BUILD_SHARED_LIBS OFF)


# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Third party libs
add_subdirectory(thirdParty/glfw)
#add_subdirectory(thirdParty/glad)


# glad
add_library(glad STATIC thirdParty/glad/src/glad.c)
target_include_directories(glad PUBLIC thirdParty/glad/include)

# opengl
find_package(OpenGL REQUIRED)



# define MY_SOURCES to list of all src files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(PhysicsEngine src/main.cpp)

target_compile_definitions(PhysicsEngine PUBLIC GLFW_INCLUDE_NONE=1)

target_link_libraries(PhysicsEngine PRIVATE
    glfw
    glad
    OpenGL::GL
    dl
    pthread
    )
