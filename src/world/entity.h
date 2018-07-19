#ifndef ENTITY_H
#define ENTITY_H

#include "glm/glm.hpp"

class Entity
{
public:
  Entity();
  virtual ~Entity();

  glm::mat4 getModelMatrix();

  virtual void update(const int &delta) = 0;
  virtual void render() = 0;

protected:
  glm::vec4 position;
  glm::vec4 rotation;
  glm::vec4 scaling;
};

#endif // ENTITY_H
