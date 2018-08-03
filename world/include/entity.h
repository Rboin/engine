#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <glm/glm.hpp>

#include "axis.h"

class Entity
{
public:
  Entity(std::shared_ptr<Axis> &a);
  virtual ~Entity();

  const glm::mat4 &getModelMatrix();
  const glm::vec3 &getPosition();
  const glm::vec3 &getRotation();
  const glm::vec3 &getScaling();
  std::shared_ptr<Axis> &getAxis();

  virtual void setPosition(glm::vec3 p);
  virtual void setRotation(glm::vec3 r);
  virtual void setScaling(glm::vec3 s);
  virtual void setAxis(std::shared_ptr<Axis> &a);

  virtual void update(const float &delta);

protected:
  glm::vec3 _position, _rotation, _scaling;
  glm::mat4 _model, _translate, _rotate, _scale;
  std::shared_ptr<Axis> _axis;

  void updateModelMatrix();
};

#endif // ENTITY_H