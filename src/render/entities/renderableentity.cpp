#include "renderableentity.h"

RenderableEntity::RenderableEntity(Entity *e, RenderObject *r)
{
  this->entity = std::unique_ptr<Entity>(e);
  this->renderObject = std::unique_ptr<RenderObject>(r);
}

std::unique_ptr<Entity> &RenderableEntity::getEntity()
{
  return this->entity;
}

std::unique_ptr<RenderObject> &RenderableEntity::getRenderObject()
{
  return this->renderObject;
}

void RenderableEntity::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &viewProjectionMatrix)
{
  this->renderObject->render(programId, proxy, this->entity->getModelMatrix(), viewProjectionMatrix);
}

void RenderableEntity::update(const double &delta)
{
  this->entity->update(delta);
}
