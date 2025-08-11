#version 460 core

struct Material {
    sampler2D baseColor;
    sampler2D specularColor;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambientColor;
    vec3 baseColor;
    vec3 specularColor;

    float constant;
    float linear;
    float quadratic;
};

in vec2 textureCoordinates;

uniform Material material;
uniform Light light;

out vec4 FragColor;

uniform vec3 cameraPosition;

in vec3 normal;
in vec3 fragPosition;

void main() {
    float lightDistance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));

    vec3 ambientColor = light.ambientColor * vec3(texture(material.baseColor, textureCoordinates));


    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(light.position - fragPosition);
    float diffuseStrength = max(dot(norm, lightDirection), 0);

    vec3 diffuseColor = light.baseColor * diffuseStrength * vec3(texture(material.baseColor, textureCoordinates));


    vec3 viewDirection = normalize(cameraPosition - fragPosition);
    // We negate the lightDirection vector as it points from the fragment to the light source when reflect() expects it to be the other way around
    vec3 reflectionDirection = reflect(-lightDirection, norm);
    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec3 specularColor = light.specularColor * specularStrength * vec3(texture(material.specularColor, textureCoordinates));

    ambientColor  *= attenuation;
    diffuseColor  *= attenuation;
    specularColor *= attenuation;

    FragColor = vec4(ambientColor + diffuseColor + specularColor, 1.0);
}
