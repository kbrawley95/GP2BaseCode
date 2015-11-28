#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Common.h"

GLuint	loadTextureFromFile(const string& filename);

GLuint	loadTextureFromFont(const string& fontFilename, int	pointSize, const string& text);

GLuint convertSDLSurfaceToTexture(SDL_Surface * surface);

GLuint LoadCubemapTexture(const string& posX, const string& negX, const string& posY, const string& negY, const string&posZ, const string& negZ);

void LoadCubeMapFace(const string& filename, GLenum face);

#endif