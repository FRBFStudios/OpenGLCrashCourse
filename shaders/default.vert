#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColors;
layout (location = 2) in vec2 inTexCoord;

out vec4 outColors;
out vec2 outTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    outTexCoord = inTexCoord;
    outColors = vec4(inColors, 1.0);
}