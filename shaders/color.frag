#version 460 core

struct Material {
    vec3 ambientColor;
    vec3 baseColor;
    vec3 specularColor;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambientColor;
    vec3 baseColor;
    vec3 specularColor;
};

uniform Material material;
uniform Light light;

out vec4 FragColor;

uniform vec3 cameraPosition;

in vec3 normal;
in vec3 fragPosition;

void main() {
    vec3 ambientColor = light.ambientColor * material.ambientColor;


    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diffuseStrength = max(dot(norm, lightDirection), 0);

    vec3 diffuseColor = light.baseColor * (diffuseStrength * material.baseColor);


    vec3 viewDirection = normalize(cameraPosition - fragPosition);
    // We negate the lightDirection vector as it points from the fragment to the light source when reflect() expects it to be the other way around
    vec3 reflectionDirection = reflect(-lightDirection, norm);
    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec3 specularColor = light.specularColor * (specularStrength * material.specularColor);

    vec3 result = ambientColor + diffuseColor + specularColor;
    FragColor = vec4(result, 1.0);
}
