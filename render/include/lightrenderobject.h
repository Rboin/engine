#ifndef LIGHTRENDEROBJECT_H
#define LIGHTRENDEROBJECT_H

#include "renderobject.h"

class LightRenderObject : public RenderObject
{
public:
  LightRenderObject(Mesh *m);

  // RenderObject interface
public:
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
  void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix) override;
  void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
  void setIsPointLight(bool p);
private:
  bool _isPointLight;
  int u_position, u_ambient, u_diffuse, u_specular, u_constant, u_linear, u_quadratic;
  glm::vec4 _currentPosition;
};

#endif // LIGHTRENDEROBJECT_H
