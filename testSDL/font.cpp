#include "font.h"
const int PLAYER1::NEXTPOSX = NextPos1::X;
const int PLAYER1::NEXTPOSY = NextPos1::Y;


const int PLAYER1::HOLDPOSX = HoldPos1::X;
const int PLAYER1::HOLDPOSY = HoldPos1::Y;
static const int POSX;
static const int POSY;

const int PLAYER1::NAMEPOSX = WindowLength::WIDTH / 6;
const int PLAYER1::NAMEPOSY = WindowLength::HEIGHT * 9 / 10;

const int PLAYER2::NEXTPOSX = NextPos2::X;
const int PLAYER2::NEXTPOSY = NextPos2::Y;

const int PLAYER2::HOLDPOSX = HoldPos2::X;
const int PLAYER2::HOLDPOSY = HoldPos2::Y;

const int PLAYER2::NAMEPOSX = WindowLength::WIDTH - PLAYER1::NAMEPOSX;
const int PLAYER2::NAMEPOSY = PLAYER1::NAMEPOSY;

const int SCORE1::POSX = PLAYER1::HOLDPOSX;
const int SCORE1::POSY = WindowLength::HEIGHT * 7 / 10;
const int SCORE1::NUMPOSX = POSX + 110;
const int SCORE1::NUMPOSY = POSY + 30;

const int SCORE2::POSX = PLAYER2::HOLDPOSX;
const int SCORE2::POSY = WindowLength::HEIGHT * 7 / 10;
const int SCORE2::NUMPOSX = POSX + 110;
const int SCORE2::NUMPOSY = POSY + 30;

const int TIMELEFT::POSX = FieldPos::X - 280;
const int TIMELEFT::POSY = 0;

Text::Text(Vector pos_, const std::string& str_, SDL_Color color_)
	:pos(pos_)
	,str(str_)
	,color(color_)
{
}

GameFont::GameFont()
	:font(nullptr)
	,mTexture{nullptr}
	, text{ {{ SCORE1::POSX, SCORE1::POSY }, "removed", { 255,255,255,255 }},
			{{SCORE2::POSX, SCORE2::POSY }, "removed", { 255,255,255,255 }},
			{{ SCORE1::POSX, SCORE1::POSY + 30 }, "blocks", { 255,255,255,255 }},
			{{ SCORE2::POSX, SCORE2::POSY + 30 }, "blocks", { 255,255,255,255 }},
			{{ PLAYER1::HOLDPOSX + size, PLAYER1::HOLDPOSY - size * 3 / 2 }, "HOLD", { 255,255,255,255 }},
			{{ PLAYER2::HOLDPOSX + size, PLAYER2::HOLDPOSY - size * 3 / 2 }, "HOLD", { 255,255,255,255 }},
			{{ PLAYER1::NEXTPOSX + size, PLAYER1::NEXTPOSY - size * 3 / 2 }, "NEXT", { 255,255,255,255 }},
			{{ PLAYER2::NEXTPOSX + size, PLAYER2::NEXTPOSY - size * 3 / 2 }, "NEXT", { 255,255,255,255 }},
			{{ PLAYER1::NAMEPOSX - size * 2, PLAYER1::NAMEPOSY }, "PLAYER1", { 200,100,100,255 }},
			{{ PLAYER2::NAMEPOSX - size * 2, PLAYER2::NAMEPOSY }, "PLAYER2", { 100,100,200,255 }},
			{{TIMELEFT::POSX, TIMELEFT::POSY}, "Time Left :", {255,255,255,255}}}
{
}

GameFont::~GameFont()
{
	TTF_CloseFont(font);
	for (int i = 0; i < 11; i++) {
		SDL_DestroyTexture(mTexture[i]);
	}
}

void GameFont::init(SDL_Renderer* Renderer, SDL_Surface* Surface)
{
	font = TTF_OpenFont("font.ttf", size);
	for (int i = 0; i < 11; i++) {
		Surface = TTF_RenderUTF8_Blended(font, text[i].str.c_str(), text[i].color);
		mTexture[i] = SDL_CreateTextureFromSurface(Renderer, Surface);
	}

}



void GameFont::draw(SDL_Renderer* Renderer)
{
	for (int i = 0; i < 11; i++) {
		int iw, ih;
		SDL_QueryTexture(mTexture[i], NULL, NULL, &iw, &ih);
		SDL_Rect txtRect = { 0,0,iw,ih };
		SDL_Rect pasteRect = { text[i].pos.x, text[i].pos.y,iw,ih};
		SDL_RenderCopy(Renderer, mTexture[i], &txtRect, &pasteRect);
	}
}



Times_Font::Times_Font(SDL_Surface* mSurface, TTF_Font* mFont, SDL_Texture* mTexture, Times* ptimes)
	: surface(mSurface)
	, font(mFont)
	, texture(mTexture)
	, times(ptimes)
{
}
void Times_Font::draw(SDL_Renderer* Renderer, Scores& scores)
{
	timer(Renderer);
	score(Renderer, scores);
}

void Times_Font::draw_(SDL_Renderer* Renderer, int a)
{
	std::string aaa = std::to_string(a);
	font = TTF_OpenFont("font.ttf", timersize);
	surface = TTF_RenderUTF8_Blended(font, aaa.c_str(), { 255,255,255,255 });
	texture = SDL_CreateTextureFromSurface(Renderer, surface);
	int iw, ih;
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { 50, 50 ,iw,ih };
	SDL_RenderCopy(Renderer, texture, &txtRect, &pasteRect);
}

void Times_Font::timer(SDL_Renderer* Renderer)
{
	std::string timer = std::to_string(int(times->getTimer()));

	font = TTF_OpenFont("font.ttf", timersize);
	surface = TTF_RenderUTF8_Blended(font, timer.c_str(), { 255,255,255,255 });
	texture = SDL_CreateTextureFromSurface(Renderer, surface);
	int iw, ih;
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { pos.x, pos.y ,iw,ih };
	SDL_RenderCopy(Renderer, texture, &txtRect, &pasteRect);
}

void Times_Font::score(SDL_Renderer* Renderer, Scores& scores)
{
	std::string score1 = std::to_string(scores.getRemBlocks(P1));
	std::string score2 = std::to_string(scores.getRemBlocks(P2));
	Vector pos = { 0,0 };
	if (!scores.isAdd(P1)) {
		font = TTF_OpenFont("font.ttf", scoresize);
		pos = { SCORE1::NUMPOSX, SCORE1::NUMPOSY };
	}
	else {
		font = TTF_OpenFont("font.ttf", bigscoresize);

		pos = { SCORE1::NUMPOSX, 
			    SCORE1::NUMPOSY - (bigscoresize - scoresize) };
	}

	surface = TTF_RenderUTF8_Blended(font, score1.c_str(), { 200,100,100,255 });
	texture = SDL_CreateTextureFromSurface(Renderer, surface);
	int iw, ih;
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect1 = { 0,0,iw,ih };
	SDL_Rect pasteRect1 = { pos.x, pos.y,iw,ih };
	SDL_RenderCopy(Renderer, texture, &txtRect1, &pasteRect1);

	if (!scores.isAdd(P2)) {
		font = TTF_OpenFont("font.ttf", scoresize);
		pos = { SCORE2::NUMPOSX, SCORE2::NUMPOSY };
	}
	else {
		font = TTF_OpenFont("font.ttf", bigscoresize);

		pos = { SCORE2::NUMPOSX,
				SCORE2::NUMPOSY - (bigscoresize - scoresize) };
	}
	surface = TTF_RenderUTF8_Blended(font, score2.c_str(), { 100,100,200,255 });
	texture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect2 = { 0,0,iw,ih };
	SDL_Rect pasteRect2 = { pos.x, pos.y,iw,ih };
	SDL_RenderCopy(Renderer, texture, &txtRect2, &pasteRect2);
}

Times_Font::~Times_Font()
{
}


