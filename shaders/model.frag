#version 460 core
struct Material {
    sampler2D DIFFUSE_MAP1;
    sampler2D SPECULAR_MAP1;

    float shininess;
};
uniform Material material;

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
//uniform DirectionalLight sun;

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec4 ambientColor;
    vec4 baseColor;
    vec4 specularColor;

    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight flashlight;

out vec4 FragColor;

in vec2 textureCoordinates;
in vec3 normal;
in vec3 fragPosition;

uniform vec3 cameraPosition;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);
vec4 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection);

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDirection = normalize(cameraPosition - fragPosition);


    //vec3 result = calculateDirectionalLight(sun, norm, viewDirection);
    vec4 result = calculateSpotLight(flashlight, norm, fragPosition, viewDirection);

    if (result.a < 0.1) {
        discard;
    }

    /*for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calculatePointLight(pointLights[i], norm, fragPosition, viewDirection);
    }*/



    FragColor = result;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragPosition);

    float diffuseStrength = max(dot(normal, lightDirection), 0);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    float lightDistance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));

    vec3 ambientColor = light.ambientColor * vec3(texture(material.DIFFUSE_MAP1, textureCoordinates));
    vec3 diffuseColor = light.baseColor * diffuseStrength * vec3(texture(material.DIFFUSE_MAP1, textureCoordinates));
    vec3 specularColor = light.specularColor * specularStrength * vec3(texture(material.SPECULAR_MAP1, textureCoordinates));

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

    vec3 ambientColor  = light.ambientColor  * vec3(texture(material.DIFFUSE_MAP1, textureCoordinates));
    vec3 diffuseColor  = light.baseColor     * diffuseStrength  * vec3(texture(material.DIFFUSE_MAP1,     textureCoordinates));
    vec3 specularColor = light.specularColor * specularStrength * vec3(texture(material.SPECULAR_MAP1, textureCoordinates));

    return (ambientColor + diffuseColor + specularColor);
}

vec4 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragPosition);
    float theta = dot(lightDirection, normalize(-light.direction));

    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    float lightDistance = length(light.position - fragPosition);
    float attenuation = 1.0f / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));


    float diffuseStrength = max(dot(normal, lightDirection), 0);
    vec3 reflectionDirection = reflect(-lightDirection, normal);

    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), material.shininess);

    vec4 ambientColor = light.ambientColor * texture(material.DIFFUSE_MAP1, textureCoordinates);
    vec4 diffuseColor = light.baseColor * diffuseStrength * texture(material.DIFFUSE_MAP1, textureCoordinates);
    vec4 specularColor = light.specularColor * specularStrength * texture(material.SPECULAR_MAP1, textureCoordinates);

    ambientColor  *= attenuation;
    diffuseColor *= attenuation;
    specularColor *= attenuation;

    diffuseColor *= intensity;
    specularColor *= intensity;

    return (ambientColor + diffuseColor + specularColor);
}