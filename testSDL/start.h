#pragma once
#include "font.h"
#include "image.h"
#include <string>
#include <map>
#include "input.h"


class Start 
{
private:
	int size = 300;
	TTF_Font* font;
	SDL_Texture* texture;
	Times* times;
	bool flag = false;
public:
	Start(Times* ptimes);
	~Start();
	void draw(SDL_Surface* surface, SDL_Renderer* renderer);
	bool isStart();
	void reset();
};

class Finish
{
private:
	int size = 130;
	int t;
	TTF_Font* font;
	std::map<int, Vector> text;
	SDL_Texture* texture[8];
	Times* times;
	Scores* scores;
	Image* image;
	GAMESTATE* gamestate;
	void subDraw(SDL_Renderer* renderer, int num);
	void drawInit(SDL_Surface* surface, SDL_Renderer* renderer);
	bool drawFinish(SDL_Renderer* renderer, int num);
public:
	Finish(Scores* pscores, Image* pimage, GAMESTATE* pgamestate);
	~Finish();
	void init(SDL_Renderer* renderer, SDL_Surface* surface);
	void draw(SDL_Surface* surface, SDL_Renderer* renderer, int num);
	bool input(const InputState& state);
};