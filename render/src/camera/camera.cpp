#include "camera.h"

Camera::Camera(const projection_information &p, glm::vec3 position) {
  this->_movement = 0;
  this->_fov = p.fov;
  this->_near = p.near;
  this->_far = p.far;
  this->_position = position;
  this->_position_buffer = glm::vec3(0.0f);
  this->_rotation = glm::vec3(0.0f);
  this->_rotation_buffer = glm::vec3(0.0f);
  this->_axis = std::make_shared<Axis>();
}

void Camera::move(Direction direction) { this->_movement |= direction; }

void Camera::undoMove(Direction direction) { this->_movement ^= direction; }

void Camera::rotate(const glm::vec3 delta) { this->_rotation_buffer += delta; }

const glm::vec3 &Camera::getRotationVector() const { return this->_rotation; }

void Camera::addPosition(const glm::vec3 dp) { this->_position_buffer += dp; }

void Camera::setPosition(glm::vec3 p) { this->_position = p; }

const glm::vec3 &Camera::getPosition() const { return this->_position; }

void Camera::setRotation(glm::vec3 r) { this->_rotation = r; }

const glm::mat4 &Camera::getViewMatrix() {
  this->updateViewMatrix();
  return this->_view;
}

glm::mat4 &Camera::getProjectionMatrix() { return this->_projection; }

std::shared_ptr<Axis> &Camera::getAxis() { return this->_axis; }

void Camera::updatePositionBuffer() {
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
