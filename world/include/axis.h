#ifndef AXIS_H
#define AXIS_H

#include <glm/glm.hpp>

/**
 * Class that holds the current orientation in 3D space.
 * The orientation can be updated using the rotation
 * matrices of entities or cameras using the
 * Axis::update(const glm::mat4 &) method.
 *
 * The Axis's default values are:
 * (Y) up = {0, 1, 0}
 * (-Z) forward = {0, 0, -1}
 * (X) right = {1, 0, 0}
 * @brief The Axis class
 */
class Axis
{
public:
  Axis(glm::vec3 up = {0.0f, 1.0f, 0.0f},
       glm::vec3 direction = {0.0f, 0.0f, -1.0f},
       glm::vec3 right = {1.0f, 0.0f, 0.0f});

  void update(const glm::mat4 &rotation);

  const glm::vec3 &getCurrentUp() const;
  const glm::vec3 &getCurrentDirection() const;
  const glm::vec3 &getCurrentRight() const;

private:
  glm::vec3 _initial_up, _initial_direction, _initial_right,
      _current_up, _current_direction, _current_right;
};

#endif // AXIS_H
