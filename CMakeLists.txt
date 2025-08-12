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
        src/util/stb.cpp
        src/util/texture.h
        src/util/texture.cpp
        src/scene/camera.h
        src/scene/camera.cpp
        src/util/model_loader.cpp
        src/util/model_loader.h
        src/util/model.cpp
        src/util/model.h)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

message(STATUS "System name: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Is CCing: ${CMAKE_CROSSCOMPILING}")
message(STATUS "WIN32: ${WIN32}")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    # For Windows cross-compiling with MinGW-w64
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/lib/windows/libglfw3.a
            opengl32  # Windows OpenGL library
    )
else()
    # Native Linux build
    target_link_libraries(${PROJECT_NAME} PRIVATE
            ${CMAKE_SOURCE_DIR}/lib/linux/libglfw3.a
            ${CMAKE_SOURCE_DIR}/lib/linux/libassimp.a
            OpenGL::GL  # Linux OpenGL target from find_package
            dl
            pthread
            wayland-client
            wayland-cursor
            wayland-egl
            xkbcommon
    )
endif()