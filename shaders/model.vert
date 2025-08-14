#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 textureCoordinates;
out vec3 normal;
out vec3 fragPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    normal = aNormal;
    fragPosition = vec3(modelMatrix * vec4(aPos, 1.0));
    textureCoordinates = aTexCoords;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}

