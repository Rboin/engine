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

class Entity
{
public:
  Entity(std::shared_ptr<Axis> axis = std::make_shared<Axis>(),
         std::shared_ptr<ComponentMap> components = std::make_shared<ComponentMap>());

  virtual ~Entity();

  std::shared_ptr<Axis> getAxis();

  std::shared_ptr<ComponentMap> getComponents();

  void addComponent(Component *component);

  void setAxis(std::shared_ptr<Axis> axis);

  long getId() const;

//  virtual void update(const double delta) = 0;

protected:
  long id;
  std::shared_ptr<Axis> axis;
  std::shared_ptr<ComponentMap> components;
};

#endif // ENTITY_H
