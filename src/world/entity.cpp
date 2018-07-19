#include "entity.h"
#include "glm/gtc/matrix_transform.hpp"

Entity::Entity()
{
}

Entity::~Entity()
{
}

glm::mat4 Entity::getModelMatrix()
{
  const glm::vec3 &pos = this->position;
  glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), pos);
  glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 rotationMatrix = rotX * rotY * rotZ;
  const glm::vec3 &scale = this->scaling;
  glm::mat4 scalingMatrix = glm::scale(glm::mat4(1.0f), scale);
  glm::mat4 model = translationMatrix * rotationMatrix * scalingMatrix;
  return model;
}
