#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

class Entity
{
public:
  Entity();
  virtual ~Entity();

  const glm::mat4 &getModelMatrix();
  const glm::vec3 &getPosition();
  const glm::vec3 &getRotation();
  const glm::vec3 &getScaling();

  virtual void setPosition(glm::vec3 p);
  virtual void setRotation(glm::vec3 r);
  virtual void setScaling(glm::vec3 s);

  virtual void update(const float &delta);

protected:
  glm::vec3 _position, _rotation, _scaling;
  glm::mat4 _model;

  void updateModelMatrix();
};

#endif // ENTITY_H
