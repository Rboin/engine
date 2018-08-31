#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "lightrenderobject.h"

namespace RenderObjects
{

class DirectionalLight : public Light
{
public:
  DirectionalLight(Mesh *m);
  // BaseRenderObject interface
public:
  virtual void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
  virtual void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &modelMatrix, const glm::mat4 &viewProjectionMatrix) override;
  virtual void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;

private:
  int u_direction;
  glm::vec3 _direction;
};

}
#endif // DIRECTIONALLIGHT_H
