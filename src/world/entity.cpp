#include "entity.h"
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity()
{
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

void Entity::update(const double &delta)
{
//  this->_rotation.x += (delta * 10);
//  this->_rotation.y += (delta * 10);
  // Update logic (calculate velocities etc).
  this->updateModelMatrix();
}

void Entity::updateModelMatrix()
{
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), this->_position),
            rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)),
            rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)),
            rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)),
            rotation = rotateZ * rotateY * rotateX,
            scale = glm::scale(glm::mat4(1.0f), this->_scaling);
  this->_model = translate * rotation * scale;
}
