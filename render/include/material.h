#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory>
#include <GL/gl.h>
#include <glm/glm.hpp>


#include "openglfunctionproxy.h"

class Material
{
public:
  Material(float power, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized();
  GLint getUniformAmbient() const;
  GLint getUniformDiffuse() const;
  GLint getUniformSpecular() const;
  glm::vec3 &getAmbientColor();
  float getReflectPower();
private:
  bool _initialized;
  GLint u_ambient, u_diffuse, u_specular;
  float _power;
  glm::vec3 _ambientColor, _diffuseColor, _specularColor;

};

#endif // MATERIAL_H
