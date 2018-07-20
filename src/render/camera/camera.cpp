#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float fov, float near, float far):
  _roll(0), _pitch(0), _yaw(0),
  _fov(fov), _near(near), _far(far),
  _position(glm::vec3(0.0f)),
  _moveBuffer(glm::vec3(0.0f)),
  _rotateBuffer(glm::vec3(0.0f))
{
  this->updateViewMatrix();
}

void Camera::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->setUniformView(programId, proxy);
  this->setUniformProjection(programId, proxy);
}

void Camera::update(const float &delta)
{
  glm::vec3 velocity = this->_moveBuffer * delta;
  glm::vec3 rotateVelocity = this->_rotateBuffer * delta;

  this->_position += velocity;
  this->_yaw += rotateVelocity.x;
  this->_pitch += rotateVelocity.y;
  this->updateViewMatrix();

  this->_moveBuffer = glm::vec3(0.0f);
  this->_rotateBuffer = glm::vec3(0.0f);
}


void Camera::addToMovementBuffer(const glm::vec3 &delta)
{
  this->_moveBuffer += delta;
}

void Camera::addToRotationBuffer(const glm::vec3 &delta)
{
  this->_rotateBuffer += delta;
}

glm::mat4 &Camera::getViewMatrix()
{
  return this->_view;
}

glm::mat4 &Camera::updateViewMatrix()
{
  if(this->_pitch > 89.0f) {
    this->_pitch = 89.0f;
  }
  if(this->_pitch < -89.0f) {
    this->_pitch = -89.0f;
  }

  glm::mat4 roll(1.0f), pitch(1.0f), yaw(1.0f);
  roll = glm::rotate(roll, glm::radians(this->_roll), glm::vec3(0, 0, 1));
  pitch = glm::rotate(pitch, glm::radians(this->_pitch), glm::vec3(1, 0, 0));
  yaw = glm::rotate(yaw, glm::radians(this->_yaw), glm::vec3(0, 1, 0));

  glm::mat4 rotate = roll * pitch * yaw;
  glm::mat4 translate(1.0f);
  translate = glm::translate(translate, -this->_position);

  this->_view = translate * rotate;
  return this->_view;
}

glm::mat4 &Camera::getProjectionMatrix()
{
  return this->_projection;
}

glm::mat4 &Camera::updateProjectionMatrix(const int width, const int height)
{
  float aspectRatio = (float) width / height;
  this->_projection = glm::perspective(glm::radians(this->_fov), aspectRatio, this->_near, this->_far);
  return this->_projection;
}

float Camera::getFov()
{
  return this->_fov;
}

void Camera::setUniformProjection(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  int n_projection = proxy->glGetUniformLocation(programId, "projection");
  proxy->glUniformMatrix4fv(n_projection, 1, GL_FALSE, glm::value_ptr(this->_projection));
}

void Camera::setUniformView(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  int n_view = proxy->glGetUniformLocation(programId, "view");
  proxy->glUniformMatrix4fv(n_view, 1, GL_FALSE, glm::value_ptr(this->_view));
}
