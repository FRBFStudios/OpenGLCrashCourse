cmake_minimum_required(VERSION 3.10)
project(OpenGLCrashCourse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

list(APPEND SOURCES src/glad.c)

add_executable(${PROJECT_NAME} ${SOURCES}
        include/VBO.h
        src/VBO.cpp
        include/shader_program.h
        src/shader_program.cpp
        include/VAO.h
        src/VAO.cpp
        include/EBO.h
        src/EBO.cpp
        src/stb.cpp
        include/texture.h)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

link_directories(${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/libglfw3.a
        OpenGL::GL
        dl
        pthread
        wayland-client
        wayland-cursor
        wayland-egl
        xkbcommon
)