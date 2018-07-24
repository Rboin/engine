#include "camera.h"

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

Camera::Camera(const projection_information &p, const view_information &v)
{
  this->_fov = p.fov;
  this->_near = p.near;
  this->_far = p.far;
  this->_position = v.position;
  this->_position_buffer = glm::vec3(0.0f);
  this->_rotation = glm::vec3(0.0f);
  this->_rotation_buffer = glm::vec3(0.0f);
  this->_up = v.up;
  this->_direction = v.look;
}


void Camera::update(const float &delta)
{
  glm::vec3 position_velocity = this->_position_buffer * delta;

  this->_position += position_velocity;
  this->_rotation += this->_rotation_buffer;

  if (this->_rotation.y > 89.0f) {
    this->_rotation.y = 89.0f;
  }
  if(this->_rotation.y < -89.0f) {
    this->_rotation.y = -89.0f;
  }

  this->getCurrentDirection();

  this->_position_buffer = glm::vec3(0.0f);
  this->_rotation_buffer = glm::vec3(0.0f);
}

void Camera::move(CameraDirection direction)
{
  glm::vec3 forward = this->getCurrentDirection();
  glm::vec3 right = this->getCurrentAxis();
  switch (direction) {
  case CameraDirection::UP:
    this->_position_buffer += this->_up;
    break;
  case CameraDirection::DOWN:
    this->_position_buffer -= this->_up;
    break;
  case CameraDirection::FORWARD:
    this->_position_buffer += forward;
    break;
  case CameraDirection::BACKWARD:
    this->_position_buffer -= forward;
    break;
  case CameraDirection::LEFT:
    this->_position_buffer -= right;
    break;
  case CameraDirection::RIGHT:
    this->_position_buffer += right;
    break;
  }
}

void Camera::rotate(const glm::vec3 &delta)
{
  this->_rotation_buffer += delta;
}

void Camera::setPosition(const glm::vec3 p)
{
  this->_position = p;
}

glm::mat4 Camera::getOrientation() const
{
  glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(0.0f, 1.0f, 0.0f)),
            pitch = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));

  return pitch * yaw;
}

glm::mat4 &Camera::getViewMatrix()
{
  this->updateViewMatrix();
  return this->_view;
}

glm::mat4 &Camera::updateViewMatrix()
{
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), -this->_position),
            rotate = this->getOrientation();

  this->_view = rotate * translate;
  return this->_view;
}

glm::vec3 &Camera::getMovementVelocity()
{
  return this->_position_buffer;
}

glm::vec3 Camera::getCurrentDirection()
{

  glm::mat4 orientation = glm::inverse(this->getOrientation());

  // Put direction into tmp vec4, as you can only do mat4 * vec4
  glm::vec4 tmp = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
  tmp = orientation * tmp;
  return glm::vec3(tmp.x, tmp.y, tmp.z);
}

glm::vec3 Camera::getCurrentAxis()
{
  glm::vec3 currentDirection = this->getCurrentDirection();
  return glm::cross(currentDirection, this->_up);
}

glm::mat4 &Camera::getProjectionMatrix()
{
  return this->_projection;
}

glm::mat4 &Camera::updateProjectionMatrix(const int width, const int height)
{
  float aspectRatio = (float) width / height;
  this->_projection = glm::perspective(glm::radians(this->_fov),
                                       aspectRatio,
                                       this->_near,
                                       this->_far);
  return this->_projection;
}
