#ifndef AXIS_H
#define AXIS_H

#include <glm/glm.hpp>

/**
 * Class that holds the current orientation in 3D space.
 * The orientation can be updated using the rotation
 * matrices of entities or cameras using the
 * Axis::update(const glm::mat4 &) method.
 * @brief The Axis class
 */
class Axis
{
public:
  Axis(glm::vec3 up, glm::vec3 direction, glm::vec3 right);

  void update(const glm::mat4 &rotation);

  const glm::vec3 &getCurrentUp() const;
  const glm::vec3 &getCurrentDirection() const;
  const glm::vec3 &getCurrentRight() const;

private:
  glm::vec3 _initial_up, _initial_direction, _initial_right,
      _current_up, _current_direction, _current_right;
};

#endif // AXIS_H
