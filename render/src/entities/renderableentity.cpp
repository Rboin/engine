#include "renderableentity.h"

RenderableEntity::RenderableEntity(RenderObject *r) : TypedEntity()
{
  this->renderObject = std::unique_ptr<RenderObject>(r);
}

std::unique_ptr<RenderObject> &RenderableEntity::getRenderObject()
{
  return this->renderObject;
}

void RenderableEntity::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &viewProjectionMatrix)
{
//  this->renderObject->render(programId, proxy, *this, viewProjectionMatrix);
}
