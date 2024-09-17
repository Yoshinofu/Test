#include "effect.h"
#include "font.h"

Effect::Effect(Array* parray)
	:array(parray)
	,clearline(parray)
	//,Vanishblocks(parray)
{
}

EffectState::EffectState()
	:t(0)
	,flag(false)
{
}

int EffectState::get_t()
{
	return t;
}
int EffectState::get_flag()
{
	return flag;
}

EffectState EffectState::getState()
{
	return *this;
}
void EffectState::chaflag(bool torf)
{
	flag = torf;
}
void EffectState::add_t(int add)
{
	t += add;
}
void EffectState::reset_t()
{
	t = 0;
}

void Effect::draw(SDL_Renderer* Renderer)
{
	clearline.draw(Renderer);
	//Vanishblocks.draw(Renderer);
}

void ClearLine::draw(SDL_Renderer* Renderer)
{
	for (int y = FieldSize::LINES - 1; y >= 0; y--) {
		if (array->getOneLine(y)) {
			array->chaOneLine(y, moveBlocks(y, Renderer));
		}
	}
}

int ClearLine::defDirection(int x1, int x2)
{
	if (x1 == x2) return 1;
	return (x1 - x2) / abs(x1 - x2);
}

bool ClearLine::isDomain(int x)
{
	return SCORE1::NUMPOSX <= x && x <= SCORE2::NUMPOSX;
}

Vector ClearLine::coordinate(Vector pos, Vector goll)
{
	int t = e_array[pos.y][pos.x].get_t();
	Vector point = block.changePoint(pos);
	int direction = defDirection(goll.x, point.x);
	int x = point.x + direction * t;
	int y = (point.y - goll.y) * (x - point.x) / (point.x - goll.x) + point.y;
	return { x,y };
}


bool ClearLine::moveBlock(Vector pos, Vector goll, SDL_Renderer* Renderer)
{
	if (e_array[pos.y][pos.x].get_flag()) return false;
	Vector coord = coordinate(pos, goll);

	if (!isDomain(coord.x)) {
		e_array[pos.y][pos.x].reset_t();
		e_array[pos.y][pos.x].chaflag(true);
		return false;
	}
	block.drawBlock(Renderer, coord, array->getColor(pos));
	e_array[pos.y][pos.x].add_t(7);
	return true;
}


Vector ClearLine::goll(Vector pos)
{
	if (array->getPlayer(pos) == P1)
		return { SCORE1::NUMPOSX, SCORE1::NUMPOSY };
	else return { SCORE2::NUMPOSX, SCORE2::NUMPOSY };
}

bool ClearLine::moveBlocks(int y, SDL_Renderer* Renderer)
{
	int count = 0;
	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
		Vector pos = { x,y };
		if (!moveBlock(pos, goll(pos), Renderer)) {
			count++;
		}
	}
	if (count >= FieldSize::COLUMNS - 2) {
		for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
			e_array[y][x].chaflag(false);
		}
		return false;
	}
	return true;
}


ClearLine::ClearLine(Array* parray)
	:array(parray)
{
}

ClearLine::~ClearLine()
{
	
}

//Vector VanishBlocks::calcCenter(PLAYER_NO player)
//{
//	Vector ret = { 0,0 };
//	int num = 0;
//	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
//		for (int y = 1; y < FieldSize::LINES - 1; y++) {
//			if (array->getPlayer({ x,y }) == player){
//				ret.x += x;
//				num++;
//			}
//		}
//	}
//	ret.x = ret.x / num;
//	return ret;
//}
//
//int VanishBlocks::defDirection(int x1, int x2)
//{
//	if (x1 == x2) return 1;
//	return (x1 - x2) / abs(x1 - x2);
//}
//
//Vector VanishBlocks::coordinate(Vector pos, Vector vertex)
//{
//	int t = e_array[pos.y][pos.x].get_t();
//	Vector point = block.changePoint(pos);
//	int direction = defDirection(pos.x, vertex.x);
//	int a = abs(point.y - vertex.y) / ((point.x - vertex.x) * (point.x - vertex.x));
//	int x = point.x + direction * t;
//	int y =  a * (x - vertex.x) * (x - vertex.x) + vertex.y;
//	return { x,y };
//}
//
//
//bool VanishBlocks::moveBlock(Vector pos, Vector vertex, SDL_Renderer* Renderer)
//{
//	if (e_array[pos.y][pos.x].get_flag()) return false;
//	Vector coord = coordinate(pos, vertex);
//
//	if (coord.x >= WindowLength::HEIGHT) {
//		e_array[pos.y][pos.x].reset_t();
//		e_array[pos.y][pos.x].chaflag(true);
//		return false;
//	}
//	block.drawBlock(Renderer, coord, array->getColor(pos));
//	e_array[pos.y][pos.x].add_t(7);
//	return true;
//}
//
//bool VanishBlocks::moveBlocks(Vector vertex, SDL_Renderer* Renderer)
//{
//	int count = 0;
//	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
//		for (int y = 0; y < FieldSize::LINES - 1; y++) {
//			if (!moveBlock({ x,y }, vertex, Renderer)) {
//				count++;
//			}
//		}
//	}
//
//	if (count >= num) {
//		for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
//			for (int y = 0; y < FieldSize::LINES - 1; y++) {
//				e_array[y][x].chaflag(false);
//			}
//		}
//		return false;
//	}
//	return true;
//}
//
//void VanishBlocks::draw(SDL_Renderer* Renderer)
//{
//	PLAYER_NO player = array->getVanish();
//	if ( player != P0 && !flag) {
//		flag = true;
//		for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
//			for (int y = 0; y < FieldSize::LINES - 1; y++) {
//				if (player == BOTH) {
//					if (array->getPlayer({ x,y }) != P0) {
//						num++;
//					}
//				}
//				else {
//					if (array->getPlayer({ x,y }) == player) {
//						num++;
//					}
//				}
//			}
//		}
//	}
//	if (!flag) return;
//
//	Vector vertex = block.changePoint(calcCenter());
//
//	if (!moveBlocks(vertex, Renderer)) {
//		flag = false;
//		array->setVanish(P0);
//		num = 0;
//	}
//}
//
//VanishBlocks::VanishBlocks(Array* parray)
//	:array(parray)
//{
//}
