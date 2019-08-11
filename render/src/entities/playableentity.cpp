#include "playableentity.h"

PlayableEntity::PlayableEntity(std::shared_ptr<Camera> c) : Entity() {
  this->_camera = c;
}

PlayableEntity::~PlayableEntity() {
  //
}

std::shared_ptr<Camera> &PlayableEntity::getCamera() { return this->_camera; }

// void PlayableEntity::update(const double delta)
//{
//  this->_camera->update(delta);
//}

void PlayableEntity::setPosition(glm::vec3 p) {
  ComponentMap &components = getComponents();
  TransformComponent &transformComponent =
      components.getComponent<TransformComponent>();
  transformComponent.setPosition(p);
  this->_camera->setPosition(p);
}

void PlayableEntity::setRotation(glm::vec3 r) {
  ComponentMap &components = getComponents();
  TransformComponent &transformComponent =
      components.getComponent<TransformComponent>();
  transformComponent.setRotation(r);
  this->_camera->setRotation(-r);
}

void PlayableEntity::setScaling(glm::vec3 s) {
  ComponentMap &components = getComponents();
  TransformComponent &transformComponent =
      components.getComponent<TransformComponent>();
  transformComponent.setScaling(s);
}
