#version 460 core

in vec3 vertexPosition;
out vec4 FragColor;

void main() {
    FragColor = vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, 1.0);
}