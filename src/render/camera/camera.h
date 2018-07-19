#ifndef CAMERA_H
#define CAMERA_H

#include <memory>
#include <glm/glm.hpp>

#include "renderer/openglfunctionproxy.h"

class Camera
{
public:
  Camera(float fov, float near, float far);
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void addToPosition(glm::vec3 delta);
  glm::mat4 &getViewMatrix();
  glm::mat4 &updateViewMatrix();
  glm::mat4 &getProjectionMatrix();
  glm::mat4 &updateProjectionMatrix(const int width, const int height);
  float getFov();

  void setUniformProjection(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void setUniformView(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
private:
  float _roll, _pitch, _yaw, _fov, _near, _far;
  glm::vec3 _position;
  glm::mat4 _view, _projection;
};

#endif // CAMERA_H
