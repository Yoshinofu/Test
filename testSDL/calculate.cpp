#include "calculate.h"

Controller::Controller()
	:RefInput()
{
}

Controller::Controller(Array* parray, Mino* pmino)
	:RefInput(parray, pmino)
{
}

Controller::Controller(const Controller& controller)
{
	*this = controller;
}

void Controller::refInput(const InputState& state)
{
	if (mino->getStatus() == STACKED) return;
	if (mino->flag.getGameover()) return;
	down(state);
	if (mino->getStatus() == STACKED) return;
	LandR(state);
	spin(state);
	hold(state);
}

void Controller::spin(const InputState& state)
{
	if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_A) == EPressed) {
		mino->flag.chaAddSpin(true);
	}

	if (state.Controller.GetButtonState(SDL_CONTROLLER_BUTTON_B) == EPressed) {
		mino->flag.chaSubSpin(true);
	}

	float left = state.Controller.GetLeftTrigger();
	mino->addPosX(int(left));
}

void Controller::down(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_UP) == EPressed
		&& !isOn()) {
		mino->addPosY(bottom());
		mino->setStatus(STACKED);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EReleased) {
		mino->flag.chaDush(false);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EPressed) {
		mino->flag.chaDush(true);
	}
}

void Controller::hold(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RSHIFT) == EPressed) {
		if (mino->flag.getHold() == SKIP) return;
		mino->flag.chaHold(GO);
	}
}

void Controller::LandR(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EHeld
		&& state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EHeld) return;

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EHeld) {
		timeKeeper[RIGHT]++;
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EReleased) {
		timeKeeper[RIGHT] = 1;
	}

	if (!isRight())
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EPressed) mino->addPosX(1);
		else if (timeKeeper[RIGHT] % 10 == 0) mino->addPosX(1);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EHeld) {
		timeKeeper[LEFT]++;
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EReleased) {
		timeKeeper[LEFT] = 1;
	}

	if (!isLeft())
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EPressed) mino->addPosX(-1);
		else if (timeKeeper[LEFT] % 10 == 0) mino->addPosX(-1);
	}
}

Keyboard::Keyboard()
	:RefInput()
{
}
Keyboard::Keyboard(Array* parray, Mino* pmino)
	:RefInput(parray, pmino)
{
}

Keyboard::Keyboard(const Keyboard& keyboard)
{
	*this = keyboard;
}

void Keyboard::refInput(const InputState& state)
{
	if (mino->getStatus() == STACKED) return;
	if (mino->flag.getGameover()) return;
	down(state);
	if (mino->getStatus() == STACKED) return;
	LandR(state);
	spin(state);
	hold(state);
}

void Keyboard::spin(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_F) == EPressed) {
		mino->flag.chaAddSpin(true);
	}
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_D) == EPressed) {
		mino->flag.chaSubSpin(true);
	}
}

void Keyboard::down(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_UP) == EPressed
		&& !isOn()) {
		mino->addPosY(bottom());
		mino->setStatus(STACKED);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EReleased) {
		mino->flag.chaDush(false);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_DOWN) == EPressed) {
		mino->flag.chaDush(true);
	}
}

void Keyboard::hold(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RSHIFT) == EPressed) {
		if (mino->flag.getHold() == SKIP) return;
		mino->flag.chaHold(GO);
	}
}

void Keyboard::LandR(const InputState& state)
{
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EHeld
		&& state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EHeld) return;

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EHeld) {
		timeKeeper[RIGHT]++;
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EReleased) {
		timeKeeper[RIGHT] = 1;
	}

	if (!isRight())
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_RIGHT) == EPressed) mino->addPosX(1);
		else if (timeKeeper[RIGHT] % 10 == 0) mino->addPosX(1);
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EHeld) {
		timeKeeper[LEFT]++;
	}

	if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EReleased) {
		timeKeeper[LEFT] = 1;
	}

	if (!isLeft())
	{
		if (state.Keyboard.GetKeyState(SDL_SCANCODE_LEFT) == EPressed) mino->addPosX(-1);
		else if (timeKeeper[LEFT] % 10 == 0) mino->addPosX(-1);
	}
}

//RefInput////
RefInput::RefInput()
	:timeKeeper{ 1,1 }
	, array(nullptr)
	, mino(nullptr)
{
}

RefInput::RefInput(Array* parray, Mino* pmino)
	:timeKeeper{ 1,1 }
	, array(parray)
	, mino(pmino)
{
}

RefInput::RefInput(const RefInput& refinput)
{
	*this = refinput;
}

bool RefInput::isRight()
{
	const int Rend = mino->getPos().x + 3;
	const int Lend = mino->getPos().x;

	for (int y = mino->getPos().y; y <= mino->getPos().y + 3; y++) {
		for (int x = Rend + 1; x >= Lend; x--) {
			if (sameStatus({ x,y })) {
				if (samePlayer({ x,y })) break;
			}
			if (array->getStatus({ x ,y }) == BLANK) continue;
			if (array->getStatus({ x, y }) == SHADOW) continue;
			if (!sameStatus({ x - 1, y })) continue;
			if (!samePlayer({ x - 1, y })) continue;
			return true;
		}
	}
	return false;
}

bool RefInput::isLeft()
{
	const int Rend = mino->getPos().x + 3;
	const int Lend = mino->getPos().x;

	for (int y = mino->getPos().y; y <= mino->getPos().y + 3; y++) {
		for (int x = Lend - 1; x <= Rend; x++) {
			if (sameStatus({ x,y })) {
				if (samePlayer({ x,y })) break;
			}
			if (array->getStatus({ x ,y }) == BLANK) continue;
			if (array->getStatus({ x, y }) == SHADOW) continue;
			if (!sameStatus({ x + 1, y })) continue;
			if (!samePlayer({ x + 1, y })) continue;
			return true;
		}
	}
	return false;
}

bool RefInput::isBelow()
{
	for (int x = mino->getPos().x; x <= mino->getPos().x + 3; x++) {
		for (int y = mino->getPos().y + 4; y >= mino->getPos().y; y--) {
			if (sameStatus({ x,y })) {
				if (samePlayer({ x,y })) break;
			}
			if (array->getStatus({ x,y }) == BLANK) continue;
			if (array->getStatus({ x,y }) == SHADOW) continue;
			if (sameStatus({ x, y - 1 }) && samePlayer({ x, y - 1 })) return true;
		}
	}
	return false;
}

int RefInput::minoBottom(int x)
{
	for (int y = mino->getPos().y + 3; y >= mino->getPos().y; y--) {
		Vector pos = { x,y };
		if (!sameStatus(pos)) continue;
		if (!samePlayer(pos))  continue;
		return y;
	}
	return -1;
}

int RefInput::blockTop(Vector pos)
{
	const int y_mini = pos.y;
	for (int y = y_mini; y < FieldSize::LINES; y++) {
		pos.y = y;
		if (array->getStatus(pos) == STACKED) return y;
	}
	return FieldSize::LINES + 1;
}

int RefInput::bottom()
{
	const int L_x = mino->getPos().x;
	const int R_x = L_x + 3;

	int mini = FieldSize::LINES - 1;

	for (int x = L_x; x <= R_x; x++) {
		int y = minoBottom(x);
		if (y == -1) continue;
		int difference = blockTop({ x,y }) - y;
		if (mini > difference) mini = difference;
	}
	return mini - 1;
}

bool RefInput::sameStatus(Vector pos)
{
	return array->getStatus(pos) == mino->getStatus();
}

bool RefInput::samePlayer(Vector pos)
{
	return array->getPlayer(pos) == mino->getPlayerNo();
}


bool RefInput::isOn()
{
	PLAYER_NO player = mino->getPlayerNo();
	int stacked = FieldSize::LINES;
	int other = FieldSize::LINES;
	for (int x = 0; x < 4; x++) {
		int x_ = x + mino->getPos().x;
		int y = minoBottom(x_) + 1;
		if (y == 0) continue;
		for (y; y < FieldSize::LINES; y++) {
			Vector pos = { x + mino->getPos().x , y };
			if (array->getPlayer(pos) == P0) continue;
			if (array->getStatus(pos) == STACKED) {
				if (stacked > y) stacked = y;
			}
			if (array->getPlayer(pos) != player) {
				if (other > y) other = y;
			}
		}
	}
	return stacked > other;
}

bool Update::update(MinoLists& minolists)
{
	if (mino->flag.getGameover()) return true;
	
	PLAYER_NO playerNo = mino->getPlayerNo();
	count++;
	shadow();
	hold(minolists);

	if (mino->getStatus() == STACKED) {
		minolists.change(playerNo);
		mino->init(playerNo, minolists.getMinoNo(playerNo, 0));
		count = 1;
		mino->flag.chaHold(PASS);
		if (isGameOver()) return false;
	}

	if (isStacked() && mino->getStatus() == FALLING) {
		count = 0;
		mino->setStatus(STACKING);
		adaptMino();
	}

	if (mino->getStatus() == STACKING && !isStacked()) {
		count = 0;
		mino->setStatus(FALLING);
		adaptMino();
	}

	if (mino->getStatus() == STACKING && count >= 60) {
		mino->setStatus(STACKED);
		adaptMino();
	}
	return true;
}

void Calculate::clearBlocks(PLAYER_NO player)
{
	for (int x = 0; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			Vector pos = { x,y };
			if (array->getPlayer(pos) == player) {
				clearBlock(pos);
			}
		}
	}
}

void Calculate::clearBlock(Vector pos)
{
	array->setColor(pos, NOTHING);
	array->setStatus(pos, BLANK);
	array->setPlayer(pos, P0);
}


Update::Update(Array* parray, Mino* pmino)
	: count(1)
	, array(parray)
	, mino(pmino)
{
}

void Update::shadow()
{
	Vector pos = mino->getPos();
	const int bottom_y = pos.y + bottom();

	COLOR_No ret[4][4] = { NOTHING };
	mino->retMino(ret);

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (ret[y][x] == NOTHING) continue;
			if (array->getStatus({ pos.x + x, bottom_y + y }) != BLANK) continue;
			array->setColor({ pos.x + x, bottom_y + y }, SHADOW_C);
			array->setStatus({ pos.x + x, bottom_y + y }, SHADOW);
			array->setPlayer({ pos.x + x, bottom_y + y }, P0);
		}
	}
}

int Update::minoBottom(int x)
{
	for (int y = mino->getPos().y + 3; y >= mino->getPos().y; y--) {
		Vector pos = { x, y };
		if (!sameStatus(pos)) continue;
		if (!samePlayer(pos))  continue;
		return y;
	}
	return -1;
}


int Update::shadowY(int x)
{
	if (isBelow()) return minoBottom(x) + 1;
	const int y_mini = minoBottom(x) + 1;
	for (int y = y_mini; y < FieldSize::LINES; y++) {
		Vector pos = { x, y };
		if (array->getStatus(pos) != BLANK) return y;
	}
	return FieldSize::LINES - 1;
}

int Update::getCount()
{
	return count;
}
void Update::addCount(int add)
{
	count += add;
}

void Update::resetCount()
{
	count = 1;
}

int Update::bottom()
{
	const int L_x = mino->getPos().x;
	const int R_x = L_x + 3;

	int mini = FieldSize::LINES - 1;

	for (int x = L_x; x <= R_x; x++) {
		int y = minoBottom(x);
		if (y == -1) continue;
		int difference = shadowY(x) - y;
		if (mini > difference) mini = difference;
	}
	return mini - 1;
}

void Update::clearMino()
{
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			Vector pos = { x + mino->getPos().x, y + mino->getPos().y };
			int status = array->getStatus(pos);
			if (status == STACKED) continue;
			if (samePlayer(pos) && sameStatus(pos)) {
				array->setColor(pos, NOTHING);
				array->setStatus(pos, BLANK);
				array->setPlayer(pos, P0);
			}
		}
	}
}

void Update::spin()
{
	Mino mino_(*mino);
	if (mino->flag.getAddSpin()
		&& mino->flag.getSubSpin()) {
		mino->flag.chaAddSpin(false);
		mino->flag.chaSubSpin(false);
		return;
	}
	else if (mino->flag.getAddSpin()) {
		mino->addSpin();
		mino->flag.chaAddSpin(false);
	}
	else if (mino->flag.getSubSpin()) {
		mino->subSpin();
		mino->flag.chaSubSpin(false);
	}

	if (!isOverlap()) return;
	mino->addPosX(1);
	if (!isOverlap()) return;
	mino->addPosX(-2);
	if (!isOverlap()) return;
	mino->addPosX(-1);
	if (!isOverlap()) return;
	*mino = mino_;
}

bool Update::isGameOver()
{
	return isOverlap();
}

bool Update::isOverlap()
{
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (mino->getArrayColor({ x,y }) == NOTHING) continue;
			Vector pos = { x + mino->getPos().x, y + mino->getPos().y };
			if (array->getStatus(pos) == STACKED)  return true;
			if (array->getPlayer(pos) == mino->getPlayerNo()) continue;
			if (array->getPlayer(pos) != P0) return true;
		}
	}
	return false;
}

void Update::fall()
{
	if (isBelow()) return;
	if (mino->getStatus() == STACKED) return;
	int interval = 60 - (mino->getSpeed() - 1) * 6;
	if (mino->flag.getDush()) {
		interval = 60 - 6 * 9;
	}
	if (interval <= 6) interval = 6;
	if (count % interval == 0) mino->addPosY(1);
}

bool Update::isBelow()
{
	for (int x = mino->getPos().x; x <= mino->getPos().x + 3; x++) {
		for (int y = mino->getPos().y + 4; y >= mino->getPos().y; y--) {
			if (array->getStatus({ x ,y }) == BLANK) continue;
			if (array->getStatus({ x, y }) == SHADOW) continue;
			if (sameStatus({ x,y }) && samePlayer({ x,y })) break;
			if (sameStatus({ x, y - 1 }) && samePlayer({ x, y - 1 })) return true;
		}
	}
	return false;
}

bool Update::sameStatus(Vector pos)
{
	return array->getStatus(pos) == mino->getStatus();
}

bool Update::samePlayer(Vector pos)
{
	return array->getPlayer(pos) == mino->getPlayerNo();
}

bool Update::isStacked()
{
	for (int x = mino->getPos().x; x < mino->getPos().x + 4; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			if (!samePlayer({ x,y })) continue;
			if (array->getStatus({ x,y }) != STACKED) {
				if (array->getStatus({ x,y + 1 }) == STACKED) return true;
			}
		}
	}
	return false;
}

void Update::pre()
{
	if (mino->getStatus() == STACKED) return;
	if (mino->flag.getGameover()) return;
	spin();
	mino->adaptArray(*array);
	fall();
	mino->adaptArray(*array);
}

void Update::hold(MinoLists& minolists)
{
	HOLDSTATUS status = mino->flag.getHold();
	if (status == PASS || status == SKIP) return;
	PLAYER_NO playerNo = mino->getPlayerNo();
	MINO_NO f_mino = minolists.getMinoNo(playerNo, 0);
	MINO_NO h_mino = minolists.getHoldMino(playerNo);
	if (h_mino == NONE) {
		minolists.setHoldMino(playerNo, f_mino);
		minolists.change(playerNo);
	}
	else {
		minolists.setHoldMino(playerNo, f_mino);
		minolists.setMino(playerNo, h_mino, 0);
	}
	mino->init(P1, minolists.getMinoNo(playerNo, 0));
	if (isOverlap()) {
		if (h_mino == NONE) {
			minolists.setHoldMino(playerNo, h_mino);
			for (int i = 4; i > 0; i--) {
				minolists.setMino(playerNo, minolists.getMinoNo(playerNo, i - 1), i);
			}
			minolists.setMino(playerNo, f_mino, 0);
		}
		else {
			minolists.setHoldMino(playerNo, h_mino);
			minolists.setMino(playerNo, f_mino, 0);
		}
		mino->init(P1, minolists.getMinoNo(playerNo, 0));
	}
	mino->flag.chaHold(SKIP);
}

COLOR_No Update::toBrack(MINO_NO mino)
{
	switch (mino)
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

COLOR_No Update::toWhite(MINO_NO mino)
{
	switch (mino)
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

COLOR_No Update::defColor()
{
	if (mino->getStatus() != STACKED) {
		return mino->getMinoColor(mino->getMinoNo());
	}
	switch (mino->getColor())
	{
	case BRACK:
		return toBrack(mino->getMinoNo());
		break;
	case WHITE:
		return toWhite(mino->getMinoNo());
		break;
	default:
		break;
	}
	return NOTHING;
}

void Update::adaptMino()
{
	COLOR_No ret[4][4] = { NOTHING };
	COLOR_No color = defColor();
	mino->retMino(ret);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (ret[y][x] == NOTHING) continue;
			Vector pos = { mino->getPos().x + x, mino->getPos().y + y };
			array->setColor(pos, color);
			array->setStatus(pos, mino->getStatus());
			array->setPlayer(pos, mino->getPlayerNo());
		}
	}
}

void Calculate::calculate(MinoLists& minolists, MoveBlocks& moveblocks)
{
	pre();
	clearBox();
	adaptMino();
	update(minolists, moveblocks);
}


void Calculate::pre()
{
	upd_1.pre();
	upd_2.pre();
}

void Calculate::adaptMino()
{
	if (!mino1->flag.getGameover()) upd_1.adaptMino();
	if (!mino2->flag.getGameover()) upd_2.adaptMino();
}

bool Calculate::update(MinoLists& minolists, MoveBlocks& moveblocks)
{
	if (!upd_1.update(minolists)) mino1->flag.chaGameover(true);
	if (!upd_2.update(minolists)) mino2->flag.chaGameover(true);

	if (mino1->flag.getGameover()) {
		upd_1.addCount(1);
		if (upd_1.getCount() >= 60 * 3) {
			mino1->flag.chaGameover(false);
			upd_1.resetCount();
			toMoveBlocks(P1, moveblocks, calcVertex(P1));
			clearBlocks(P1);
		}
	}

	if (mino2->flag.getGameover()) {
		upd_2.addCount(1);
		if (upd_2.getCount() >= 60 * 3) {
			mino2->flag.chaGameover(false);
			upd_2.resetCount();
			toMoveBlocks(P2, moveblocks, calcVertex(P2));
			clearBlocks(P2);
		}
	}

	calcSpeed();
	clearLine(moveblocks);
	return true;
}

void Calculate::toMoveBlocks(PLAYER_NO player, MoveBlocks& moveblocks, Vector vertex)
{
	for (int x = 1; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			if (array->getPlayer({ x,y }) != player) continue;
			moveblocks.add(array->getBlock({ x,y }), { x,y }, VANISH, vertex);
		}
	}
}

Vector Calculate::calcVertex(PLAYER_NO player)
{
	int retx = 0, num = 0;
	for (int x = 1; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			if (array->getPlayer({ x,y }) == player) {
				retx += x;
				num++;
			}
		}
	}
	return { retx / num, 0 };
}

void Calculate::calcSpeed()
{
	//int interval = 60 * 15;
	int interval = int(TIMELIMIT::t / 10);
	if (int(times->getSeconds()) % interval == 0) {
		int level1 = int(times->getSeconds()) / interval + 1;
		int level2 = level1;
		mino1->setSpeed(level1);
		mino2->setSpeed(level2);
	}
}

void Calculate::oneDown(int line)
{
	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
		for (int y = line; y > 0; y--) {
			Vector pos = { x,y };
			if (array->getStatus(pos) == FALLING)continue;
			if (array->getStatus(pos) == STACKING)continue;
			Vector pos2 = { x,y - 1 };
			array->setColor(pos, array->getColor(pos2));
			array->setStatus(pos, array->getStatus(pos2));
			array->setPlayer(pos, array->getPlayer(pos2));
		}
	}
}

bool Calculate::isOneLine(int y)
{
	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
		Vector pos = { x,y };
		if (array->getStatus(pos) != STACKED) return false;
	}
	return true;
}

//void Calculate::score(int y)
//{
//	for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
//		PLAYER_NO player = array->getPlayer({ x,y });
//		if (player == P1) times->addScore1(1);
//		else if (player == P2) times->addScore2(1);
//	}
//}

void Calculate::clearLine(MoveBlocks& moveblocks)
{
	for (int y = 0; y < FieldSize::LINES - 1; y++) {
		if (isOneLine(y)) {
			for (int x = 1; x < FieldSize::COLUMNS - 1; x++) {
				moveblocks.add(array->getBlock({ x,y }), { x,y }, TOSCORE);
			}
			array->chaClearLine(y, true);
			//score(y);
			oneDown(y);
			array->chaOneLine(y, false);
		}
	}
}

Calculate::Calculate(Array* parray, Mino* pmino1, Mino* pmino2, Times* ptimes)
	:array(parray)
	,mino1 (pmino1)
	,mino2 (pmino2)
	,upd_1(array, mino1)
	,upd_2(array, mino2)
	,times (ptimes)
{
}

void Calculate::clearBox()
{
	for (int x = 0; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			Vector pos = { x,y };
			int status = array->getStatus(pos);
			if (status != STACKED) {
				array->clearBlock(pos);
			}
		}
	}
}

void Update::clearBox()
{
	for (int x = 0; x < FieldSize::COLUMNS; x++) {
		for (int y = 0; y < FieldSize::LINES; y++) {
			Vector pos = { x,y };
			int status = array->getStatus(pos);
			if (status != STACKED) {
				array->clearBlock(pos);
			}
		}
	}
}

