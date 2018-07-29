#include "playableentity.h"

PlayableEntity::PlayableEntity(Camera *c, Entity *e, RenderObject *r) :
  RenderableEntity(e, r)
{
  this->_camera = std::unique_ptr<Camera>(c);
}

std::shared_ptr<Camera> &PlayableEntity::getCamera()
{
  return this->_camera;
}

void PlayableEntity::update(const float &delta)
{
  this->_camera->update(delta);

  this->setPosition(this->_camera->getPosition() + glm::vec3(0.0f, 0.0f, 0.5f));

  // Inverse the camera's rotation.
  glm::vec3 rotation = -this->_camera->getRotationVector();
  this->setRotation(rotation);
  RenderableEntity::update(delta);
}
