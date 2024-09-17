#pragma once
#include "SDL_image.h"
#include "constant.h"

class Image
{
private:
	SDL_Surface* image;
	SDL_Texture* image_texture;
	int flags = IMG_INIT_PNG;
public:
	Image(SDL_Surface* mImage, SDL_Texture* mImTexturer);
	void back(SDL_Renderer* Renderer, int alfa);
	void backInit(SDL_Renderer* Renderer);
};
