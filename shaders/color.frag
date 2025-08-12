#version 460 core

struct Material {
    sampler2D baseColor;
    sampler2D specularColor;

    float shininess;
};

struct PointLight {
    vec3 position;

    vec3 ambientColor;
    vec3 baseColor;
    vec3 specularColor;

    float constant;
    float linear;
    float quadratic;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];


struct DirectionalLight {
    vec3 direction;

    vec3 ambientColor;
    vec3 baseColor;
    vec3 specularColor;
};
uniform DirectionalLight sun;


in vec3 normal;
in vec3 fragPosition;
in vec2 textureCoordinates;

out vec4 FragColor;

uniform vec3 cameraPosition;

uniform Material material;


vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDirection = normalize(cameraPosition - fragPosition);


    vec3 result = calculateDirectionalLight(sun, norm, viewDirection);

    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calculatePointLight(pointLights[i], norm, fragPosition, viewDirection);
    }


    FragColor = vec4(result, 1.0);
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragPosition);

    float diffuseStrength = max(dot(normal, lightDirection), 0);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    float lightDistance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));

    vec3 ambientColor = light.ambientColor * vec3(texture(material.baseColor, textureCoordinates));
    vec3 diffuseColor = light.baseColor * diffuseStrength * vec3(texture(material.baseColor, textureCoordinates));
    vec3 specularColor = light.specularColor * specularStrength * vec3(texture(material.specularColor, textureCoordinates));

    ambientColor  *= attenuation;
    diffuseColor  *= attenuation;
    specularColor *= attenuation;

    return (ambientColor + diffuseColor + specularColor);
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.direction);

    float diffuseStrength = max(dot(normal, -lightDirection), 0);
    vec3 reflectionDirection = reflect(lightDirection, normal);

    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec3 ambientColor  = light.ambientColor  * vec3(texture(material.baseColor, textureCoordinates));
    vec3 diffuseColor  = light.baseColor     * diffuseStrength  * vec3(texture(material.baseColor,     textureCoordinates));
    vec3 specularColor = light.specularColor * specularStrength * vec3(texture(material.specularColor, textureCoordinates));

    return (ambientColor + diffuseColor + specularColor);
}