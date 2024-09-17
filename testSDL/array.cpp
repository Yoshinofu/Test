#include "array.h"

Array::Array()
	: P1COLOR(BRACK)
	, P2COLOR(WHITE)
	, clearline{false}
	, oneline{false}
	, vanish(P0)
{
	box.resize(FieldSize::LINES);	
	for (int i = 0; i < FieldSize::LINES; i++) {
		box[i].resize(FieldSize::COLUMNS);
	}
}

void Array::substitute(Array& arr)
{
	*this = arr;
}

STATUS Array::getStatus(Vector pos) const
{
	if (pos.x < 0) return BLANK;
	if (pos.x > FieldSize::COLUMNS - 1) return BLANK;
	if (pos.y > FieldSize::LINES - 1) return BLANK;
	return box[pos.y][pos.x].getStatus();
}

COLOR_No Array::getColor(Vector pos) const
{
	if (pos.x < 0) return NOTHING;
	if (pos.x > FieldSize::COLUMNS - 1) return NOTHING;
	if (pos.y > FieldSize::LINES - 1) return NOTHING;
	return box[pos.y][pos.x].getColor();
}

PLAYER_NO Array::getPlayer(Vector pos) const
{
	if (pos.x < 0) return P0;
	if (pos.x > FieldSize::COLUMNS - 1) return P0;
	if (pos.y > FieldSize::LINES - 1) return P0;
	return box[pos.y][pos.x].getPlayer();
}

PLAYER_NO Array::getVanish()
{
	return vanish;
}
bool Array::getClearLine(int y) const
{
	return clearline[y];
}

bool Array::getOneLine(int y) const
{
	return oneline[y];
}

COLOR_No Array::getPlayerColor(PLAYER_NO player) const
{
	if (player == P1) return P1COLOR;
	return P2COLOR;
}

MOVESTATUS Array::getMovestat(Vector pos) const
{
	if (pos.x < 0) return PLAY;
	if (pos.x > FieldSize::COLUMNS - 1) return PLAY;
	if (pos.y > FieldSize::LINES - 1) return PLAY;
	return box[pos.y][pos.x].getMoveStat();
}
Block Array::getBlock(Vector pos) const
{
	if (pos.x < 0) return box[0][0].getBlock();
	if (pos.x > FieldSize::COLUMNS - 1) return box[0][0].getBlock();
	if (pos.y > FieldSize::LINES - 1) return box[0][0].getBlock();
	return box[pos.y][pos.x].getBlock();
}

void Array::setPoint(Vector pos, Point point)
{
	if (pos.x < 0) return;
	if (pos.x > FieldSize::COLUMNS - 1) return;
	if (pos.y > FieldSize::LINES - 1) return;
	box[pos.y][pos.x].setPoint(point);
}
void Array::setMovestate(Vector pos, MOVESTATUS status)
{
	if (pos.x < 0) return;
	if (pos.x > FieldSize::COLUMNS - 1) return;
	if (pos.y > FieldSize::LINES - 1) return;
	box[pos.y][pos.x].setMoveStat(status);
}

void Array::setStatus(Vector pos, STATUS status) 
{
	if (pos.x < 0) return;
	if (pos.x > FieldSize::COLUMNS - 1) return;
	if (pos.y > FieldSize::LINES - 1) return;
	box[pos.y][pos.x].setStatus(status);
}

void Array::chaClearLine(int y, bool torf)
{
	clearline[y] = torf;
}

void Array::chaOneLine(int y, bool torf)
{
	oneline[y] = torf;
}

void Array::setColor(Vector pos, COLOR_No color) 
{
	if (pos.x < 0) return;
	if (pos.x > FieldSize::COLUMNS - 1) return;
	if (pos.y > FieldSize::LINES - 1) return;
	box[pos.y][pos.x].setColor(color);
}

void Array::setVanish(PLAYER_NO player)
{
	vanish = player;
}

void Array::setPlayer(Vector pos, PLAYER_NO player)
{
	if (pos.x < 0) return;
	if (pos.x > FieldSize::COLUMNS - 1) return;
	if (pos.y > FieldSize::LINES - 1) return;
	box[pos.y][pos.x].setPlayer(player);
}

void Array::setPlayerColor(PLAYER_NO player, COLOR_No color)
{
	if (player == P1) P1COLOR = color;
	else P2COLOR = color;
}


void Array::init()
{
	const int max_x = FieldSize::COLUMNS;
	const int max_y = FieldSize::LINES-1;

	for (int y = 0; y < max_y; y++) {
		box[y][0].setStatus(STACKED);
		box[y][max_x-1].setStatus(STACKED);
		box[y][0].setColor(GRAY);
		box[y][max_x-1].setColor(GRAY);
	}

	for (int x = 0; x < max_x; x++) {
		box[max_y][x].setStatus(STACKED);
		box[max_y][x].setColor(GRAY);
	}
	for (int x = 0; x < max_x; x++) {
		for (int y = 0; y < max_y; y++) {
			int status = box[y][x].getStatus();
			if (status != STACKED) {
				box[y][x].setColor(NOTHING);
				box[y][x].setStatus(BLANK);
			}
		}
	}
}

void Array::clearBlock(Vector pos)
{
	setStatus(pos, BLANK);
	setColor(pos, NOTHING);
	setPlayer(pos, P0);
}


void Array::clearStacked()
{
	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
		for (int y = 0; y < FieldSize::LINES - 1; y++) {
			if (getStatus({ x,y }) != STACKED) continue;
			clearBlock({ x,y });
		}
	}
}