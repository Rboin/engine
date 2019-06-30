#version 430 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;

    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 color;

in vec2 TextureCoordinate;
in vec3 Normal;
in vec3 FragmentPosition;

#define N_POINT_LIGHTS 2
uniform Material material;
uniform Light[N_POINT_LIGHTS] light;
uniform DirectionalLight directionalLight;
uniform vec3 cameraPosition;

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
    vec3 lightDirection = normalize(-light.direction);
    float diffuseScalar = max(dot(normal, lightDirection), 0.0);
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularScalar = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);

    // Calculate resulting colors.
    vec3 diffuseTexture = vec3(texture(material.diffuse, TextureCoordinate));
    vec3 ambient = light.ambient * diffuseTexture;
    vec3 diffuse = light.diffuse * diffuseScalar * diffuseTexture;
    vec3 specular = light.specular * specularScalar * vec3(texture(material.specular, TextureCoordinate));
    return (ambient + diffuse + specular);
}

vec3 calculatePointLight(Light light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection) {
    vec3 lightDirection = normalize(light.position - fragmentPosition);

    float diffuseScalar = max(dot(normal, lightDirection), 0.0);

    vec3 reflectDirection = reflect(-lightDirection, normal);
    float specularScalar = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    // Attenuation
    float distance = length(light.position - fragmentPosition);
    float linearReduction = (light.constant + light.linear) * distance;
    float quadraticReduction = light.quadratic * (distance * distance);
    float attenuation = 1.0 / (linearReduction + quadraticReduction);
    vec3 diffuseTexture = vec3(texture(material.diffuse, TextureCoordinate));
    vec3 ambient = light.ambient * diffuseTexture;
    vec3 diffuse = light.diffuse * diffuseScalar * diffuseTexture;
    vec3 specular = light.specular * specularScalar * vec3(texture(material.specular, TextureCoordinate));

    return attenuation * (ambient + diffuse + specular);
}

void main() {


    // Emission lighting
    vec3 emission = texture(material.emission, TextureCoordinate).rgb;

    vec3 normal = normalize(Normal);
    vec3 viewDirection = normalize(cameraPosition - FragmentPosition);
    // Directional lighting
    vec3 directional = calculateDirectionalLight(directionalLight, normal, viewDirection);
    // Point lighting
    vec3 pointLights = vec3(0.0, 0.0, 0.0);
    for (int i = 0; i < N_POINT_LIGHTS; i++) {
        pointLights += calculatePointLight(light[i], normal, FragmentPosition, viewDirection);
    }

    // Resulting color
    //vec3 result = attenuation * (ambient + diffuse + specular) + emission;
    color = vec4(directional + pointLights + emission, 1.0);
}
