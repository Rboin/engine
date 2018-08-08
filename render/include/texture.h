#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "openglfunctionproxy.h"

struct TextureImage {
  GLuint texture;
  int width, height;
  std::vector<unsigned char> imageData;
  GLint internalFormat;
  GLenum imageFormat;
};

class Texture
{
public:
  Texture();
  void initialize(GLuint programId, std::shared_ptr<OpenGLFunctionProxy> &proxy);
  void setTexture(TextureImage *texture);
  int getUniformDiffuse();
  std::unique_ptr<TextureImage> &getTextureData();
private:
  int u_diffuse;
  std::unique_ptr<TextureImage> _texture;

  void initializeTexture(std::unique_ptr<TextureImage> &textureData,
                         std::shared_ptr<OpenGLFunctionProxy> &proxy,
                         GLuint programId,
                         int index, std::string name);
};

#endif // TEXTURE_H
