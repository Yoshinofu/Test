#pragma once
#include "SDL.h"
#include "block.h"
#include "array.h"
#include "constant.h"
#include "mino.h"

class EffectState {
private:
	int t;
	bool flag;
public:
	EffectState();
	EffectState getState();
	int get_t();
	int get_flag();
	void chaflag(bool torf);
	void add_t(int add);
	void reset_t();
};

//class VanishBlocks {
//private:
//	Array* array;
//
//	bool flag = false;
//	int num = 0;
//	DrawBlock block;
//	EffectState e_array[50][50];
//	Vector calcCenter(PLAYER_NO player);
//	int defDirection(int x1, int x2);
//	Vector coordinate(Vector pos, Vector vertex);
//	bool moveBlock(Vector pos, Vector pos_vertex, SDL_Renderer* Renderer);
//	bool moveBlocks(Vector vertex, SDL_Renderer* Renderer);
//
//public:
//	VanishBlocks(Array* parray);
//	void draw(SDL_Renderer* Renderer);
//};

class ClearLine {
private:
	Array* array;
	DrawBlock block;
	EffectState e_array[50][50];
	Vector goll(Vector pos);
	bool isDomain(int x);
	Vector coordinate(Vector pos, Vector goll);
	int defDirection(int x1, int x2);
	bool moveBlock(Vector start, Vector goll, SDL_Renderer* Renderer);
	bool moveBlocks(int y, SDL_Renderer* Renderer);
public:
	ClearLine(Array* parray);
	~ClearLine();
	void draw(SDL_Renderer* Renderer);
};


class Effect {
private:
	Array* array;
	ClearLine clearline;
	//VanishBlocks Vanishblocks;

public:
	Effect(Array* parray);
	void draw(SDL_Renderer* Renderer);
};
