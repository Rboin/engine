#include "scene.h"

Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<World> world, PlayableEntity *player)
{
  this->_camera = camera;
  this->_world = world;
  this->_player = std::unique_ptr<PlayableEntity>(player);
  this->_lights = std::vector<std::unique_ptr<Entity>>();
}

void Scene::setCamera(std::shared_ptr<Camera> camera)
{
  this->_camera = camera;
}

std::shared_ptr<Camera> Scene::getCamera()
{
  return this->_camera;
}

void Scene::setWorld(std::shared_ptr<World> world)
{
  this->_world = world;
}

std::shared_ptr<World> Scene::getWorld()
{
  return this->_world;
}

std::unique_ptr<PlayableEntity> &Scene::getPlayer()
{
  return this->_player;
}

void Scene::addLight(Entity *light)
{
  this->_lights.push_back(std::unique_ptr<Entity>(light));
}

std::vector<std::unique_ptr<Entity> > &Scene::getLights()
{
  return this->_lights;
}

void Scene::update(const double &delta)
{
  this->_player->update(delta);
  std::vector<std::unique_ptr<System>> &systems = this->_world->getSystems();
  std::vector<std::unique_ptr<Entity>> &entities = this->_world->getEntities();
  for (auto it = systems.begin(); it != systems.end(); ++it) {
    std::unique_ptr<System> &currentSystem = (*it);
    currentSystem->update(delta, entities);
    currentSystem->update(delta, this->_lights);
  }
}
