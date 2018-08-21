#include "movingentity.h"

MovingEntity::MovingEntity() : TypedEntity()
{

}

MovingEntity::~MovingEntity()
{

}

void MovingEntity::update(const float &delta)
{

  glm::vec3 rot = glm::vec3(1.0f, 1.0f, 0.0f);
  const glm::vec3 &currentRotation = this->_components->getComponent<TransformComponent>()->getRotation();
  rot = currentRotation + rot;
  this->_components->getComponent<TransformComponent>()->setRotation(rot);
  Entity::update(delta);
}
