#pragma once
#include "constant.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "array.h"

class MinoList
{
private:
	MINO_NO list[5];
	PLAYER_NO playerNo;
	MINO_NO holdMino;
public:
	MinoList(PLAYER_NO pNo);
	MINO_NO getMino(int num);
	void setMino(int num, MINO_NO minoNo);
	MINO_NO getHoldMino();
	void setHoldMino(MINO_NO minoNo);
};

class MinoLists
{
private:
	int get_rand(int min, int max);
	void looplist(MinoList& minolist);
	MinoList minolist1;
	MinoList minolist2;
public:
	MinoLists(PLAYER_NO player1, PLAYER_NO player2);
	void init();
	void change(PLAYER_NO playerNo);
	MINO_NO getMinoNo(PLAYER_NO pNo, int number);
	MINO_NO getHoldMino(PLAYER_NO pNo);
	void setHoldMino(PLAYER_NO pNo, MINO_NO minoNo);
	void setMino(PLAYER_NO pNo, MINO_NO minoNo, int num);
};

class Flag
{
private:
	bool gameover;
	bool addspin;
	bool subspin;
	bool dush;
	bool vanish;
	HOLDSTATUS hold;
public:
	Flag();
	bool getGameover();
	bool getAddSpin();
	bool getSubSpin();
	bool getDush();
	HOLDSTATUS getHold();

	void chaGameover(bool torf);
	void chaAddSpin(bool torf);
	void chaSubSpin(bool torf);
	void chaDush(bool torf);
	void chaHold(HOLDSTATUS status);
};

class Mino
{
private:
	int spin;
	Vector pos;
	MINO_NO minoNo;
	PLAYER_NO playerNo;
	STATUS status;
	COLOR_No color;
	int speed;
	int dspeed;
	bool button[4];
public:
	Mino();
	Mino(PLAYER_NO player);
	Mino(Mino& mino);
	Flag flag;

	void init(PLAYER_NO pNo, MINO_NO mNo);

	STATUS getStatus() const;
	MINO_NO getMinoNo() const;
	PLAYER_NO getPlayerNo();
	Vector getPos() const;
	int getSpin() const;
	void setSpin(int num);
	COLOR_No getColor() const;
	COLOR_No getMinoColor(MINO_NO num) const;
	int getSpeed() const;
	int getDSpeed() const;
	COLOR_No getArrayColor(Vector pos) const;
	bool getButton(BUTTONSTATUS num) const;
	void addPosX(int x);
	void addPosY(int y);
	void setStatus(STATUS sta);
	void setColor(COLOR_No cNo);
	void setSpeed(int level);
	void setDSpeed(int level);
	void setMinoNo(MINO_NO No);
	void setButton(BUTTONSTATUS num, bool torf);
    void addSpin();
	void subSpin();
	void retArray(COLOR_No array[4][4], COLOR_No ret[4][4]) const;
	void retMino(COLOR_No array[4][4]) const;
	void clearMino(Array& array);
	void adaptArray(Array& array);
	COLOR_No defColor();
	COLOR_No toBrack();
	COLOR_No toWhite();
};


