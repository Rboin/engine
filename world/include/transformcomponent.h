#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include <glm/glm.hpp>

#include "typedcomponent.hpp"

class TransformComponent : public TypedComponent<TransformComponent>
{
public:
  TransformComponent(int owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling);

  const glm::vec3 &getPosition();
  const glm::vec3 &getRotation();
  const glm::vec3 &getScaling();
  const glm::mat4 &getModel();

  // Component interface
public:
  void update(const float &delta) override;

private:
  glm::vec3 _position, _rotation, _scale;
  glm::mat4 _model;
};

#endif // MODELCOMPONENT_H
