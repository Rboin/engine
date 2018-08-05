#version 430 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 color;

in vec2 TextureCoordinate;
in vec3 Normal;
in vec3 FragmentPosition;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    // Ambient
    vec3 ambient = light.ambient * material.ambient;

    // Diffuse lighting
    vec3 normalized = normalize(Normal);
    vec3 lightRayDirection = normalize(light.position - FragmentPosition);
    float diffuseScalar = max(dot(normalized, lightRayDirection), 0.0);
    vec3 diffuse = light.diffuse * (diffuseScalar * material.diffuse);

    // Specular lighting
    vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightRayDirection, normalized);
    float specularScalar = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * (specularScalar * material.specular);

    // Resulting color
    vec3 resultingColor = ambient + diffuse + specular;
    color = vec4(resultingColor, 1.0);// * mix(texture(texture1, TextureCoordinate), texture(texture2, TextureCoordinate), 0.2);
}
