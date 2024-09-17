#include "draw.h"

DrawBackGround::DrawBackGround(int fieldwidth)
	:color(0)
{
	this->FIELDWIDTH = fieldwidth;
}

void DrawBackGround::drawLine(SDL_Renderer* Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 40, 70, 40, 255);
	for (int i = 0; i <= FieldSize::LINES; i++) {
		SDL_Rect field{
		FieldPos::X - FieldLength::LINETHICKNESS / 2,			// Top left x
		FieldPos::Y + i * BlockLength::HEIGHT - FieldLength::LINETHICKNESS / 2,			// Top left y
		FIELDWIDTH + FieldLength::LINETHICKNESS,		// Width
		FieldLength::LINETHICKNESS	// Height
		};
		SDL_RenderFillRect(Renderer, &field);
	}

	for (int i = 0; i <= FieldSize::COLUMNS; i++) {
		SDL_Rect field{
		FieldPos::X + i * BlockLength::WIDTH - FieldLength::LINETHICKNESS / 2,			// Top left x
		FieldPos::Y,			// Top left y
		FieldLength::LINETHICKNESS,		// Width
		FieldLength::HEIGHT	// Height
		};
		SDL_RenderFillRect(Renderer, &field);
	}
}

void DrawBackGround::drawBackWall(SDL_Renderer* Renderer)
{
	color.setColor(Renderer, FIELD);
	SDL_Rect field{
	FieldPos::X,			// Top left x
	FieldPos::Y,			// Top left y
	FIELDWIDTH,		// Width
	FieldLength::HEIGHT	// Height
	};
	SDL_RenderFillRect(Renderer, &field);
}

void DrawBackGround::drawBackGround(SDL_Renderer* Renderer)
{
	drawBackWall( Renderer);
	drawLine(Renderer);
}

DrawField::DrawField()
	:FIELDWIDTH(FieldLength::WIDTH)
	,DdrawBackGround(FIELDWIDTH)
{
}

void DrawField::drawField(SDL_Renderer* Renderer)
{
	DdrawBackGround.drawBackGround(Renderer);
}

DrawMino::DrawMino()
{
}

Vector DrawMino::defPos(Mino mino)
{
	int status = mino.getStatus();
	int pNo = mino.getPlayerNo();

	if (status == NEXT) {
		if (pNo == P1) return { NextPos1::X, NextPos1::Y };
		else           return { NextPos2::X, NextPos2::Y };
	}
	else if (status == HOLD) {
		if (pNo == P1) return { HoldPos1::X, HoldPos1::Y };
		else           return { HoldPos2::X, HoldPos2::Y };
	}
	return { 0,0 };
}

Vector DrawMino::changePoint(Vector pos)
{

	Vector ret;
	ret.x = pos.x * BlockLength::WIDTH + FieldPos::X;
	ret.y = pos.y * BlockLength::HEIGHT + FieldPos::Y;
	return ret;
}

void DrawMino::loopBlock(Vector pos, COLOR_No minoArray[4][4], SDL_Renderer* Renderer)
{
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			COLOR_No color = minoArray[y][x];
			if (color == NOTHING) continue;
			Vector pos_ = { pos.x + x * BlockLength::WIDTH, pos.y + y * BlockLength::HEIGHT };
			block.drawBlock(Renderer, pos_, color);
		}
	}
}

void DrawMino::draw(Vector pos, int MinoNo, SDL_Renderer* Renderer)
{
	switch (MinoNo)
	{
	case NONE:
		return;
		break;
	case I_MINO:
		loopBlock(pos, IMINO::array0, Renderer);
		return;
		break;
	case J_MINO:
		loopBlock(pos, JMINO::array0, Renderer);
		return;
		break;
	case L_MINO:
		loopBlock(pos, LMINO::array0, Renderer);
		return;
		break;
	case O_MINO:
		loopBlock(pos, OMINO::array0, Renderer);
		return;
		break;
	case S_MINO:
		loopBlock(pos, SMINO::array0, Renderer);
		return;
		break;
	case T_MINO:
		loopBlock(pos, TMINO::array0, Renderer);
		return;
		break;
	case Z_MINO:
		loopBlock(pos, ZMINO::array0, Renderer);
		return;
		break;
	default:
		break;
	}
}


DrawHold::DrawHold()
{
}

void DrawHold::drawBackGround(SDL_Renderer* Renderer)
{
	const int linethickness = 2;

	SDL_SetRenderDrawColor(Renderer, 70, 70, 70, 255);
	SDL_Rect hold1{
	HoldPos1::X,			// Top left x
	HoldPos1::Y,			// Top left y
	HoldLength::WIDTH,		// Width
	HoldLength::HEIGHT	// Height
	};
	SDL_RenderFillRect(Renderer, &hold1);

	SDL_Rect hold2{
	HoldPos2::X,			// Top left x
	HoldPos2::Y,			// Top left y
	HoldLength::WIDTH,		// Width
	HoldLength::HEIGHT	// Height
	};
	SDL_RenderFillRect(Renderer, &hold2);

	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	for (int i = 0; i <= 4; i++) {
		SDL_Rect hold{
		HoldPos1::X - linethickness / 2,			// Top left x
		HoldPos1::Y + i * BlockLength::HEIGHT - linethickness / 2,			// Top left y
		HoldLength::WIDTH + linethickness,		// Width
		linethickness	// Height
		};
		SDL_RenderFillRect(Renderer, &hold);
	}

	for (int i = 0; i <= 4; i++) {
		SDL_Rect hold{
		HoldPos2::X - linethickness / 2,			// Top left x
		HoldPos2::Y + i * BlockLength::HEIGHT - linethickness / 2,			// Top left y
		HoldLength::WIDTH + linethickness,		// Width
		linethickness	// Height
		};
		SDL_RenderFillRect(Renderer, &hold);
	}

	for (int i = 0; i <= 4; i++) {
		SDL_Rect hold1{
		HoldPos1::X + i * BlockLength::WIDTH - linethickness / 2,			// Top left x
		HoldPos1::Y,			// Top left y
		linethickness,		// Width
		HoldLength::HEIGHT	// Height
		};
		SDL_RenderFillRect(Renderer, &hold1);
		SDL_Rect hold2{
		HoldPos2::X + i * BlockLength::WIDTH - linethickness / 2,			// Top left x
		HoldPos2::Y,			// Top left y
		linethickness,		// Width
		HoldLength::HEIGHT	// Height
		};
		SDL_RenderFillRect(Renderer, &hold2);
	}
}

Vector DrawHold::defPos(PLAYER_NO playerNo)
{
	if (playerNo == P1) return { HoldPos1::X, HoldPos1::Y };
	else return { HoldPos2::X, HoldPos2::Y };
}

void DrawHold::draw(SDL_Renderer* Renderer, MinoLists& minolists)
{
	Vector pos1 = defPos(P1);
	drawMino.draw(pos1, minolists.getHoldMino(P1), Renderer);

	Vector pos2 = defPos(P2);
	drawMino.draw(pos2, minolists.getHoldMino(P2), Renderer);
}

DrawNext::DrawNext()
{
}

void DrawNext::drawBackGround(SDL_Renderer* Renderer)
{
	int linethickness = 2;


	//back
	SDL_SetRenderDrawColor(Renderer, 50, 50, 50, 255);
	SDL_Rect next1{
	NextPos1::X,			// Top left x
	NextPos1::Y,			// Top left y
	NextLength::WIDTH,		// Width
	NextLength::HEIGHT	// Height
	};
	SDL_RenderFillRect(Renderer, &next1);

	SDL_Rect next2{
	NextPos2::X,			// Top left x
	NextPos2::Y,			// Top left y
	NextLength::WIDTH,		// Width
	NextLength::HEIGHT	// Height
	};
	SDL_RenderFillRect(Renderer, &next2);

	//line
	SDL_SetRenderDrawColor(Renderer, 150, 150, 150, 255);
	for (int i = 0; i <= 4; i++) {
		linethickness = 2;
		if (i % 4 == 0) {
			linethickness = 4;
		};
		SDL_Rect next1{
		NextPos1::X + i * BlockLength::WIDTH - linethickness / 2,			// Top left x
		NextPos1::Y,			// Top left y
		linethickness,		// Width
		NextLength::HEIGHT	// Height
		};
		SDL_RenderFillRect(Renderer, &next1);
		SDL_Rect next2{
		NextPos2::X + i * BlockLength::WIDTH - linethickness / 2,			// Top left x
		NextPos2::Y,			// Top left y
		linethickness,		// Width
		NextLength::HEIGHT	// Height
		};
		SDL_RenderFillRect(Renderer, &next2);
	}

	for (int i = 0; i <= 4 * NextLength::NUM; i++) {
		linethickness = 2;
		if (i % 4 == 0) {
			linethickness = 4;
		};
		SDL_Rect next1{
		NextPos1::X - linethickness / 2,			// Top left x
		NextPos1::Y + i * BlockLength::HEIGHT - linethickness / 2,			// Top left y
		NextLength::WIDTH + linethickness,		// Width
		linethickness	// Height
		};
		SDL_RenderFillRect(Renderer, &next1);

		SDL_Rect next2{
		NextPos2::X - linethickness / 2,			// Top left x
		NextPos2::Y + i * BlockLength::HEIGHT - linethickness / 2,			// Top left y
		NextLength::WIDTH + linethickness,		// Width
		linethickness	// Height
		};

		SDL_RenderFillRect(Renderer, &next2);
	}
}

Vector DrawNext::defPos(PLAYER_NO playerNo)
{
	if (playerNo == P1) return { NextPos1::X, NextPos1::Y };
	else return { NextPos2::X, NextPos2::Y };
}

void DrawNext::draw(SDL_Renderer* Renderer, MinoLists& minolists)
{
	Vector pos1 = defPos(P1);
	for (int i = 1; i < NextLength::NUM + 1; i++) {
		drawMino.draw(pos1, minolists.getMinoNo(P1,i), Renderer);
		pos1.y += BlockLength::HEIGHT * 4;
	}

	Vector pos2 = defPos(P2);
	for (int i = 1; i < NextLength::NUM + 1; i++) {
		drawMino.draw(pos2, minolists.getMinoNo(P2,i), Renderer);
		pos2.y += BlockLength::HEIGHT * 4;
	}
}


DrawBack::DrawBack()
{
}

void DrawBack::draw(SDL_Renderer* Renderer)
{
	field.drawField(Renderer);
	hold.drawBackGround(Renderer);
	next.drawBackGround(Renderer);
}

GetUpdata::GetUpdata()
{
}

DrawBox::DrawBox()
{
}

void DrawBox::draw(Array& array, SDL_Renderer* Renderer)
{
	for (int x = 0; x < FieldSize::COLUMNS; x++)
	{
		for (int y = 0; y < FieldSize::LINES; y++)
		{
			Vector pos = { x, y };
			Vector coord = mino.changePoint(pos);
			block.drawBlock(Renderer, coord, array.getColor(pos));
		}
	}
}


Draw::Draw()
{
}

void Draw::all(SDL_Renderer* Renderer, Array& array,MinoLists& minolists)
{

	back.draw(Renderer);
	box.draw(array, Renderer);
	next.draw(Renderer, minolists);
	hold.draw(Renderer, minolists);
	
}