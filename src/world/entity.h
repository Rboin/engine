#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

class Entity
{
public:
  Entity();
  virtual ~Entity();

  const glm::mat4 &getModelMatrix();

  virtual void update(const double &delta);

protected:
  glm::vec3 _position, _rotation, _scaling;
  glm::mat4 _model;

  void updateModelMatrix();
};

#endif // ENTITY_H
