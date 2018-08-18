#include "entity.h"


Entity::Entity(std::shared_ptr<Axis> &a)
{
}

Entity::~Entity()
{
}

const glm::mat4 &Entity::getModelMatrix()
{
  return this->_model;
}

const glm::vec3 &Entity::getPosition()
{
  return this->_position;
}

void Entity::setPosition(glm::vec3 p)
{
  this->_position = p;
}

const glm::vec3 &Entity::getRotation()
{
  return this->_rotation;
}

void Entity::setRotation(glm::vec3 r)
{
  this->_rotation = r;
}

const glm::vec3 &Entity::getScaling()
{
  return this->_scaling;
}

std::shared_ptr<Axis> &Entity::getAxis()
{
  return this->_axis;
}

const unsigned int Entity::getId()
{
  return this->_id;
}

void Entity::setScaling(glm::vec3 s)
{
  this->_scaling = s;
}

void Entity::setAxis(std::shared_ptr<Axis> &a)
{
  this->_axis = a;
}

void Entity::update(const float &delta)
{
}

void Entity::updateModelMatrix()
{
}
