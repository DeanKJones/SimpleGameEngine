#pragma once
#include <string>
#include "RendererSDL.h"
#include "RendererOGL.h"

using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadSDL(RendererSDL& rendererP, const string& filenameP);
	bool loadOGL(RendererOGL& rendererP, const string& filenameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }
	void setActive() const;

private:
	unsigned int textureID;
	string filename;
	SDL_Texture* SDLTexture;
	int width;
	int height;
};

