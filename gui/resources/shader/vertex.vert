#version 430 core

in layout(location = 1) vec3 position;
in layout(location = 2) vec3 normal;
in layout(location = 3) vec3 textureCoordinate;

uniform layout(location = 4) mat3 normalModel;
uniform layout(location = 5) mat4 modelToWorld;
uniform layout(location = 6) mat4 modelToProjection;

out vec2 TextureCoordinate;
out vec3 Normal;
out vec3 FragmentPosition;

void main()
{
   gl_Position = modelToProjection * vec4(position, 1.0);
   TextureCoordinate = vec2(textureCoordinate.x, textureCoordinate.y);
   FragmentPosition = vec3(modelToWorld * vec4(position, 1.0));
   Normal = normalModel * normal;
}
