#ifndef TYPEDCOMPONENT_HPP
#define TYPEDCOMPONENT_HPP

#include "component.hpp"

template<class T>
class TypedComponent : public Component
{
public:
  TypedComponent(OwnerId ownerId) : Component(ownerId)
  {
    this->id = TypeId<Component>::get<T>();
  }
};

#endif // TYPEDCOMPONENT_HPP
