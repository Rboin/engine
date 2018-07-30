#include "texture.h"
#include "shaderattribute.h"

Texture::Texture()
{
  this->_textures = std::vector<std::unique_ptr<TextureImage>>();
}

void Texture::initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy)
{
  int i = 0;
  std::string name = "texture";
  std::vector<std::unique_ptr<TextureImage>>::iterator it;
  for (it = this->_textures.begin(); it != this->_textures.end(); ++it) {
    std::unique_ptr<TextureImage> &currentTexture = (*it);
    this->initializeTexture(currentTexture, proxy, programId, i, name + std::to_string(i+1));
    i++;
  }
}

void Texture::addTexture(TextureImage *texture)
{
  this->_textures.push_back(std::unique_ptr<TextureImage>(texture));
}

std::vector<std::unique_ptr<TextureImage> > &Texture::getTextures()
{
  return this->_textures;
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
  GLint samplerLocation = FragmentAttribute::UNIFORM_TEXTURE1 + index;
  proxy->glUniform1i(samplerLocation, index);
}
