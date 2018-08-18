#include "playableentity.h"

PlayableEntity::PlayableEntity(std::shared_ptr<Camera> c, RenderObject *r) :
  RenderableEntity(r)
{
  this->_camera = c;
}

std::shared_ptr<Camera> &PlayableEntity::getCamera()
{
  return this->_camera;
}

void PlayableEntity::update(const float &delta)
{
  RenderableEntity::update(delta);
  this->_camera->update(delta);
}

void PlayableEntity::setPosition(glm::vec3 p)
{
  Entity::setPosition(p);
  this->_camera->setPosition(p);
}

void PlayableEntity::setRotation(glm::vec3 r)
{
  Entity::setRotation(r);
  this->_camera->setRotation(-r);
}
