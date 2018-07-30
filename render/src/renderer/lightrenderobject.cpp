#include "lightrenderobject.h"

#include <glm/gtc/type_ptr.hpp>
#include "shaderattribute.h"

LightRenderObject::LightRenderObject(Mesh *m) : RenderObject(m)
{

}

void LightRenderObject::render(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy, std::unique_ptr<Entity> &entity, const glm::mat4 &viewProjectionMatrix)
{
  GLuint vao = this->_mesh->getVao();
  this->bind(vao, proxy);

  this->_currentMVP = viewProjectionMatrix * entity->getModelMatrix();
  this->_currentPosition = entity->getPosition();
  this->setUniforms(programId, proxy);
  unsigned int verticesSize = this->_mesh->getVertex()->getVerticesSize();
  proxy->glDrawArrays(GL_TRIANGLES, 0, verticesSize);
  this->unbind(proxy);
}

void LightRenderObject::setUniforms(GLuint program, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  // Set Light uniform color
  glm::vec3 color = this->_mesh->getMaterial()->getAmbientColor();
  int lightLocation = FragmentAttribute::UNIFORM_LIGHT_COLOR;
  proxy->glUniform3fv(lightLocation, 1, glm::value_ptr(color));
  int lightPositionLocation = FragmentAttribute::UNIFORM_LIGHT_POSITION;
  proxy->glUniform3fv(lightPositionLocation, 1, glm::value_ptr(this->_currentPosition));
  RenderObject::setUniforms(program, proxy);
}
