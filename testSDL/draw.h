#ifndef draw_h_
#define draw_h_

#include "SDL.h"
#include "block.h"
#include "constant.h"
#include "mino.h"
#include "array.h"


class DrawBackGround
{
private:
	int FIELDWIDTH;
	Color color;
public:
	DrawBackGround(int fieldwidth);
	void drawLine(SDL_Renderer* Renderer);
	void drawBackWall(SDL_Renderer* Renderer);
	void drawBackGround(SDL_Renderer* Renderer);
};

class DrawField
{
private:
	int FIELDWIDTH;
	DrawBackGround DdrawBackGround;
public:
	DrawField();
	void drawField(SDL_Renderer* Renderer);
};

class DrawMino
{
private:
	DrawBlock block;
	Vector defPos(Mino mino);
	void loopBlock(Vector pos, COLOR_No minoArray[4][4], SDL_Renderer* Renderer);
public:
	DrawMino();
	Vector changePoint(Vector pos);
	void draw(Vector pos, int minoNo, SDL_Renderer* Renderer);
};



class DrawHold
{
private:
	DrawMino drawMino;
public:
	DrawHold();
	void drawBackGround(SDL_Renderer* Renderer);
	Vector defPos(PLAYER_NO playerNo);
	void draw(SDL_Renderer* Renderer, MinoLists& minolists);
};

class DrawNext
{
private:
	DrawMino drawMino;
public:
	DrawNext();
	void drawBackGround(SDL_Renderer* Renderer);
	Vector defPos(PLAYER_NO playerNo);
	void draw(SDL_Renderer* Renderer, MinoLists& minolists);
};


class GetUpdata
{
private:
public:
	GetUpdata();
};

class DrawBack
{
private:
	DrawField field;
	DrawHold hold;
	DrawNext next;
public:
	DrawBack();
	void draw(SDL_Renderer* Renderer);
};

class DrawBox
{
private:
	DrawMino mino;
	DrawBlock block;

public:
	DrawBox();
	void draw(Array& array, SDL_Renderer* Renderer);
};

class Draw
{
private:
	DrawBack back;
	DrawBox box;
	DrawNext next;
	DrawHold hold;
public:
	Draw();
	void all(SDL_Renderer* Renderer, Array& array,MinoLists& minolists);
};
#endif