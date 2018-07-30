#include "renderableentity.h"

RenderableEntity::RenderableEntity(Entity *e, RenderObject *r) : Entity(e->getAxis())
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
  this->renderObject->render(programId, proxy, this->entity, viewProjectionMatrix);
}

void RenderableEntity::update(const float &delta)
{
  this->entity->update(delta);
}

void RenderableEntity::setPosition(glm::vec3 p)
{
  this->entity->setPosition(p);
}

void RenderableEntity::setRotation(glm::vec3 r)
{
  this->entity->setRotation(r);
}

void RenderableEntity::setScaling(glm::vec3 s)
{
  this->entity->setScaling(s);
}
