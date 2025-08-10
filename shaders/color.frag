#version 460 core
out vec4 FragColor;

uniform vec3 color;
uniform vec3 cameraPosition;

in vec3 normal;
in vec3 fragPosition;

uniform vec3 lightColor;
uniform vec3 lightSourcePosition;
uniform float lightStrength;

void main() {
    float ambientStrength = 0.2 * (lightStrength / 2);
    int shininess = 32;

    vec3 ambientColor = ambientStrength * lightColor;

    vec3 norm = normalize(normal);
    vec3 lightDirection = normalize(lightSourcePosition - fragPosition);
    float diffuseStrength = max(dot(norm, lightDirection), 0) * lightStrength;
    vec3 diffuseColor = diffuseStrength * lightColor;

    float specularFactor = 1.0;
    vec3 viewDirection = normalize(cameraPosition - fragPosition);

    // We negate the lightDirection vector as it points from the fragment to the light source when reflect() expects it to be the other way around
    vec3 reflectionDirection = reflect(-lightDirection, norm);
    float specularStrength = pow(max(dot(viewDirection, reflectionDirection), 0.0), shininess);
    vec3 specularColor = specularFactor * specularStrength * lightColor;

    vec3 result = (ambientColor + diffuseColor + specularColor) * color;
    FragColor = vec4(result, 1.0);
}
