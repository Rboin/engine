#ifndef VERTEX_H
#define VERTEX_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "openglfunctionproxy.h"

struct VertexData {
  unsigned int vertexSize, indiceSize, colorSize, textureSize, normalSize;

  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
};

class Vertex
{
public:
  Vertex(VertexData *data);
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void deleteBuffers(std::shared_ptr<OpenGLFunctionProxy> &proxy);
  bool isInitialized();
  const unsigned int &getVbo() const;
  void setVbo(unsigned int v);
  const std::vector<glm::vec3> &getVertices() const;
  unsigned long getVerticesSize() const;
  unsigned long getIndiceSize() const;
private:
  bool _initialized;
  unsigned int _vbo, _ebo;
  std::unique_ptr<VertexData> _data;
};
#endif // VERTEX_H
