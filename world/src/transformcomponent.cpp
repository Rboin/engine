#include "transformcomponent.h"

#include <glm/gtc/matrix_transform.hpp>

TransformComponent::TransformComponent(long owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling)
  : TypedComponent(owner),
    _position(position),
    _rotation(rotation),
    _scale(scaling)
{

}

TransformComponent::~TransformComponent()
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

void TransformComponent::setModel(glm::mat4 m)
{
  this->_model = m;
}
