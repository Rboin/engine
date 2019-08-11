#ifndef TYPEDSYSTEM_HPP
#define TYPEDSYSTEM_HPP

#include <memory>
#include <vector>

#include "system.h"
#include "typeid.hpp"

template <class T>
class TypedSystem : public System {
 public:
  TypedSystem() { this->_id = TypeId<System>::get<T>(); }

  ~TypedSystem() {}

  virtual void handle(
      const double &delta,
      std::vector<std::unique_ptr<Entity> > &entities) override {
    for (auto iter = entities.begin(); iter != entities.end(); ++iter) {
      std::unique_ptr<Entity> &currentEntity = (*iter);
      const ComponentMap &components = currentEntity->getComponents();
      bool hasComponent = components.hasComponent<T>();
      if (hasComponent) {
        this->handle(delta, currentEntity);
      }
    }
  }

  virtual void handle(const double delta, std::unique_ptr<Entity> &entity) = 0;

 private:
  long _id;
};

#endif  // TYPEDSYSTEM_HPP
