#ifndef SHADERINFORMATION_H
#define SHADERINFORMATION_H

#include <string>
#include <memory>
#include "GL/gl.h"


class ShaderInformation
{
public:
  ShaderInformation(std::string vertexSource, std::string fragmentSource);
  void setPositionAttribute(GLuint attr);
  void setColorAttribute(GLuint attr);
  void setMatrixUniform(GLuint m);

  GLuint getPositionAttribute();
  GLuint getColorAttribute();
  GLuint getMatrixUniform();

  std::string getVertexSource();
  std::string getFragmentSource();
private:
  GLuint positionAttribute, colorAttribute, matrixUniform;
  std::string vertexSource, fragmentSource;
};
#endif // SHADERINFORMATION_H
