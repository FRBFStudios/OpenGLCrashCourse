#version 460 core
layout (location = 0) in vec3 aPos;

out vec3 vertexPosition;

void main() {
    vertexPosition = vec3(aPos.x, aPos.y, aPos.z);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}