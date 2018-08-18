#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "typeid.hpp"
#include "axis.h"

/**
 * @brief The BaseEntity base class.
 *
 */
class Entity
{
public:
  Entity(std::shared_ptr<Axis> a = std::make_shared<Axis>())
  {
    this->_axis = a;
    this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_scaling = glm::vec3(1.0f, 1.0f, 1.0f);
  }

  virtual ~Entity() {}

  virtual const glm::mat4 &getModelMatrix()
  {
    return this->_model;
  }

  virtual const glm::vec3 &getPosition()
  {
    return this->_position;
  }

  virtual const glm::vec3 &getRotation()
  {
    return this->_rotation;
  }

  virtual const glm::vec3 &getScaling()
  {
    return this->_scaling;
  }

  virtual std::shared_ptr<Axis> &getAxis()
  {
    return this->_axis;
  }

  virtual void setPosition(glm::vec3 p)
  {
    this->_position = p;
  }

  virtual void setRotation(glm::vec3 r)
  {
    this->_rotation = r;
  }

  virtual void setScaling(glm::vec3 s)
  {
    this->_scaling = s;
  }

  virtual void setAxis(std::shared_ptr<Axis> &a)
  {
    this->_axis = a;
  }

  virtual void update(const float &delta)
  {
    //  this->_rotation.x += (delta * 10);
    //  this->_rotation.y += (delta * 10);
    // Update logic (calculate velocities etc).
    this->updateModelMatrix();
    this->_axis->update(this->_rotate);
  }

protected:
  glm::vec3 _position, _rotation, _scaling;
  glm::mat4 _model, _translate, _rotate, _scale;
  std::shared_ptr<Axis> _axis;

  virtual void updateModelMatrix()
  {
    this->_translate = glm::translate(glm::mat4(1.0f), this->_position);
    this->_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    this->_rotate = glm::rotate(this->_rotate, glm::radians(this->_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    this->_rotate = glm::rotate(this->_rotate, glm::radians(this->_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    this->_scale = glm::scale(glm::mat4(1.0f), this->_scaling);
    this->_model = this->_translate * this->_rotate * this->_scale;
  }
};

#endif // ENTITY_HPP
