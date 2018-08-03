#version 430 core

out vec4 color;

in vec2 TextureCoordinate;
in vec3 Normal;
in vec3 FragmentPosition;

uniform layout(location = 6) float reflectPower;
uniform layout(location = 7) vec3 lightPosition;
uniform layout(location = 8) vec3 lightColor;
uniform layout(location = 9) vec3 objectColor;
uniform layout(location = 10) sampler2D texture1;
uniform layout(location = 11) sampler2D texture2;

void main() {
    vec3 ambient = 0.1 * lightColor;
    vec3 norm = normalize(Normal);
    vec3 lightRayDirection = normalize(lightPosition - FragmentPosition);
    float diffuseScalar = max(dot(Normal, lightRayDirection), 0.0);
    vec3 diffuseColor = diffuseScalar * lightColor;
    vec3 reflectedColor = reflectPower * objectColor;
    vec3 resultingColor = (lightColor + diffuseColor) * reflectedColor;
    color = vec4(resultingColor, 1.0);// * mix(texture(texture1, TextureCoordinate), texture(texture2, TextureCoordinate), 0.2);
}
