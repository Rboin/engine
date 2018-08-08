#include "texture.h"

Texture::Texture()
{
}

void Texture::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->initializeTexture(this->_diffuseTexture, proxy, programId, 0, "material.diffuse", this->u_diffuse);
  this->initializeTexture(this->_specularTexture, proxy, programId, 1, "material.specular", this->u_specular);
  this->initializeTexture(this->_emissionTexture, proxy, programId, 2, "material.emission", this->u_emission);
}

void Texture::setDiffuseTexture(TextureImage *texture)
{
  this->_diffuseTexture = std::unique_ptr<TextureImage>(texture);
}

void Texture::setSpecularTexture(TextureImage *texture)
{
  this->_specularTexture = std::unique_ptr<TextureImage>(texture);
}

void Texture::setEmissionTexture(TextureImage *texture)
{
  this->_emissionTexture = std::unique_ptr<TextureImage>(texture);
}

int Texture::getUniformDiffuse()
{
  return this->u_diffuse;
}

int Texture::getUniformSpecular()
{
  return this->u_specular;
}

int Texture::getUniformEmission()
{
  return this->u_emission;
}

std::unique_ptr<TextureImage> &Texture::getDiffuseTexture()
{
  return this->_diffuseTexture;
}

std::unique_ptr<TextureImage> &Texture::getSpecularTexture()
{
  return this->_specularTexture;
}

std::unique_ptr<TextureImage> &Texture::getEmissionTexture()
{
  return this->_emissionTexture;
}

void Texture::initializeTexture(std::unique_ptr<TextureImage> &textureData,
                                std::shared_ptr<OpenGLFunctionProxy> &proxy,
                                GLuint programId,
                                int index,
                                std::string name, int &uniform)
{
  // Generate texture ID.
  proxy->glGenTextures(1, &textureData->texture);
  proxy->glBindTexture(GL_TEXTURE_2D, textureData->texture);

  proxy->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  proxy->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  proxy->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  proxy->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  int width = textureData->width, height = textureData->height;
  unsigned char *data = textureData->imageData.data();
  GLint internalFormat = textureData->internalFormat;
  GLenum imageFormat = textureData->imageFormat;

  proxy->glTexImage2D(GL_TEXTURE_2D,
                      0,
                      internalFormat,
                      width,
                      height,
                      0,
                      imageFormat,
                      GL_UNSIGNED_BYTE,
                      data);

  proxy->glGenerateMipMap(GL_TEXTURE_2D);

  const char *samplerName = name.c_str();
  uniform = proxy->glGetUniformLocation(programId, samplerName);
  proxy->glUniform1i(this->u_diffuse, index);
}
