#include "entity.h"

Entity::Entity(std::shared_ptr<Axis> axis,
               std::shared_ptr<ComponentMap> components) {
  this->axis = axis;
  this->components = components;
  this->id = TypeId<Entity>::template get<Entity>();
}

Entity::~Entity() {}

std::shared_ptr<Axis> Entity::getAxis() { return axis; }

ComponentMap &Entity::getComponents() { return *components; }

void Entity::addComponent(Component *component) {
  components->addComponent(component);
}

void Entity::setAxis(std::shared_ptr<Axis> axis) { this->axis = axis; }

long Entity::getId() const { return id; }
