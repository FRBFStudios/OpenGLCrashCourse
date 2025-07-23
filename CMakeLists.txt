cmake_minimum_required(VERSION 3.10)
project(OpenGLCrashCourse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

# Gather all source files in src/
file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        OpenGL::GL
        ${GLFW_LIBRARIES}
        glad
)