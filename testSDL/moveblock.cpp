#include "moveblock.h"

void MoveBlocks::add(Block block, Vector pos, MOVESTATUS movestatus)
{
	Point point = changePoint(pos);
	Block mblock(block, point, movestatus);
	mblocks.push_back(mblock);
}

void MoveBlocks::add(Block block, Vector pos, MOVESTATUS movestatus, Vector vertex)
{
	Point point = changePoint(pos);
	Point pvertex = changePoint(vertex);
	Block mblock(block, point, movestatus, pvertex);
	mblocks.push_back(mblock);
}

void MoveBlocks::addAllStacked(Array& array)
{
	for (int x = 1; x < FieldSize::COLUMNS-1; x++) {
		for (int y = 0; y < FieldSize::LINES-1; y++) {
			Vector pos = { x,y };
			if (array.getStatus(pos) != STACKED) continue;
			add(array.getBlock(pos), pos, GAMESET);
		}
	}
}

void MoveBlocks::draw(SDL_Renderer* Renderer, Scores& scores)
{
	for (int i = 0; i < mblocks.size(); i++) {
		Point point = mblocks[i].getPoint();
		Vector pos = { int(point.x), int(point.y) };
		drawblock.drawBlock(Renderer, pos, mblocks[i].getColor());
	}
	update(scores);
}

void MoveBlocks::update(Scores& scores)
{
	addT(1);
	for (int i = 0; i < mblocks.size(); i++) {
		coordinate(mblocks[i]);
	}

	auto itr = mblocks.begin();
	while (itr != mblocks.end()){
		if (isRemove(*itr)){
			scoreUpdate(*itr, scores);
			itr = mblocks.erase(itr);
		}
		else{
			itr++;
		}
	}
}

void ToScore::coordinate(Block& block)
{
	Point goll = defGoll(block.getPlayer());
	Point point = block.getPoint();
	float dx = direction(block.getPlayer()) * block.getT() * block.getT() / 100;
	float dy = (goll.y - point.y) * dx / (goll.x - point.x) ;
	block.setPoint({ point.x + dx, point.y + dy });
}

void MoveBlocks::scoreUpdate(Block& block, Scores& scores)
{
	if (block.getMoveStat() != TOSCORE) return;
	scores.addRemBlocks(1, block.getPlayer());
}

bool MoveBlocks::isRemove(const Block& block)
{
	if (block.getMoveStat() == TOSCORE)
		return toscore.isDone(block.getPoint().x);
	if (block.getMoveStat() == VANISH) 
		return vanish.isDone(block.getPoint().y);
	return block.getT() > 1000;
}

void MoveBlocks::coordinate(Block& block)
{
	MOVESTATUS status = block.getMoveStat();
	if (status == TOSCORE) {
		toscore.coordinate(block);
	}
	if (status == VANISH) {
		vanish.coordinate(block);
	}
	if (status == GAMESET) {
		gameset.coordinate(block);
	}
}


Point MoveBlocks::changePoint(Vector pos)
{
	Point ret;
	ret.x = float(pos.x * BlockLength::WIDTH + FieldPos::X);
	ret.y = float(pos.y * BlockLength::HEIGHT + FieldPos::Y);
	return ret;
}

Vector MoveBlocks::VanishCoord(Block& block)
{
	return { 0,0 };
}
size_t MoveBlocks::getSize()
{
	return mblocks.size();
}

void MoveBlocks::addT(int add)
{
	for (int i = 0; i < mblocks.size(); i++) {
		mblocks[i].addT(add);
	}
}

MoveBlocks::MoveBlocks()
	:gameset()
{
}

void MoveBlocks::init(COLOR_No P1color, COLOR_No P2color)
{
	mP1color = P1color;
	mP2color = P2color;
	gameset.setColor(P1color, P2color);
}


void Vanish::coordinate(Block& block)
{
	Point point = block.getPoint();
	Point vertex = block.getVertex();
	float y = point.y + block.getT() * (abs(point.y) + 50) / FieldLength::HEIGHT;
	float x = point.x + (point.x - vertex.x) * 3 / FieldLength::WIDTH;
	block.setPoint({x,y});
}

float Vanish::direction(const Block& block)
{
	float ret = block.getPoint().x - block.getVertex().x;
	if (ret == 0) return 0;
	return ret / abs(ret);
}

bool Vanish::isDone(float y) {
	return y >= WindowLength::HEIGHT;
}

bool ToScore::isDone(float x)
{
	return !(goll1.x < x && x < goll2.x);
}

Point ToScore::defGoll(PLAYER_NO player)
{
	if (player == P1) return goll1;
	return goll2;
}

float ToScore::direction(PLAYER_NO player)
{
	if (player == P1) return -1;
	return 1;
}

float GameSet::radius(Point point)
{
	return sqrt((center.x - point.x) * (center.x - point.x) +
		   (center.y - point.y) * (center.y - point.y));
}

double GameSet::radian(Point point)
{
	return atan2(point.y - center.y, point.x - center.x);
}

void GameSet::coordCircle(Block& block)
{
	double r = radius(block.getPoint()) - 1;
	double rad = radian(block.getPoint()) + 2 * PI / r;
	float x = center.x + float(r * cos(rad));
	float y = center.y + float(r * sin(rad));
	block.setPoint({ x,y });
}

void GameSet::changePlayer(Block& block)
{
	if (block.getPlayer() == P1) block.setPlayer(P2);
	else block.setPlayer(P1);
}

void GameSet::changeColor(Block& block)
{
	Point point = block.getPoint();
	if (abs(center.x - point.x) <= 50) {
		if (abs(center.y - point.y) <= 50) {
			if (block.getPlayer() == P1) block.setColor(mP2color);
			else block.setColor(mP1color);
		}
	}
}


void GameSet::changeStatus(Block& block)
{
	Point point = block.getPoint();
	if (abs(center.x - point.x) <= 2) {
		if (abs(center.y - point.y) <= 2) {
			changePlayer(block);
			block.setMoveStat(TOSCORE);
			block.resetT();
		}
	}
}

void GameSet::setColor(COLOR_No P1color, COLOR_No P2color)
{
	mP1color = P1color;
	mP2color = P2color;
}

void GameSet::coordinate(Block& block)
{
	changeColor(block);
	changeStatus(block);
	coordCircle(block);
}
