#include "material.h"

Material::Material(float shinePower, Texture *texture, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
  _initialized(false),
  _shinePower(shinePower),
  _texture(texture),
  _ambientColor(ambient),
  _diffuseColor(diffuse),
  _specularColor(specular),
  u_shinePower(-1),
  u_ambient(-1),
  u_diffuse(-1),
  u_specular(-1)
{}

void Material::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->_texture->initialize(programId, proxy);
  if (this->u_shinePower < 0) {
    this->u_shinePower = proxy->glGetUniformLocation(programId, "material.shininess");
  }

//  if (this->u_ambient < 0) {
//    this->u_ambient = proxy->glGetUniformLocation(programId, "material.ambient");
//  }
//  if (this->u_diffuse < 0) {
//    this->u_specular = proxy->glGetUniformLocation(programId, "material.diffuse");
//  }
//  if (this->u_specular < 0) {
//    this->u_specular = proxy->glGetUniformLocation(programId, "material.specular");
//  }
}

bool Material::isInitialized()
{
  return this->_initialized;
}

int Material::getUniformShininess() const
{
  return this->u_shinePower;
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

glm::vec3 &Material::getDiffuseColor()
{
  return this->_diffuseColor;
}

glm::vec3 &Material::getSpecularColor()
{
  return this->_specularColor;
}

std::unique_ptr<Texture> &Material::getTexture()
{
  return this->_texture;
}

float Material::getShinePower()
{
  return this->_shinePower;
}
