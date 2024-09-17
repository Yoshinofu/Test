#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "constant.h"
#include "input.h"
 
class Opening {
private:
	Vector origin = { 200,100 };
	int statenum = 4;
	bool selected = false;
	int select = 0;
	const int size = 40;
	SDL_Texture* mTexture[5];
	TTF_Font* font;
public:
	Opening();
	void init(SDL_Renderer* Renderer, SDL_Surface* Surface);
	bool input(const InputState& state);
	GAMESTATE draw(SDL_Renderer* Renderer);
	void reset();
	~Opening();
};
