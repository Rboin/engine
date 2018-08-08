#version 430 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
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

void main() {
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoordinate));

    // Diffuse lighting
    vec3 normalized = normalize(Normal);
    vec3 lightRayDirection = normalize(light.position - FragmentPosition);
    float diffuseScalar = max(dot(normalized, lightRayDirection), 0.0);
    vec3 diffuse = light.diffuse * diffuseScalar * vec3(texture(material.diffuse, TextureCoordinate));

    // Specular lighting
    vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightRayDirection, normalized);
    float specularScalar = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * specularScalar * vec3(texture(material.specular, TextureCoordinate));

    // Resulting color
    color = vec4(ambient + diffuse + specular, 1.0);
}
