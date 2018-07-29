#include "shaderinformation.h"

ShaderInformation::ShaderInformation(std::string vertexSource, std::string fragmentSource)
{
  this->vertexSource = vertexSource;
  this->fragmentSource = fragmentSource;
}

void ShaderInformation::setPositionAttribute(GLuint attr)
{
  this->positionAttribute = attr;
}

void ShaderInformation::setColorAttribute(GLuint attr)
{
  this->colorAttribute = attr;
}

void ShaderInformation::setMatrixUniform(GLuint m)
{
  this->matrixUniform = m;
}

GLuint ShaderInformation::getPositionAttribute()
{
  return this->positionAttribute;
}

GLuint ShaderInformation::getColorAttribute()
{
  return this->colorAttribute;
}

GLuint ShaderInformation::getMatrixUniform()
{
  return this->matrixUniform;
}

std::string ShaderInformation::getVertexSource()
{
  return this->vertexSource;
}

std::string ShaderInformation::getFragmentSource()
{
  return this->fragmentSource;
}
