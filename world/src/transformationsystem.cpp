#include "transformationsystem.h"

TransformationSystem::TransformationSystem()
{

}

void TransformationSystem::update(const float &delta, std::unique_ptr<Entity> &entity)
{

  std::shared_ptr<TransformComponent> component = entity->getComponents()->getComponent<TransformComponent>();
  // Get transformation values
  glm::vec3 position = component->getPosition(),
            rotation = component->getRotation(),
            scaling  = component->getScaling();
  // Update model matrix
  glm::mat4 translate, rotate, scale, model;
  translate = glm::translate(glm::mat4(1.0f), position);
  rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  rotate = glm::rotate(rotate, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  rotate = glm::rotate(rotate, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  scale = glm::scale(glm::mat4(1.0f), scaling);
  model = translate * rotate * scale;
  component->setModel(model);
  entity->getAxis()->update(rotate);
  entity->update(delta);
}
