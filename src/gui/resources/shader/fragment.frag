#version 430 core
out vec4 col;

in vec3 color;
in vec2 texCoordinate;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    col = mix(texture(texture1, texCoordinate), texture(texture2, texCoordinate), 0.2);
}
