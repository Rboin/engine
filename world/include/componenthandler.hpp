#ifndef COMPONENTHANDLER_H
#define COMPONENTHANDLER_H

#include <vector>
#include <memory>

#include "entity.hpp"

/**
 * @brief The ComponentHandler class handles the updating of specific components.
 *
 * This is the base class for all Component Handlers. Each handler defines which type of component it handles.
 */
class ComponentHandler
{
public:
  virtual void update(const std::vector<std::unique_ptr<Entity>> &entities, const double &delta) = 0;
};

template<class T>
class TypedComponentHandler : public ComponentHandler
{
  // ComponentHandler interface
public:
  virtual void update(const std::vector<std::unique_ptr<Entity> > &entities, const double &delta) override
  {
    typename std::vector<std::unique_ptr<Entity>>::const_iterator it;
    for (it = entities.begin(); it != entities.end(); ++it) {
      std::shared_ptr<T> component = (*it)->getComponents()->template getComponent<T>();
      if (component != nullptr) {
        this->handle(component, delta);
      }
    }
  }

  virtual void handle(std::shared_ptr<T> &c, const double &delta) = 0;
};

#endif // COMPONENTHANDLER_H
