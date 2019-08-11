#include "transformationsystem.h"

TransformationSystem::TransformationSystem() {}

void TransformationSystem::handle(const double delta,
                                  std::unique_ptr<Entity> &entity) {
  ComponentMap &components = entity->getComponents();
  TransformComponent &component = components.getComponent<TransformComponent>();
  // Get transformation values
  glm::vec3 position = component.getPosition();
  glm::vec3 rotation = component.getRotation();
  glm::vec3 scaling = component.getScaling();
  // Update model matrix
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
  glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x),
                                 glm::vec3(1.0f, 0.0f, 0.0f));
  rotate = glm::rotate(rotate, glm::radians(rotation.y),
                       glm::vec3(0.0f, 1.0f, 0.0f));
  rotate = glm::rotate(rotate, glm::radians(rotation.z),
                       glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), scaling);
  glm::mat4 model = translate * rotate * scale;
  component.setModel(model);
  entity->getAxis()->update(rotate);
}
