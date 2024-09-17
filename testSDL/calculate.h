#pragma once
#include "constant.h"
#include "mino.h"
#include "array.h"
#include "input.h"
#include "times.h"
#include "moveblock.h"


class RefInput
{
protected:
	int timeKeeper[2];
	Array* array;
	Mino* mino;
	virtual void LandR(const InputState& state) = 0;
	virtual void down(const InputState& state) = 0;
	virtual void spin(const InputState& state) = 0;
	virtual void hold(const InputState& state) = 0;
	bool sameStatus( Vector pos);
	bool samePlayer( Vector pos);
	bool isRight();
	bool isLeft();
	bool isBelow();
	bool isOn();
	int  minoBottom(int x);
	int	 blockTop(Vector pos);
	int  bottom();

public:
	RefInput();
	RefInput(Array* parray, Mino* pmino);
	RefInput(const RefInput& refinput);
	virtual void refInput(const InputState& state) = 0;
};

class Keyboard : public RefInput
{
private:
	void LandR(const InputState& state);
	void down(const InputState& state);
	void spin(const InputState& state);
	void hold(const InputState& state);
public:
	Keyboard();
	Keyboard(Array* parray, Mino* pmino);
	Keyboard(const Keyboard& keyboard);
	void refInput(const InputState& state);
};

class Controller : public RefInput
{
private:
	void LandR(const InputState& state);
	void down(const InputState& state);
	void spin(const InputState& state);
	void hold(const InputState& state);
public:
	Controller();
	Controller(Array* parray, Mino* pmino);
	Controller(const Controller& controller);
	void refInput(const InputState& state);
};


class Update
{
private:
	Array* array;
	Mino* mino;
	bool clearmyblocks = false;

	int count;
	bool sameStatus(Vector pos);
	bool samePlayer(Vector pos);
	void clearMino();
	bool isBelow();
	bool isStacked();
	void fall();
	void spin();
	void hold(MinoLists& minolists);
	bool isOverlap();
	int  minoBottom(int x);
	int	 shadowY(int x);
	int  bottom();
	void shadow();
	bool isGameOver();
	COLOR_No defColor();
	COLOR_No toBrack(MINO_NO mino);
	COLOR_No toWhite(MINO_NO mino);
	void clearBox();
public:
	Update(Array* parray, Mino* pmino);
	void pre();
	void adaptMino();
	int getCount();
	void resetCount();
	void addCount(int add);
	bool update(MinoLists& minolists);

};

class Calculate
{
private:
	Array* array;
	Mino* mino1;
	Mino* mino2;
	Times* times;

	Update upd_1;
	Update upd_2;
	void clearBox();
	void pre();
	void adaptMino();
	bool update(MinoLists& minolists, MoveBlocks& moveblocks);
	bool isOneLine(int y);
	void oneDown(int line);
	void clearLine(MoveBlocks& moveblocks);
	//void score(int y);
	void calcSpeed();
	void clearBlocks(PLAYER_NO player);
	void clearBlock(Vector pos);
	void toMoveBlocks(PLAYER_NO player, MoveBlocks& moveblocks, Vector vertex);
	Vector calcVertex(PLAYER_NO player);
public:
	Calculate(Array* parray, Mino* pmino1, Mino* pmino2, Times* ptimes);
	void calculate(MinoLists& minolists, MoveBlocks& moveblocks);
};


