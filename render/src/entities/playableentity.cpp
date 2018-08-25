#include "playableentity.h"

PlayableEntity::PlayableEntity(std::shared_ptr<Camera> c) :
  Entity()
{
  this->_camera = c;
}

std::shared_ptr<Camera> &PlayableEntity::getCamera()
{
  return this->_camera;
}

void PlayableEntity::update(const float &delta)
{
  this->_camera->update(delta);
  Entity::update(delta);
}

void PlayableEntity::setPosition(glm::vec3 p)
{
  this->getComponents()->getComponent<TransformComponent>()->setPosition(p);
  this->_camera->setPosition(p);
}

void PlayableEntity::setRotation(glm::vec3 r)
{
  this->getComponents()->getComponent<TransformComponent>()->setRotation(r);
  this->_camera->setRotation(-r);
}

void PlayableEntity::setScaling(glm::vec3 s)
{
  this->getComponents()->getComponent<TransformComponent>()->setScaling(s);
}
