#pragma once
#include "block.h"
#include <vector>

class Array
{
private:
	std::vector< std::vector<Block> > box;
	bool clearline[30];
	bool oneline[30];
	PLAYER_NO vanish;
	COLOR_No P1COLOR;
	COLOR_No P2COLOR;
public: 
	Array();
	~Array() {};
	void init();
	STATUS getStatus(Vector pos) const;
	COLOR_No getColor(Vector pos) const;
	PLAYER_NO getPlayer(Vector pos) const;
	COLOR_No getPlayerColor(PLAYER_NO player) const;
	bool getClearLine(int y) const;
	bool getOneLine(int y) const;
	void setPoint(Vector pos, Point point);
	PLAYER_NO getVanish();
	MOVESTATUS getMovestat(Vector pos) const;
	Block getBlock(Vector pos) const;
	void setMovestate(Vector pos, MOVESTATUS status);
	void substitute(Array& arr);
	void setStatus(Vector pos, STATUS status);
	void setColor(Vector pos, COLOR_No color);
	void setPlayer(Vector pos, PLAYER_NO player);
	void setPlayerColor(PLAYER_NO player, COLOR_No color);
	void setVanish(PLAYER_NO player);
	void chaClearLine(int y, bool torf);
	void chaOneLine(int y, bool torf);
	void clearBlock(Vector pos);
	void clearStacked();
};

