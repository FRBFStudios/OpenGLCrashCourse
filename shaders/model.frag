#version 460 core
out vec4 FragColor;

in vec2 textureCoordinates;

uniform sampler2D DIFFUSE_MAP1;

void main() {
    FragColor = texture(DIFFUSE_MAP1, textureCoordinates);
}