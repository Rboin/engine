#include "fpscamera.h"

FPSCamera::FPSCamera(const projection_information &p, glm::vec3 position) :
  Camera(p, position)
{

}

void FPSCamera::update(const float &delta)
{
  // TODO: Rewrite camera to contain an entity to follow, set entity's position to camera position, same for rotation. (keep camera seperate)
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

  this->_axis->update(glm::inverse(this->getRotation()));

  this->_position_buffer = glm::vec3(0.0f);
  this->_rotation_buffer = glm::vec3(0.0f);
}

glm::mat4 FPSCamera::getRotation() const
{
  glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.x), glm::vec3(0.0f, 1.0f, 0.0f)),
            pitch = glm::rotate(glm::mat4(1.0f), glm::radians(this->_rotation.y), glm::vec3(1.0f, 0.0f, 0.0f));

  return pitch * yaw;
}

void FPSCamera::updateViewMatrix()
{
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), -this->_position),
            rotate = this->getRotation();

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
