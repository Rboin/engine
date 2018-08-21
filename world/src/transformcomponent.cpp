#include "transformcomponent.h"

#include <glm/gtc/matrix_transform.hpp>

TransformComponent::TransformComponent(int owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling)
  : TypedComponent(owner),
    _position(position),
    _rotation(rotation),
    _scale(scaling)
{

}

const glm::vec3 &TransformComponent::getPosition()
{
  return this->_position;
}

void TransformComponent::setPosition(glm::vec3 p)
{
  this->_position = p;
}

const glm::vec3 &TransformComponent::getRotation()
{
  return this->_rotation;
}

void TransformComponent::setRotation(glm::vec3 r)
{
  this->_rotation = r;
}

const glm::vec3 &TransformComponent::getScaling()
{
  return this->_scale;
}

void TransformComponent::setScaling(glm::vec3 s)
{
  this->_scale = s;
}

const glm::mat4 &TransformComponent::getModel()
{
  return this->_model;
}

void TransformComponent::update(const float &delta)
{
  // Translation
  this->_model = glm::translate(glm::mat4(1.0f), this->_position);
  // Rotation
  this->_model = glm::rotate(this->_model, glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  this->_model = glm::rotate(this->_model, glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  this->_model = glm::rotate(this->_model, glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  // Scaling
  this->_model = glm::scale(this->_model, this->_scale);
}
