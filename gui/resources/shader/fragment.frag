#version 430 core

out vec4 color;

in vec2 TextureCoordinate;
in vec3 Normal;
in vec3 FragmentPosition;

uniform layout(location = 7) float reflectPower;
uniform layout(location = 8) float shinePower;
uniform layout(location = 9) vec3 lightPosition;
uniform layout(location = 10) vec3 lightColor;
uniform layout(location = 11) vec3 objectColor;
uniform layout(location = 12) vec3 cameraPosition;
uniform layout(location = 13) sampler2D texture1;
uniform layout(location = 14) sampler2D texture2;

void main() {
    // Diffuse lighting
    vec3 lightRayDirection = normalize(lightPosition - FragmentPosition);
    float diffuseScalar = max(dot(Normal, lightRayDirection), 0.0);
    vec3 diffuseColor = diffuseScalar * lightColor;

    // Specular lighting
    vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightRayDirection, Normal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), shinePower);
    vec3 specularColor = specular * lightColor;

    // Resulting color
    vec3 reflectedColor = reflectPower * objectColor;
    vec3 resultingColor = (lightColor + diffuseColor + specularColor) * reflectedColor;
    color = vec4(resultingColor, 1.0);// * mix(texture(texture1, TextureCoordinate), texture(texture2, TextureCoordinate), 0.2);
}
