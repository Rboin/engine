#include "lightrenderobject.h"

#include <glm/gtc/type_ptr.hpp>

#include <transformcomponent.h>

LightRenderObject::LightRenderObject(Mesh *m) : RenderObject(m),
  _isPointLight(true),
  u_position(-1),
  u_ambient(-1),
  u_diffuse(-1),
  u_specular(-1),
  u_constant(-1),
  u_linear(-1),
  u_quadratic(-1)
{

}

void LightRenderObject::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  if (this->u_position < 0) {
    this->u_position = proxy->glGetUniformLocation(programId, "light.position");
  }
  if (this->u_ambient < 0) {
    this->u_ambient = proxy->glGetUniformLocation(programId, "light.ambient");
  }
  if (this->u_diffuse < 0) {
    this->u_diffuse = proxy->glGetUniformLocation(programId, "light.diffuse");
  }
  if (this->u_specular < 0) {
    this->u_specular = proxy->glGetUniformLocation(programId, "light.specular");
  }
  if (this->u_constant < 0) {
    this->u_constant = proxy->glGetUniformLocation(programId, "light.constant");
  }
  if (this->u_linear < 0) {
    this->u_linear = proxy->glGetUniformLocation(programId, "light.linear");
  }
  if (this->u_quadratic < 0) {
    this->u_quadratic = proxy->glGetUniformLocation(programId, "light.quadratic");
  }
  RenderObject::initialize(programId, proxy);
}

void LightRenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, const glm::mat4 &modelMatrix, const glm::mat4 &viewProjectionMatrix)
{
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);
  this->setTextures(proxy);

  this->updateMatrices(modelMatrix, viewProjectionMatrix);

  float w = 0.0f;
  if (this->_isPointLight) {
    w = 1.0f;
  }
  // Get the position (4th column)
  glm::vec3 position(modelMatrix[3]);
  this->_currentPosition = glm::vec4(position, w);
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void LightRenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set Light uniform position
  proxy->glUniform4fv(this->u_position, 1, glm::value_ptr(this->_currentPosition));
  // Set Light uniform color
  proxy->glUniform3fv(this->u_ambient, 1, glm::value_ptr(this->_mesh->getMaterial()->getAmbientColor()));
  proxy->glUniform3fv(this->u_diffuse, 1, glm::value_ptr(this->_mesh->getMaterial()->getDiffuseColor()));
  proxy->glUniform3fv(this->u_specular, 1, glm::value_ptr(this->_mesh->getMaterial()->getSpecularColor()));
  proxy->glUniform1f(this->u_constant, 1.0f);
  proxy->glUniform1f(this->u_linear, 0.09f);
  proxy->glUniform1f(this->u_quadratic, 0.032f);
  RenderObject::setUniforms(program, proxy);
}

void LightRenderObject::setIsPointLight(bool p)
{
  this->_isPointLight = p;
}
