#version 430 core

layout(location = 1) in vec3 position;
layout(location = 2) in vec3 textureCoordinate;
layout(location = 3) in vec3 normal;
layout(location = 4) uniform mat4 MVP;

out vec2 texCoordinate;
out vec3 Normal;


void main()
{
   gl_Position = MVP * vec4(position, 1.0f);
   texCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
   Normal = normal;
}
