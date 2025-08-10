#version 460 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

//out vec3 color;
out vec3 normal;
out vec3 fragPosition;
out vec2 textureCoordinates;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    //color = aColor;
    normal = aNormal;
    textureCoordinates = aTexCoord;
    fragPosition = vec3(modelMatrix * vec4(aPos, 1.0));
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
}