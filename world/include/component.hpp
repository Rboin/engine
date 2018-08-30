#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "typeid.hpp"

using OwnerId = int;
using ComponentId = int;

class Component
{
public:

  Component(OwnerId owner)
  {
    this->_owner_id = owner;
    this->_id = -1;
  }

  virtual ~Component() {}

  const ComponentId getComponentId() const
  {
    return this->_id;
  }

  const OwnerId getOwnerId() const
  {
    return this->_owner_id;
  }

protected:
  OwnerId _owner_id;
  ComponentId _id;
};

#endif // COMPONENT_HPP
