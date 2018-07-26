#include "axis.h"

Axis::Axis(glm::vec3 up, glm::vec3 direction, glm::vec3 right)
{
  this->_initial_up = up;
  this->_current_up = up;
  this->_initial_direction = direction;
  this->_current_direction = direction;
  this->_initial_right = right;
  this->_current_right = right;
}

void Axis::update(const glm::mat4 &rotation)
{
  glm::vec4 tmp = glm::vec4(this->_initial_direction.x, this->_initial_direction.y, this->_initial_direction.z, 0.0f);
  tmp = glm::normalize(rotation * tmp);
  this->_current_direction = glm::vec3(tmp.x, tmp.y, tmp.z);
  this->_current_right = glm::cross(this->_current_direction, this->_initial_up);
  this->_current_up = glm::cross(this->_current_direction, this->_current_right);
}

const glm::vec3 &Axis::getCurrentUp() const
{
  return this->_current_up;
}

const glm::vec3 &Axis::getCurrentDirection() const
{
  return this->_current_direction;
}

const glm::vec3 &Axis::getCurrentRight() const
{
  return this->_current_right;
}
