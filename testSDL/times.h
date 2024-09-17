#pragma once
#include "constant.h"

class Times
{
private:
	float TIMELIMIT = TIMELIMIT::t;
	float seconds;
	int count;
	float timer;
public:
	Times();
	void update(float deltaTime);
	void update(float deltaTime, bool start);
	float getSeconds() const;
	int getCount() const;
	float getTimer() const;
	bool TimeLimit();
	void reset();
};

class Score
{
private:
	int score = 0;
	int removeblocks = 0;
	bool flag = false;
public:
	int t = 0;
	int getScore() const;
	void addScore(int add);
	int getRemBlocks() const;
	void addRemBlocks(int add);
	bool isAdd();
	void reset();
};

class Scores
{
private:
	Score score1;
	Score score2;
public:
	void addScore(int add, PLAYER_NO player);
	void addRemBlocks(int add, PLAYER_NO player);
	int getScore(PLAYER_NO player) const;
	int getRemBlocks(PLAYER_NO player) const;
	bool isAdd(PLAYER_NO player);
	PLAYER_NO winer();
	void reset();
};