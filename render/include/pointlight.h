#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "lightrenderobject.h"

namespace RenderObjects
{

class PointLight : public Light
{
public:
  PointLight(Mesh *m);
  void setIndex(int i);
  // BaseRenderObject interface
public:
  virtual void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
  virtual void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &modelMatrix, const glm::mat4 &viewProjectionMatrix) override;
  virtual void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
private:
  int _index, u_position, u_constant, u_linear, u_quadratic;
  glm::vec3 _currentPosition;
};

}

#endif // POINTLIGHT_H
