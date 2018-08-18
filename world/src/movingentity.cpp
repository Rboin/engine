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
  rot = this->getRotation() + rot;
  this->setRotation(rot);
  Entity::update(delta);
}
