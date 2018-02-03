#pragma once
#include <string>
#include <gl/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class Texture
{
public:
	Texture();
	~Texture();

	GLuint getTextureID();
	GLuint loadDDS(const char * imagepath);
	void loadTexture(std::string filePath);

protected:
	

	GLuint textureID;
	SDL_Surface *Surface;
};