#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>


#include "openglfunctionproxy.h"

class Material
{
public:
  Material(float shinePower, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized();
  int getUniformShininess() const;
  int getUniformAmbient() const;
  int getUniformDiffuse() const;
  int getUniformSpecular() const;
  glm::vec3 &getAmbientColor();
  glm::vec3 &getDiffuseColor();
  glm::vec3 &getSpecularColor();
  float getShinePower();
private:
  bool _initialized;
  int u_shinePower, u_ambient, u_diffuse, u_specular;
  float _shinePower;
  glm::vec3 _ambientColor, _diffuseColor, _specularColor;

};

#endif // MATERIAL_H
