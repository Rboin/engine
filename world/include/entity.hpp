#ifndef ENTITY_H
#define ENTITY_H

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
         std::shared_ptr<ComponentMap> c = std::make_shared<ComponentMap>())
  {
    this->_axis = a;
    this->_components = c;
  }

  virtual ~Entity() {}

  virtual std::shared_ptr<Axis> getAxis()
  {
    return this->_axis;
  }

  virtual std::shared_ptr<ComponentMap> getComponents()
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
    // This method can be used to implement custom update behaviour (e.g. the player)
  }

protected:
  int _id;
  std::shared_ptr<Axis> _axis;
  std::shared_ptr<ComponentMap> _components;
};

#endif // ENTITY_HPP
