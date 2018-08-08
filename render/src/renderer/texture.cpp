#include "texture.h"

Texture::Texture()
{
}

void Texture::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  this->initializeTexture(this->_texture, proxy, programId, 0, "material.diffuse");
}

void Texture::setTexture(TextureImage *texture)
{
  this->_texture = std::unique_ptr<TextureImage>(texture);
}

int Texture::getUniformDiffuse()
{
  return this->u_diffuse;
}

std::unique_ptr<TextureImage> &Texture::getTextureData()
{
  return this->_texture;
}

void Texture::initializeTexture(std::unique_ptr<TextureImage> &textureData,
                                std::shared_ptr<OpenGLFunctionProxy> &proxy,
                                GLuint programId,
                                int index,
                                std::string name)
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
  this->u_diffuse = proxy->glGetUniformLocation(programId, samplerName);
  proxy->glUniform1i(this->u_diffuse, index);
}
