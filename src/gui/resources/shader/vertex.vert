#version 430 core

in vec3 position;
in vec3 inColor;
in vec3 textureCoordinate;

out vec3 color;
out vec2 texCoordinate;

uniform mat4 MVP;

void main()
{
   gl_Position = MVP * vec4(position, 1.0f);
   color = inColor;
   texCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
}
