#include "image.h"

Image::Image(SDL_Surface* mImage, SDL_Texture* mImTexturer)
	:image(mImage)
	,image_texture(mImTexturer)
{
}

void Image::backInit(SDL_Renderer* Renderer)
{
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) IMG_GetError();
    image = IMG_Load("brack.png");
    image_texture = SDL_CreateTextureFromSurface(Renderer, image);
}

void Image::back(SDL_Renderer* Renderer, int alfa)
{
    SDL_SetTextureAlphaMod(image_texture, alfa);
    int iw = WindowLength::WIDTH, ih = WindowLength::HEIGHT;
    SDL_QueryTexture(image_texture, NULL, NULL, &iw, &ih);
    SDL_Rect image_rect = { 0,0, iw,ih};
    SDL_Rect draw_rect = { 0, 0,  WindowLength::WIDTH, WindowLength::HEIGHT};
    SDL_RenderCopy(Renderer, image_texture, &image_rect, &draw_rect);
}