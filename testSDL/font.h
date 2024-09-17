#ifndef font_h_
#define font_h_
#include "SDL_ttf.h"
#include "iostream"
#include "constant.h"
#include "string"
#include "times.h"

struct SCORE1
{
	static const int POSX;
	static const int POSY;
	static const int NUMPOSX;
	static const int NUMPOSY;
};

struct SCORE2
{
	static const int POSX;
	static const int POSY;
	static const int NUMPOSX;
	static const int NUMPOSY;
};

struct PLAYER1
{
	static const int NEXTPOSX;
	static const int NEXTPOSY;

	static const int HOLDPOSX;
	static const int HOLDPOSY;

	static const int NAMEPOSX;
	static const int NAMEPOSY;
};

struct PLAYER2
{
	static const int NEXTPOSX;
	static const int NEXTPOSY;

	static const int HOLDPOSX;
	static const int HOLDPOSY;

	static const int NAMEPOSX;
	static const int NAMEPOSY;
};

struct TIMELEFT
{
	static const int POSX;
	static const int POSY;
};

class Text
{
private:
public:
	Text(Vector pos_, const std::string& str_, SDL_Color color_);
	Vector pos;
	std::string str;
	SDL_Color color;
};

class Times_Font
{
private:
	SDL_Surface* surface;
	TTF_Font* font;
	SDL_Texture* texture;
	Times* times;

	const int timersize = 35;
	Vector pos = {FieldPos::X - 100, 0};
	const int scoresize = 30;
	const int bigscoresize = 40;

	void timer(SDL_Renderer* Renderer);
	void score(SDL_Renderer* Renderer, Scores& scores);
public:
	Times_Font(SDL_Surface* mSurface, TTF_Font* mFont, SDL_Texture* mTexturer, Times* ptimes);
	void draw(SDL_Renderer* Renderer, Scores& score);
	void draw_(SDL_Renderer* Renderer, int a);
	~Times_Font();
};

class GameFont
{
private:	
	const int size = 30;
	SDL_Texture* mTexture[11];
	Text text[11];
	TTF_Font* font;
public:
	GameFont();
	void init(SDL_Renderer* Renderer, SDL_Surface* Surface);
	void draw(SDL_Renderer* Renderer);
	~GameFont();
};

#endif

