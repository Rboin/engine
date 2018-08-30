#ifndef MODELCOMPONENT_H
#define MODELCOMPONENT_H

#include <glm/glm.hpp>

#include "typedcomponent.hpp"

class TransformComponent : public TypedComponent<TransformComponent>
{
public:
  TransformComponent(int owner, glm::vec3 position, glm::vec3 rotation, glm::vec3 scaling);

  const glm::vec3 &getPosition();
  void setPosition(glm::vec3 p);
  const glm::vec3 &getRotation();
  void setRotation(glm::vec3 r);
  const glm::vec3 &getScaling();
  void setScaling(glm::vec3 s);
  const glm::mat4 &getModel();
  void setModel(glm::mat4 m);

private:
  glm::vec3 _position, _rotation, _scale;
  glm::mat4 _model;
};

#endif // MODELCOMPONENT_H
