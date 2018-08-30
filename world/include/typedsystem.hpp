#ifndef TYPEDSYSTEM_HPP
#define TYPEDSYSTEM_HPP

#include <memory>
#include <vector>

#include "system.h"
#include "typeid.hpp"


template<class T>
class TypedSystem : public System
{
public:

  TypedSystem()
  {
    this->_id = TypeId<System>::get<T>();
  }

  virtual void update(const float &delta, std::vector<std::unique_ptr<Entity> > &entities) override
  {
    for (auto iter = entities.begin(); iter != entities.end(); ++iter) {
      std::unique_ptr<Entity> &currentEntity = (*iter);
      bool hasComponent = currentEntity->getComponents()->hasComponent<T>();
      if (hasComponent) {
        this->update(delta, currentEntity);
      }
    }
  }

  virtual void update(const float &delta, std::unique_ptr<Entity> &entity) = 0;

private:
  long _id;
};

#endif // TYPEDSYSTEM_HPP
