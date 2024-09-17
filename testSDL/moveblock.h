#pragma once
#include "block.h"
#include "constant.h"
#include <vector>
#include <functional>
#include "font.h"
#include "array.h"
#include "math.h"


class Vanish
{
private:
	Point goll1 = { float(FieldPos::X), float(FieldLength::HEIGHT) };
	Point goll2 = { float(FieldPos::X) + float(FieldLength::WIDTH - BlockLength::WIDTH), float(FieldLength::HEIGHT) };
	float direction(const Block& block);
public:
	void coordinate(Block& block);
	bool isDone(float y);
};

class ToScore
{
private:
	Point goll1 = { float(SCORE1::NUMPOSX), float(SCORE1::NUMPOSY) };
	Point goll2 = { float(SCORE2::NUMPOSX - 10), float(SCORE2::NUMPOSY) };
	Point defGoll(PLAYER_NO player);
	float direction(PLAYER_NO player);
public:
	void coordinate(Block& block);
	bool isDone(float x);
};

class GameSet
{
private:
	Point center = { float(FieldPos::X + FieldLength::WIDTH / 2),
					 float(FieldPos::Y + FieldLength::HEIGHT / 2)};
	const double PI = 3.141593;
	COLOR_No mP1color = BRACK;
	COLOR_No mP2color = WHITE;
	float radius(Point point);
	double radian(Point point);
	void coordCircle(Block& block);
	void changeStatus(Block& block);
	void changePlayer(Block& block);
	void changeColor(Block& block);
public:
	void coordinate(Block& block);
	void setColor(COLOR_No P1color, COLOR_No P2color);

};

class MoveBlocks
{
private:
	std::vector<Block> mblocks;
	COLOR_No mP1color = WHITE;
	COLOR_No mP2color = BRACK;
	DrawBlock drawblock;
	ToScore toscore;
	Vanish vanish;
	GameSet gameset;
	bool isRemove(const Block& block);
	void coordinate(Block& block);
	Vector VanishCoord(Block& block);
	void scoreUpdate(Block& block, Scores& scores);
public:
	MoveBlocks();
	Point changePoint(Vector pos);
	void init(COLOR_No P1color, COLOR_No P2color);
	void update(Scores& scores);
	void draw(SDL_Renderer* Renderer, Scores& scores);
	void add(Block block, Vector pos, MOVESTATUS movestatus);
	void add(Block block, Vector pos, MOVESTATUS movestatus, Vector vertex);
	void addAllStacked(Array& array);
	void addT(int add);
	size_t getSize();
};

