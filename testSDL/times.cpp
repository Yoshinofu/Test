#include "times.h"

Times::Times()
	:seconds(0)
	,count(1)
	,timer(TIMELIMIT)
{
}

float zeroOrMore(float x, float sub) {
	if (x - sub <= 0) return 0;
	return x - sub;
}

void Times::update(float deltaTime)
{
	seconds += deltaTime;
	count += 1;
	timer = zeroOrMore(timer, deltaTime);
}

void Times::update(float deltaTime, bool start)
{
	if (start) return;
	seconds += deltaTime;
	count += 1;
}

float Times::getSeconds() const
{
	return seconds;
}
int Times::getCount() const
{
	return count;
}

float Times::getTimer() const
{
	return timer;
}

bool Times::TimeLimit()
{
	return timer <= 0;
}

void Times::reset()
{
	seconds = 0;
	count = 0;
	timer = TIMELIMIT;
}

PLAYER_NO Scores::winer()
{
	int sco1 = score1.getRemBlocks();
	int sco2 = score2.getRemBlocks();
	if (sco1 > sco2) return P1;
	else if (sco2 > sco1) return P2;
	return P0;
}

int Score::getScore() const
{
	return score;
}
void Score::addScore(int add)
{
	score += add;
}
int Score::getRemBlocks() const
{
	return removeblocks;
}
void Score::addRemBlocks(int add)
{
	removeblocks += add;
	flag = true;
}

void Scores::addScore(int add, PLAYER_NO player)
{
	if (player == P1) {
		score1.addScore(add);
		return;
	}
	score2.addScore(add);
}
void Scores::addRemBlocks(int add, PLAYER_NO player)
{
	if (player == P1) {
		score1.addRemBlocks(add);
		return;
	}
	score2.addRemBlocks(add);
}

bool Score::isAdd()
{
	if (flag) {
		if (t >= 60) {
			flag = false;
			t = 0;
		}
		return true;
	}
	else return false;
}

void Score::reset()
{
	score = 0;
	removeblocks = 0;
	flag = false;
	t = 0;
}

int Scores::getScore(PLAYER_NO player) const
{
	if (player == P1) return score1.getScore();
	return score2.getScore();
}

int Scores::getRemBlocks(PLAYER_NO player) const
{
	if (player == P1) return score1.getRemBlocks();
	return score2.getRemBlocks();
}

void Scores::reset()
{
	score1.reset();
	score2.reset();
}

bool Scores::isAdd(PLAYER_NO player)
{
	score1.t++;
	score2.t++;
	if (player == P1) return score1.isAdd();
	return score2.isAdd();
}