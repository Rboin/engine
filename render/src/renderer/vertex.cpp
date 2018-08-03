#include "vertex.h"
#include "shaderattribute.h"

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
                      this->_data->vertices.size() * sizeof(glm::vec3),
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
  int position = VertexAttribute::POSITION;
  proxy->glVertexAttribPointer(position,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) 0);
  proxy->glEnableVertexAttribArray(position);

  int color = proxy->glGetAttribLocation(programId, "inColor");
  proxy->glVertexAttribPointer(color,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) (this->_data->vertexSize * sizeof(glm::vec3)));
  proxy->glEnableVertexAttribArray(color);

  int textureCoordinates = VertexAttribute::TEXTURE_COORDINATE;
  proxy->glVertexAttribPointer(textureCoordinates,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) ((this->_data->vertexSize + this->_data->colorSize) * sizeof(glm::vec3)));
  proxy->glEnableVertexAttribArray(textureCoordinates);

  int normalLocation = VertexAttribute::NORMAL,
      normalIndex = this->_data->vertexSize + this->_data->colorSize + this->_data->textureSize;
  proxy->glVertexAttribPointer(normalLocation,
                               vecSize,
                               GL_FLOAT,
                               GL_FALSE,
                               sizeof(glm::vec3),
                               (void *) (normalIndex * sizeof(glm::vec3)));
  proxy->glEnableVertexAttribArray(normalLocation);

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
