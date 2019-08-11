#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include <memory>
#include <unordered_map>

#include "component.hpp"

/**
 * @brief The ComponentList class holds an Entity's assigned components.
 * This class is used to register components to an Entity. Each entity would
 * have it's own ComponentList. Specific components can be accessed by using the
 * ComponentList::getComponent<U>() method.
 */
class ComponentMap {
 public:
  ComponentMap() {}
  ~ComponentMap() {
    if (_components.size() > 0) {
      for (auto iterator = this->_components.begin();
           iterator != this->_components.end(); ++iterator) {
        delete iterator->second;
      }
      _components.clear();
    }
  }

  /**
   * @brief addComponent
   * @param c
   */
  void addComponent(Component *component) {
    this->_components.insert({component->getComponentId(), component});
  }

  /**
   * Returns the component of the requested type.
   */
  template <class U>
  U &getComponent() {
    ComponentId requested = TypeId<Component>::get<U>();
    auto iter = this->_components.find(requested);
    U *component = nullptr;
    if (iter != this->_components.end()) {
      // Found the requested component.
      component = (U *)iter->second;
    }
    return *component;
  }

  template <class U>
  bool hasComponent() const {
    ComponentId requested = TypeId<Component>::get<U>();
    auto iter = this->_components.find(requested);
    bool result = false;
    if (iter != this->_components.end()) {
      result = true;
    }
    return result;
  }

 private:
  std::unordered_map<ComponentId, Component *> _components;
};

#endif  // COMPONENTLIST_H
