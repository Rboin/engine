#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "playableentity.h"
#include "world.h"

class Scene {
 public:
  Scene(std::shared_ptr<Camera> camera, std::shared_ptr<World> world);
  //  Scene(std::shared_ptr<Camera> camera, std::shared_ptr<World> world,
  //  PlayableEntity *player, Entity *directionalLight);

  void setCamera(Camera *camera);
  Camera &getCamera();

  void setWorld(World *world);
  World &getWorld();

  //  std::unique_ptr<PlayableEntity> &getPlayer();

  void addPointLight(Entity *light);
  std::vector<std::unique_ptr<Entity>> &getPointLights();
  void addDirectionalLight(Entity *directionalLight);
  Entity &getDirectionalLight();

  void update(const double delta);

 private:
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<World> _world;
  //  std::unique_ptr<PlayableEntity> _player;
  std::vector<std::unique_ptr<Entity>> directionalLights;
  std::vector<std::unique_ptr<Entity>> _pointLights;
};

#endif  // SCENE_H
