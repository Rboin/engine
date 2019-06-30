#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "axis.h"
#include "openglfunctionproxy.h"

enum Direction {
  UP = 1,
  DOWN = 2,
  FORWARD = 4,
  BACKWARD = 8,
  RIGHT = 16,
  LEFT = 32
};

struct projection_information {
  float fov, near, far;
};

struct view_information {
  glm::vec3 position, up, look, right;
};

class Camera
{
public:
  Camera(const projection_information &p, glm::vec3 position);

  /**
   * Adds the given movement direction to the movement buffer. Can be undone using the Camera::undoMove(Direction) method.
   * @brief move
   * @param direction
   */
  void move(Direction direction);

  /**
   * Undoes the move done by Camera::move(Direction).
   * @brief undoMove
   * @param direction
   */
  void undoMove(Direction direction);

  /**
   * Add a vector of rotations (in degrees) to the rotation buffer.
   * @brief rotate
   * @param delta
   */
  void rotate(const glm::vec3 delta);

  const glm::vec3 &getRotationVector() const;

  /**
   * Adds the given vector to the position buffer.
   * @brief addPosition
   * @param dp
   */
  void addPosition(const glm::vec3 dp);

  void setPosition(glm::vec3 p);

  glm::vec3 getPosition();

  void setRotation(glm::vec3 r);

  glm::mat4 &getViewMatrix();

  glm::mat4 &getProjectionMatrix();

  std::shared_ptr<Axis> &getAxis();

  virtual void update(const double delta) = 0;
  virtual glm::mat4 getRotation() const = 0;
  virtual void updateViewMatrix() = 0;
  virtual void updateProjectionMatrix(const int width, const int height) = 0;

protected:
  int _movement;
  float _fov, _near, _far;
  glm::vec3 _position, _position_buffer,
      _rotation, _rotation_buffer;
  glm::mat4 _view, _projection;
  std::shared_ptr<Axis> _axis;

  /**
   * Gets the current forward and right directions and adds these
   * vectors to the position buffer based on whether a certain
   * key has been pressed.
   * @brief updatePositionBuffer
   */
  void updatePositionBuffer();
};

#endif // CAMERA_HPP
