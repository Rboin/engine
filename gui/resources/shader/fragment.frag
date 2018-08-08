#version 430 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};

struct Light {
    vec4 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

out vec4 color;

in vec2 TextureCoordinate;
in vec3 Normal;
in vec3 FragmentPosition;

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;

vec3 calculateLightDirection(vec3 lightPosition, float w) {
    if (w == 0.0)
        return normalize(-lightPosition);
    else if (w == 1.0)
        return normalize(lightPosition - FragmentPosition);
}

void main() {
    vec3 lightPosition = vec3(light.position);
    // Ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TextureCoordinate).rgb;

    // Diffuse lighting
    vec3 normalized = normalize(Normal);
    vec3 lightRayDirection = calculateLightDirection(lightPosition, light.position.w);
    float diffuseScalar = max(dot(normalized, lightRayDirection), 0.0);
    vec3 diffuse = light.diffuse * diffuseScalar * texture(material.diffuse, TextureCoordinate).rgb;

    // Specular lighting
    vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
    vec3 reflectDirection = reflect(-lightRayDirection, normalized);
    float specularScalar = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular = light.specular * specularScalar * texture(material.specular, TextureCoordinate).rgb;

    // Emission lighting
    vec3 emission = texture(material.emission, TextureCoordinate).rgb;

    // Attenuation
    float distance = length(lightPosition - FragmentPosition);
    float linearReduction = (light.constant + light.linear) * distance;
    float quadraticReduction = light.quadratic * (distance * distance);
    float attenuation = 1.0 / (linearReduction + quadraticReduction);

    // Resulting color
    vec3 result = attenuation * (ambient + diffuse + specular) + emission;
    color = vec4(result, 1.0);
}
