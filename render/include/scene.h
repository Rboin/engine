#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "playableentity.h"
#include "world.h"

class Scene
{
public:
  Scene(std::shared_ptr<Camera> camera, std::shared_ptr<World> world, PlayableEntity *player);

  void setCamera(std::shared_ptr<Camera> camera);
  std::shared_ptr<Camera> getCamera();

  void setWorld(std::shared_ptr<World> world);
  std::shared_ptr<World> getWorld();

  std::unique_ptr<PlayableEntity> &getPlayer();

  void addLight(Entity *light);
  std::vector<std::unique_ptr<Entity>> &getLights();

  void update(const double &delta);

private:
  std::shared_ptr<Camera> _camera;
  std::shared_ptr<World> _world;
  std::unique_ptr<PlayableEntity> _player;
  std::vector<std::unique_ptr<Entity>> _lights;
};

#endif // SCENE_H
