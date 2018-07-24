#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/openglfunctionproxy.h"

enum CameraDirection {
  UP, DOWN, FORWARD, BACKWARD, RIGHT, LEFT
};

struct projection_information {
  float fov, near, far;
};

struct view_information {
  glm::vec3 position, up, look;
};

class Camera
{
public:
  Camera(const projection_information &p, const view_information &v);
  void update(const float &delta);
  void move(CameraDirection direction);
  void rotate(const glm::vec3 &delta);
  void setPosition(const glm::vec3 p);

  glm::mat4 getOrientation() const;
  glm::mat4 &getViewMatrix();
  glm::mat4 &updateViewMatrix();
  glm::vec3 &getMovementVelocity();
  glm::mat4 &getProjectionMatrix();
  glm::mat4 &updateProjectionMatrix(const int width, const int height);

private:
  GLuint u_view, u_projection;
  float _fov, _near, _far;
  glm::vec3 _position, _position_buffer,
      _rotation, _rotation_buffer,
      _up, _axis, _direction;
  glm::mat4 _view, _projection;

  glm::vec3 getCurrentDirection();
  glm::vec3 getCurrentAxis();
};

#endif // CAMERA_H
