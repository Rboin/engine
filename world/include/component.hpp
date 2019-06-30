#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "typeid.hpp"

using OwnerId = long;
using ComponentId = long;

class Component
{
public:

  Component(OwnerId owner)
  {
    ownerId = owner;
    id = -1;
  }

  virtual ~Component() {}

  ComponentId getComponentId() const
  {
    return id;
  }

  OwnerId getOwnerId() const
  {
    return ownerId;
  }

protected:
  OwnerId ownerId;
  ComponentId id;
};

#endif // COMPONENT_HPP
