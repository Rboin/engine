#version 430 core
out vec4 col;

in vec2 texCoordinate;
//in vec3 Normal;

layout(location = 5) uniform float reflectPower;
layout(location = 6) uniform vec3 lightPosition;
layout(location = 7) uniform vec3 lightColor;
layout(location = 8) uniform vec3 objectColor;
layout(location = 9) uniform sampler2D texture1;
layout(location = 10) uniform sampler2D texture2;

void main() {
    vec3 absorbedObjectColor = reflectPower * objectColor;
    vec3 result = lightColor * absorbedObjectColor;
    col = vec4(result, 1.0f) * mix(texture(texture1, texCoordinate), texture(texture2, texCoordinate), 0.2);
}
