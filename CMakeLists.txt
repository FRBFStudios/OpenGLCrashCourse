cmake_minimum_required(VERSION 3.10)
project(OpenGLCrashCourse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)

set(SOURCES
        src/Main.cpp
        src/stb.cpp
        src/shaderClass.cpp
        src/VAO.cpp
        src/VBO.cpp
        src/EBO.cpp
        src/Texture.cpp
        src/glad.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

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