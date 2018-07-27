#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "axis.h"
#include "renderer/openglfunctionproxy.h"

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
  Camera(const projection_information &p, const view_information &v)
  {
    this->_movement = 0;
    this->_fov = p.fov;
    this->_near = p.near;
    this->_far = p.far;
    this->_position = v.position;
    this->_position_buffer = glm::vec3(0.0f);
    this->_rotation = glm::vec3(0.0f);
    this->_rotation_buffer = glm::vec3(0.0f);
    this->_axis = std::make_unique<Axis>(v.up, v.look, v.right);
  }

  /**
   * Adds the given movement direction to the movement buffer. Can be undone using the Camera::undoMove(Direction) method.
   * @brief move
   * @param direction
   */
  void move(Direction direction)
  {
    this->_movement |= direction;
  }

  /**
   * Undoes the move done by Camera::move(Direction).
   * @brief undoMove
   * @param direction
   */
  void undoMove(Direction direction)
  {
    this->_movement ^= direction;
  }

  /**
   * Add a vector of rotations (in degrees) to the rotation buffer.
   * @brief rotate
   * @param delta
   */
  void rotate(const glm::vec3 &delta)
  {
    this->_rotation_buffer += delta;
  }

  const glm::vec3 &getRotationVector() const
  {
    return this->_rotation;
  }

  /**
   * Adds the given vector to the position buffer.
   * @brief addPosition
   * @param dp
   */
  void addPosition(const glm::vec3 dp)
  {
    this->_position_buffer += dp;
  }

  /**
   * Sets the current position of the camera.
   * @brief setPosition
   * @param p A vector (XYZ) containing the position.
   */
  void setPosition(glm::vec3 p)
  {
    this->_position = p;
  }

  glm::vec3 getPosition()
  {
    return this->_position;
  }

  glm::mat4 &getViewMatrix()
  {
    this->updateViewMatrix();
    return this->_view;
  }

  glm::mat4 &getProjectionMatrix()
  {
    return this->_projection;
  }

  virtual void update(const float &delta) = 0;
  virtual glm::mat4 getRotation() const = 0;
  virtual void updateViewMatrix() = 0;
  virtual void updateProjectionMatrix(const int width, const int height) = 0;

protected:
  int _movement;
  float _fov, _near, _far;
  glm::vec3 _position, _position_buffer,
      _rotation, _rotation_buffer;
  glm::mat4 _view, _projection;
  std::unique_ptr<Axis> _axis;

  /**
   * Gets the current forward and right directions and adds these
   * vectors to the position buffer based on whether a certain
   * key has been pressed.
   * @brief updatePositionBuffer
   */
  void updatePositionBuffer()
  {
    if (this->_movement) {
      glm::vec3 up = this->_axis->getCurrentUp();
      glm::vec3 forward = this->_axis->getCurrentDirection();
      glm::vec3 right = this->_axis->getCurrentRight();
      if (this->_movement & Direction::UP) {
        this->addPosition(up);
      }
      if (this->_movement & Direction::DOWN) {
        this->addPosition(-up);
      }
      if (this->_movement & Direction::FORWARD) {
        this->addPosition(forward);
      }
      if (this->_movement & Direction::BACKWARD) {
        this->addPosition(-forward);
      }
      if (this->_movement & Direction::LEFT) {
        this->addPosition(-right);
      }
      if (this->_movement & Direction::RIGHT) {
        this->addPosition(right);
      }
    }
  }
};

#endif // CAMERA_HPP
