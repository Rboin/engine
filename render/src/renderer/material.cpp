#include "material.h"

Material::Material(float reflectPower, float shinePower, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
  _initialized(false),
  _power(reflectPower),
  _shinePower(shinePower),
  _ambientColor(ambient),
  _diffuseColor(diffuse),
  _specularColor(specular)
{}

void Material::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{

}

bool Material::isInitialized()
{
  return this->_initialized;
}

GLint Material::getUniformAmbient() const
{
  return this->u_ambient;
}

GLint Material::getUniformDiffuse() const
{
  return this->u_diffuse;
}

GLint Material::getUniformSpecular() const
{
  return this->u_specular;
}

glm::vec3 &Material::getAmbientColor()
{
  return this->_ambientColor;
}

float Material::getReflectPower()
{
  return this->_power;
}

float Material::getShinePower()
{
  return this->_shinePower;
}
