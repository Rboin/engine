#ifndef TYPEENTITY_HPP
#define TYPEENTITY_HPP

#include "entity.hpp"

// TODO: MAKE OTHER ENTITIES INHERIT FROM THIS WITH THEIR OWN TYPE AS T

template<class T>
class TypedEntity : public Entity
{
public:
  TypedEntity() : Entity()
  {
    this->_id = TypeId<Entity>::template get<T>();
  }

  virtual ~TypedEntity()
  {}
};

#endif // TYPEENTITY_HPP
