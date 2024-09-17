#include "opening.h"

Opening::Opening()
	:font(nullptr)
	,mTexture{ nullptr }
{
}

Opening::~Opening()
{
	TTF_CloseFont(font);
	for (int i = 0; i < 5; i++) {
		SDL_DestroyTexture(mTexture[i]);
	}
}

void Opening::reset()
{
	selected = false;
	select = 0;
}

void Opening::init(SDL_Renderer* Renderer, SDL_Surface* Surface)
{
	font = TTF_OpenFont("font.ttf", size);
	Surface = TTF_RenderUTF8_Blended(font, "CASE 1", { 255,255,255,255 });
	mTexture[0] = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = TTF_RenderUTF8_Blended(font, "CASE 2", { 255,255,255,255 });
	mTexture[1] = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = TTF_RenderUTF8_Blended(font, "CASE 3", { 255,255,255,255 });
	mTexture[2] = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = TTF_RenderUTF8_Blended(font, "CASE 4", { 255,255,255,255 });
	mTexture[3] = SDL_CreateTextureFromSurface(Renderer, Surface);
}

bool Opening::input(const InputState& state)
{
	if (selected) return false;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_UP) == EPressed) select += 3;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EPressed) select += 1;
	select = select % 4;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == EPressed) selected = true;
	return true;
}

GAMESTATE Opening::draw(SDL_Renderer* Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_RenderClear(Renderer);
	for (int i = 0; i < 5; i++) {
		int dx = 0;
		if (i == select) dx = -30;
		int iw, ih;
		SDL_QueryTexture(mTexture[i], NULL, NULL, &iw, &ih);
		SDL_Rect txtRect = { 0,0,iw,ih };
		SDL_Rect pasteRect = { origin.x + dx, origin.y + size * 2 * i,iw,ih };
		SDL_RenderCopy(Renderer, mTexture[i], &txtRect, &pasteRect);
	}

	SDL_RenderPresent(Renderer);
	if (selected) return GAMESTATE(select + 1);
	return OPENING;
}