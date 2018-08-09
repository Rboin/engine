#version 430 core

in vec3 position;
in vec3 normal;
in vec3 textureCoordinate;

uniform mat3 normalModel;
uniform mat4 modelToWorld;
uniform mat4 modelToProjection;

out vec2 TextureCoordinate;
out vec3 Normal;
out vec3 FragmentPosition;

void main()
{
   TextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
   FragmentPosition = vec3(modelToWorld * vec4(position, 1.0));
   Normal = normalModel * normal;

   gl_Position = modelToProjection * vec4(position, 1.0);
}
