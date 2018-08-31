#include "scene.h"

Scene::Scene(std::shared_ptr<Camera> camera, std::shared_ptr<World> world, PlayableEntity *player, Entity *directionalLight)
{
  this->_camera = camera;
  this->_world = world;
  this->_player = std::unique_ptr<PlayableEntity>(player);
  this->_directionalLight = std::unique_ptr<Entity>(directionalLight);
  this->_pointLights = std::vector<std::unique_ptr<Entity>>();
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

void Scene::addPointLight(Entity *light)
{

  this->_pointLights.push_back(std::unique_ptr<Entity>(light));
}

std::vector<std::unique_ptr<Entity> > &Scene::getPointLights()
{
  return this->_pointLights;
}

std::unique_ptr<Entity> &Scene::getDirectionalLight()
{
  return this->_directionalLight;
}

void Scene::update(const double &delta)
{
  if (this->_player) {
    this->_player->update(delta);
  }
  if (this->_directionalLight) {
    this->_directionalLight->update(delta);
  }
  std::vector<std::unique_ptr<System>> &systems = this->_world->getSystems();
  std::vector<std::unique_ptr<Entity>> &entities = this->_world->getEntities();
  for (auto it = systems.begin(); it != systems.end(); ++it) {
    std::unique_ptr<System> &currentSystem = (*it);
    currentSystem->update(delta, entities);
    currentSystem->update(delta, this->_pointLights);
  }
}
