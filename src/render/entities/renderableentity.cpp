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

void RenderableEntity::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->renderObject->render(programId, proxy);
}

void RenderableEntity::update(const double &delta)
{
  this->entity->update(delta);
}
