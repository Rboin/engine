#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "typeid.hpp"
#include "axis.h"
#include "componentlist.hpp"
#include "transformcomponent.h"

/**
 * @brief The BaseEntity base class.
 *
 */
class Entity
{
public:
  Entity(std::shared_ptr<Axis> a = std::make_shared<Axis>(),
         std::shared_ptr<ComponentList> c = std::make_shared<ComponentList>())
  {
    this->_axis = a;
    this->_components = c;
  }

  virtual ~Entity() {}

  virtual std::shared_ptr<Axis> getAxis()
  {
    return this->_axis;
  }

  virtual std::shared_ptr<ComponentList> getComponents()
  {
    return this->_components;
  }

  virtual void addComponent(Component *c)
  {
    this->_components->addComponent(c);
  }

  virtual void setAxis(std::shared_ptr<Axis> a)
  {
    this->_axis = a;
  }

  virtual const int getId() const
  {
    return this->_id;
  }

  virtual void update(const float &delta)
  {
    //  this->_rotation.x += (delta * 10);
    //  this->_rotation.y += (delta * 10);
    // Update logic (calculate velocities etc).
    this->_components->update(delta);
    const glm::vec3 &rotation = this->_components->getComponent<TransformComponent>()->getRotation();
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    this->_axis->update(rotationMatrix);
  }

protected:
  int _id;
  std::shared_ptr<Axis> _axis;
  std::shared_ptr<ComponentList> _components;
};

#endif // ENTITY_HPP
