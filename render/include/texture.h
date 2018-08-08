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
  void setDiffuseTexture(TextureImage *texture);
  void setSpecularTexture(TextureImage *texture);
  void setEmissionTexture(TextureImage *texture);
  int getUniformDiffuse();
  int getUniformSpecular();
  int getUniformEmission();
  std::unique_ptr<TextureImage> &getDiffuseTexture();
  std::unique_ptr<TextureImage> &getSpecularTexture();
  std::unique_ptr<TextureImage> &getEmissionTexture();
private:
  int u_diffuse, u_specular, u_emission;
  std::unique_ptr<TextureImage> _diffuseTexture;
  std::unique_ptr<TextureImage> _specularTexture;
  std::unique_ptr<TextureImage> _emissionTexture;

  void initializeTexture(std::unique_ptr<TextureImage> &textureData,
                         std::shared_ptr<OpenGLFunctionProxy> &proxy,
                         GLuint programId,
                         int index, std::string name, int &uniform);
};

#endif // TEXTURE_H
