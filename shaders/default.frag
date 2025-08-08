#version 460 core

out vec4 FragColor;

in vec4 outColors;
in vec2 outTexCoord;

uniform sampler2D tex;
// uniform sampler2D texOverlay;

void main() {
    // FragColor = mix(texture(tex, outTexCoord), texture(texOverlay, outTexCoord), 0.2);
    FragColor = texture(tex, outTexCoord)  * outColors;
}