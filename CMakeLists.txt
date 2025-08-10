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
        src/util/VBO.h
        src/util/VBO.cpp
        src/util/shader_program.h
        src/util/shader_program.cpp
        src/util/VAO.h
        src/util/VAO.cpp
        src/util/EBO.h
        src/util/EBO.cpp
        src/texture/stb.cpp
        src/texture/texture.h
        src/texture/texture.cpp
        src/scene/camera.h
        src/scene/camera.cpp)

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