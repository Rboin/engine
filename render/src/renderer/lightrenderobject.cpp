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

  this->updateMatrices(entity->getModelMatrix(), viewProjectionMatrix);
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
  proxy->glUniform3fv(FragmentAttribute::UNIFORM_LIGHT_COLOR, 1, glm::value_ptr(color));
  proxy->glUniform3fv(FragmentAttribute::UNIFORM_LIGHT_POSITION, 1, glm::value_ptr(this->_currentPosition));
  RenderObject::setUniforms(program, proxy);
}
