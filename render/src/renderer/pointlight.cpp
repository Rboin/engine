#include "pointlight.h"

#include <glm/gtc/type_ptr.hpp>

RenderObjects::PointLight::PointLight(Mesh *m) : Light(m),
  u_position(-1),
  u_constant(-1),
  u_linear(-1),
  u_quadratic(-1)
{

}

void RenderObjects::PointLight::setIndex(int i)
{
  this->_index = i;
}

void RenderObjects::PointLight::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  std::string base = "light[" + std::to_string(this->_index) + "].";
  if (this->u_position < 0) {
    this->u_position = proxy->glGetUniformLocation(programId, (base + "position").c_str());
  }
  if (this->u_ambient < 0) {
    this->u_ambient = proxy->glGetUniformLocation(programId, (base + "ambient").c_str());
  }
  if (this->u_diffuse < 0) {
    this->u_diffuse = proxy->glGetUniformLocation(programId, (base + "diffuse").c_str());
  }
  if (this->u_specular < 0) {
    this->u_specular = proxy->glGetUniformLocation(programId, (base + "specular").c_str());
  }
  if (this->u_constant < 0) {
    this->u_constant = proxy->glGetUniformLocation(programId, (base + "constant").c_str());
  }
  if (this->u_linear < 0) {
    this->u_linear = proxy->glGetUniformLocation(programId, (base + "linear").c_str());
  }
  if (this->u_quadratic < 0) {
    this->u_quadratic = proxy->glGetUniformLocation(programId, (base + "quadratic").c_str());
  }
  BaseRenderObject::initialize(programId, proxy);
}

void RenderObjects::PointLight::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &modelMatrix, const glm::mat4 &viewProjectionMatrix)
{
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  this->setTextures(proxy);

  this->updateMatrices(modelMatrix, viewProjectionMatrix);

  // Get the position (4th column)
  glm::vec3 position(modelMatrix[3]);
  this->_currentPosition = position;
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void RenderObjects::PointLight::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set Light uniform position
  proxy->glUniform3fv(this->u_position, 1, glm::value_ptr(this->_currentPosition));
  // Set Light uniform color
  proxy->glUniform3fv(this->u_ambient, 1, glm::value_ptr(this->_mesh->getMaterial()->getAmbientColor()));
  proxy->glUniform3fv(this->u_diffuse, 1, glm::value_ptr(this->_mesh->getMaterial()->getDiffuseColor()));
  proxy->glUniform3fv(this->u_specular, 1, glm::value_ptr(this->_mesh->getMaterial()->getSpecularColor()));
  proxy->glUniform1f(this->u_constant, 1.0f);
  proxy->glUniform1f(this->u_linear, 0.09f);
  proxy->glUniform1f(this->u_quadratic, 0.032f);
  BaseRenderObject::setUniforms(program, proxy);
}
