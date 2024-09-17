#include "mino.h"

Flag::Flag()
	: gameover(false)
	, addspin(false)
	, subspin(false)
	, hold(PASS)
	, dush(false)
	, vanish(false)
{
}

bool Flag::getGameover()
{
	return gameover;
}
bool Flag::getAddSpin()
{
	return addspin;
}
bool Flag::getSubSpin()
{
	return subspin;
}
bool Flag::getDush()
{
	return dush;
}

HOLDSTATUS Flag::getHold()
{
	return hold;
}

void Flag::chaGameover(bool torf)
{
	gameover = torf;
}
void Flag::chaAddSpin(bool torf)
{
	addspin = torf;
}
void Flag::chaSubSpin(bool torf)
{
	subspin = torf;
}
void Flag::chaDush(bool torf)
{
	dush = torf;
}

void Flag::chaHold(HOLDSTATUS status)
{
	hold = status;
}

MinoList::MinoList(PLAYER_NO pNo)
	:playerNo(pNo)
	,list{O_MINO}
	,holdMino(NONE)
{
}

MINO_NO MinoList::getMino(int num)
{
	return list[num];
}

void MinoList::setMino(int num, MINO_NO minoNo)
{
	list[num] = minoNo;
}

MINO_NO MinoList::getHoldMino()
{
	return holdMino;
}
void MinoList::setHoldMino(MINO_NO minoNo)
{
	holdMino = minoNo;
}


int MinoLists::get_rand(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

MinoLists::MinoLists(PLAYER_NO player1, PLAYER_NO player2)
	:minolist1(player1)
	,minolist2(player2)
{
}

MINO_NO MinoLists::getHoldMino(PLAYER_NO pNo)
{
	if (pNo == P1) return minolist1.getHoldMino();
	else return minolist2.getHoldMino();
}

void MinoLists::setHoldMino(PLAYER_NO pNo, MINO_NO minoNo)
{
	if (pNo == P1) minolist1.setHoldMino(minoNo);
	else minolist2.setHoldMino(minoNo);
}

void MinoLists::init()
{
	minolist1.setMino(0, MINO_NO(get_rand(I_MINO, Z_MINO)));
	minolist2.setMino(0, MINO_NO(get_rand(I_MINO, Z_MINO)));

	for (int i = 1; i < NextLength::NUM + 1; i++) {
		minolist1.setMino( i, MINO_NO(get_rand(I_MINO, Z_MINO)));
		while (minolist1.getMino(i - 1) == minolist1.getMino(i)) {
			minolist1.setMino( i, MINO_NO(get_rand(I_MINO, Z_MINO)));
		}
	}

	for (int i = 1; i < NextLength::NUM + 1; i++) {
		minolist2.setMino( i, MINO_NO(get_rand(I_MINO, Z_MINO)));
		while (minolist2.getMino(i - 1) == minolist2.getMino(i)) {
			minolist2.setMino( i, MINO_NO(get_rand(I_MINO, Z_MINO)));
		}
	}
	setHoldMino(P1, NONE);
	setHoldMino(P2, NONE);
}

void MinoLists::setMino(PLAYER_NO pNo, MINO_NO minoNo, int num)
{
	if (pNo == P1) minolist1.setMino(num, minoNo);
	else minolist2.setMino(num, minoNo);
}


void MinoLists::looplist(MinoList& minolist)
{
	for (int i = 0; i < NextLength::NUM; i++) {
		minolist.setMino( i, minolist.getMino(i + 1));
	}
}

void MinoLists::change(PLAYER_NO playerNo)
{
	if (playerNo == P1) {
		looplist(minolist1);
		while (minolist1.getMino(3) == minolist1.getMino(4)) {
			minolist1.setMino( 4, MINO_NO(get_rand(I_MINO, Z_MINO)));
		}
	}

	else if (playerNo == P2) {
		looplist(minolist2);
		while (minolist2.getMino(3) == minolist2.getMino(4)) {
			minolist2.setMino( 4, MINO_NO(get_rand(I_MINO, Z_MINO)));
		}
	}
}

MINO_NO MinoLists::getMinoNo(PLAYER_NO pNo, int number)
{
	if (pNo == P1) return minolist1.getMino(number);
	else return minolist2.getMino(number);
}

Mino::Mino()
	:spin(0)
	, pos({ 0,0 })
	, minoNo(O_MINO)
	, playerNo(P1)
	, status(FALLING)
	, color(NOTHING)
	, speed(1)
	, dspeed(1)
	, button{ false }
{
}

Mino::Mino(PLAYER_NO player)
	:spin(0)
	,pos({0,0})
	,minoNo(O_MINO)
	,playerNo(player)
	,status(FALLING)
	,color(NOTHING)
	,speed(1)
	,dspeed(1)
	,button{false}
{
}

Mino::Mino(Mino& mino)
{
	*this = mino;
}

void Mino::init(PLAYER_NO pNo, MINO_NO mNo)
{
	minoNo = mNo;
	status = FALLING;
	spin = 0;
	if (pNo == P1) pos = { 2, 1 };
	else if (pNo == P2 ) pos = { 9, 1 };
}

STATUS Mino::getStatus() const
{
	return status;
}

MINO_NO Mino::getMinoNo() const
{
	return minoNo;
}
PLAYER_NO Mino::getPlayerNo()
{
	return playerNo;
}

Vector Mino::getPos() const
{
	return pos;
}

COLOR_No Mino::getColor() const
{
	return color;
}

COLOR_No Mino::getMinoColor(MINO_NO num) const
{
	switch (num)
	{
	case NONE:
		return NOTHING;
		break;
	case I_MINO:
		return IMINO::c;
		break;
	case J_MINO:
		return JMINO::c;
		break;
	case L_MINO:
		return LMINO::c;
		break;
	case O_MINO:
		return OMINO::c;
		break;
	case S_MINO:
		return SMINO::c;
		break;
	case T_MINO:
		return TMINO::c;
		break;
	case Z_MINO:
		return ZMINO::c;
		break;
	default:
		break;
	}
	return NOTHING;
}

int Mino::getSpeed() const
{
	return speed;
}

int Mino::getDSpeed() const
{
	return dspeed;
}

void Mino::setStatus(STATUS sta)
{
	status = sta;
}

void Mino::addPosX(int x)
{
	pos.x += x;
	if (pos.x > FieldSize::COLUMNS - 2) pos.x = FieldSize::COLUMNS - 2;
	if (pos.x < 0)
		pos.x = 0;
}

void Mino::addPosY(int y)
{
	pos.y += y;
}

void Mino::setColor(COLOR_No cNo)
{
	color = cNo;
}

void Mino::setSpeed(int level)
{
	if (level > 10) level = 10;
	speed = level;
}

void Mino::setDSpeed(int level)
{
	if (level > 10) level = 10;
	dspeed = level;
}

void Mino::addSpin()
{
	spin += 1;
	spin = spin % 4;
}

void Mino::subSpin()
{
	spin += 3;
	spin = spin % 4;
}

void Mino::retArray(COLOR_No array[4][4], COLOR_No ret[4][4]) const
{
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			ret[y][x] = array[y][x];
		}
	}
}

void Mino::retMino(COLOR_No array[4][4]) const
{
	
	switch (minoNo)
	{
	case NONE:
		return;
		break;
	case I_MINO:
		switch (spin%2)
		{
		case 0:
			retArray(IMINO::array0, array);
			break;
		case 1:
			retArray(IMINO::array1, array);
			break;
		default:
			break;
		}
		break;
	case J_MINO:
		switch (spin)
		{
		case 0:
			retArray(JMINO::array0, array);
			break;
		case 1:
			retArray(JMINO::array1, array);
			break;
		case 2:
			retArray(JMINO::array2, array);
			break;
		case 3:
			retArray(JMINO::array3, array);
			break;
		default:
			break;
		}
		break;
	case L_MINO:
		switch (spin)
		{
		case 0:
			retArray(LMINO::array0, array);
			break;
		case 1:
			retArray(LMINO::array1, array);
			break;
		case 2:
			retArray(LMINO::array2, array);
			break;
		case 3:
			retArray(LMINO::array3, array);
			break;
		default:
			break;
		}		
		break;
	case O_MINO:
		retArray(OMINO::array0, array);
		break;
	case S_MINO:
		switch (spin%2)
		{
		case 0:
			retArray(SMINO::array0, array);
			break;
		case 1:
			retArray(SMINO::array1, array);
			break;
		default:
			break;
		}
		break;
	case T_MINO:
		switch (spin)
		{
		case 0:
			retArray(TMINO::array0, array);
			break;
		case 1:
			retArray(TMINO::array1, array);
			break;
		case 2:
			retArray(TMINO::array2, array);
			break;
		case 3:
			retArray(TMINO::array3, array);
			break;
		default:
			break;
		}
		break;
	case Z_MINO:
		switch (spin%2)
		{
		case 0:
			retArray(ZMINO::array0, array);
			break;
		case 1:
			retArray(ZMINO::array1, array);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}

COLOR_No Mino::getArrayColor(Vector pos) const
{
	COLOR_No ret[4][4] = { NOTHING };
	retMino(ret);
	return ret[pos.y][pos.x];
}

void Mino::setMinoNo(MINO_NO No)
{
	minoNo = No;
}

COLOR_No Mino::defColor()
{
	if (status != STACKED) {
		return getMinoColor(minoNo);
	}
	switch (playerNo)
	{
	case P0:
		return getMinoColor(minoNo);
		break;
	case P1:
		return toBrack();
		break;
	case P2:
		return toWhite();
		break;
	default:
		break;
	}
	return NOTHING;
}

void Mino::clearMino(Array& array)
{
	for (int x = 0; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			Vector pos = { x,y };
			if (array.getStatus(pos) == STACKED) continue;
			PLAYER_NO player = array.getPlayer(pos);
			if (player == playerNo) {
				array.setColor(pos, NOTHING);
				array.setStatus(pos, BLANK);
				array.setPlayer(pos, P0);
			}
		}
	}
}

bool Mino::getButton(BUTTONSTATUS num) const
{
	return button[num];
}

int Mino::getSpin() const
{
	return spin;
}
void Mino::setSpin(int num)
{
	spin = num;
}
void Mino::setButton(BUTTONSTATUS num, bool torf)
{
	button[num] = torf;
}


void Mino::adaptArray(Array& array)
{
	clearMino(array);
	COLOR_No ret[4][4] = { NOTHING };
	COLOR_No color = defColor();
	retMino(ret);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (ret[y][x] == NOTHING) continue;
			Vector pos_ = { pos.x + x, pos.y + y };
			array.setColor(pos_, color);
			array.setStatus(pos_, status);
			array.setPlayer(pos_, playerNo);
		}
	}
}

COLOR_No Mino::toBrack()
{
	switch (minoNo)
	{
	case NONE:
		return NOTHING;
		break;
	case I_MINO:
		return IMINO::bc;
		break;
	case J_MINO:
		return JMINO::bc;
		break;
	case L_MINO:
		return LMINO::bc;
		break;
	case O_MINO:
		return OMINO::bc;
		break;
	case S_MINO:
		return SMINO::bc;
		break;
	case T_MINO:
		return TMINO::bc;
		break;
	case Z_MINO:
		return ZMINO::bc;
		break;
	default:
		break;
	}
	return NOTHING;
}

COLOR_No Mino::toWhite()
{
	switch (minoNo)
	{
	case NONE:
		return NOTHING;
		break;
	case I_MINO:
		return IMINO::wc;
		break;
	case J_MINO:
		return JMINO::wc;
		break;
	case L_MINO:
		return LMINO::wc;
		break;
	case O_MINO:
		return OMINO::wc;
		break;
	case S_MINO:
		return SMINO::wc;
		break;
	case T_MINO:
		return TMINO::wc;
		break;
	case Z_MINO:
		return ZMINO::wc;
		break;
	default:
		break;
	}
	return NOTHING;
}
