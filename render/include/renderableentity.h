#ifndef RENDERABLEENTITY_H
#define RENDERABLEENTITY_H

#include <memory>
#include "typedentity.hpp"
#include "renderobject.h"

class RenderableEntity : public TypedEntity<RenderableEntity>
{
public:
  RenderableEntity(RenderObject *r);

  std::unique_ptr<RenderObject> &getRenderObject();

  void render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &viewProjectionMatrix);

private:
  std::unique_ptr<RenderObject> renderObject;
};

#endif // RENDERABLEENTITY_H
