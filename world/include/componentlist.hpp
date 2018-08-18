#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <memory>
#include <unordered_map>

#include "component.hpp"


/**
 * @brief The ComponentList class holds an Entity's assigned components.
 * This class is used to register components to an Entity. Each entity would have it's own ComponentList.
 * Specific components can be accessed by using the ComponentList::getComponent<U>() method.
 */
class ComponentList
{
public:
  ComponentList() {}
  ~ComponentList() {}

  /**
   * @brief addComponent
   * @param c
   */
  void addComponent(Component *c)
  {
    this->_components.insert({c->getComponentId(), std::shared_ptr<Component>(c)});
  }

  void addComponent(std::shared_ptr<Component> c)
  {
    this->_components.insert({c->getComponentId(), c});
  }

  /**
   * Returns the component of the requested type.
   */
  template<class U>
  std::shared_ptr<U> getComponent()
  {
    ComponentId requested = TypeId<Component>::get<U>();
    auto iter = this->_components.find(requested);
    std::shared_ptr<U> component = nullptr;
    if (iter != this->_components.end()) {
      // Found the requested component.
      component = std::static_pointer_cast<U>(iter->second);
    }
    return component;
  }
private:
  std::unordered_map<ComponentId, std::shared_ptr<Component>> _components;
};

#endif // COMPONENTLIST_H
