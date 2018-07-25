#include "fpscamera.h"

FPSCamera::FPSCamera(const projection_information &p, const view_information &v) :
  Camera(p, v)
{

}

void FPSCamera::update(const float &delta)
{
  this->updatePositionBuffer();
  glm::vec3 position_velocity = this->_position_buffer * delta;

  this->_position += position_velocity;
  this->_rotation += this->_rotation_buffer;

  // Limit pitch.
  if (this->_rotation.y > 89.0f) {
    this->_rotation.y = 89.0f;
  }
  if(this->_rotation.y < -89.0f) {
    this->_rotation.y = -89.0f;
  }

  this->_position_buffer = glm::vec3(0.0f);
  this->_rotation_buffer = glm::vec3(0.0f);
}

glm::mat4 FPSCamera::getOrientation() const
{
  glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(0.0f, 1.0f, 0.0f)),
            pitch = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));

  return pitch * yaw;
}

glm::vec3 FPSCamera::getCurrentDirection()
{
  glm::mat4 orientation = glm::inverse(this->getOrientation());

  // Put direction into tmp vec4, as you can only do mat4 * vec4
  glm::vec4 tmp = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
  tmp = orientation * tmp;
  return glm::vec3(tmp.x, tmp.y, tmp.z);
}

glm::vec3 FPSCamera::getCurrentAxis()
{
  glm::vec3 currentDirection = this->getCurrentDirection();
  return glm::cross(currentDirection, this->_up);
}

void FPSCamera::updateViewMatrix()
{
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), -this->_position),
            rotate = this->getOrientation();

  this->_view = rotate * translate;
}

void FPSCamera::updateProjectionMatrix(const int width, const int height)
{
  float aspectRatio = (float) width / height;
  this->_projection = glm::perspective(glm::radians(this->_fov),
                                       aspectRatio,
                                       this->_near,
                                       this->_far);
}
