#include "entity.h"
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity(std::shared_ptr<Axis> &a)
{
  this->_axis = a;
  this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
  this->_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  this->_scaling = glm::vec3(1.0f, 1.0f, 1.0f);
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
//  this->_rotation.x += (delta * 10);
//  this->_rotation.y += (delta * 10);
  // Update logic (calculate velocities etc).
  this->updateModelMatrix();
  this->_axis->update(this->_rotate);
}

void Entity::updateModelMatrix()
{
  this->_translate = glm::translate(glm::mat4(1.0f), this->_position);
  this->_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  this->_rotate = glm::rotate(this->_rotate, glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  this->_rotate = glm::rotate(this->_rotate, glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  this->_scale = glm::scale(glm::mat4(1.0f), this->_scaling);
  this->_model = this->_translate * this->_rotate * this->_scale;
}
