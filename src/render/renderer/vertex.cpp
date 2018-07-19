#include "vertex.h"
#include "vertexlocation.h"

Vertex::Vertex(VertexData *data) :
  _initialized(false)
{
  this->_data = std::unique_ptr<VertexData>(data);
}

void Vertex::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  proxy->glGenBuffers(1, &this->_vbo);
  proxy->glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
  proxy->glBufferData(GL_ARRAY_BUFFER,
                      (this->_data->vertexSize + this->_data->colorSize + this->_data->textureSize) * sizeof(glm::vec3),
                      this->_data->vertices.data(),
                      GL_STATIC_DRAW);

  // Binding indices
  proxy->glGenBuffers(1, &this->_ebo);
  proxy->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
  proxy->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      this->_data->indiceSize * sizeof(unsigned int),
                      this->_data->indices.data(),
                      GL_STATIC_DRAW);

  // Bind shader variables
  GLint vecSize = this->_data->vertices[0].length();
  GLuint position = static_cast<GLuint>(proxy->glGetAttribLocation(programId, "position"));
  proxy->glEnableVertexAttribArray(position);
  proxy->glVertexAttribPointer(position,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) 0);
  GLuint color = static_cast<GLuint>(proxy->glGetAttribLocation(programId, "inColor"));
  proxy->glEnableVertexAttribArray(color);
  proxy->glVertexAttribPointer(color,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) (this->_data->vertexSize * sizeof(glm::vec3)));

  GLuint textureCoordinates = static_cast<GLuint>(proxy->glGetAttribLocation(programId, "textureCoordinate"));
  proxy->glEnableVertexAttribArray(textureCoordinates);
  proxy->glVertexAttribPointer(textureCoordinates,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) ((this->_data->vertexSize + this->_data->colorSize) * sizeof(glm::vec3)));

  this->_initialized = true;
}

void Vertex::deleteBuffers(std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  proxy->glDeleteBuffers(1, &_vbo);
}

bool Vertex::isInitialized()
{
  return this->_initialized;
}

const unsigned int &Vertex::getVbo() const
{
  return this->_vbo;
}

void Vertex::setVbo(unsigned int v)
{
  this->_vbo = v;
}

const std::vector<glm::vec3> &Vertex::getVertices() const
{
  return this->_data->vertices;
}

unsigned long Vertex::getVerticesSize() const
{
  return this->_data->vertexSize;
}

unsigned long Vertex::getIndiceSize() const
{
  return this->_data->indiceSize;
}
