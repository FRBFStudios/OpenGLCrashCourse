#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inColors;
layout (location = 2) in vec2 inTexCoord;

out vec4 outColors;
out vec2 outTexCoord;

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    outTexCoord = inTexCoord;
    outColors = vec4(inColors, 1.0);
}