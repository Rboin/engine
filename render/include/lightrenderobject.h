#ifndef LIGHTRENDEROBJECT_H
#define LIGHTRENDEROBJECT_H

#include "renderobject.h"

class LightRenderObject : public RenderObject
{
public:
  LightRenderObject(Mesh *m);

  // RenderObject interface
public:
  void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix) override;
  void setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy) override;
private:
  glm::vec3 _currentPosition;
};

#endif // LIGHTRENDEROBJECT_H