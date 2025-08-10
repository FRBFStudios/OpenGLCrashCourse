#version 460 core

struct Material {
    vec3 ambientColor;
    vec3 surfaceColor;
    vec3 specularColor;
    float shininess;
};

uniform Material material;

out vec4 FragColor;

uniform vec3 color;
uniform vec3 cameraPosition;

in vec3 normal;
in vec3 fragPosition;

uniform vec3 lightSourcePosition;

void main() {
    vec3 ambientColor = vec3(0.1f) * material.ambientColor;


    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightSourcePosition - fragPosition);
    float diffuseStrength = max(dot(norm, lightDirection), 0);

    vec3 diffuseColor = vec3(1.0f) * (diffuseStrength * material.surfaceColor);


    vec3 viewDirection = normalize(cameraPosition - fragPosition);
    // We negate the lightDirection vector as it points from the fragment to the light source when reflect() expects it to be the other way around
    vec3 reflectionDirection = reflect(-lightDirection, norm);
    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec3 specularColor = vec3(1.0f) * (specularStrength * material.specularColor);

    vec3 result = ambientColor + diffuseColor + specularColor;
    FragColor = vec4(result, 1.0);
}
