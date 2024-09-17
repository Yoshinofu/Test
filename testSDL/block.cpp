#include "block.h"


STATUS Block::getStatus() const
{
	return mstatus;
}
MOVESTATUS Block::getMoveStat() const
{
	return mmovestatus;
}
COLOR_No Block::getColor() const
{
	return mcolor;
}
PLAYER_NO Block::getPlayer() const
{
	return mplayer;
}
Block Block::getBlock() const
{
	return *this;
}
Point Block::getVertex() const
{
	return mvertex;
}

void Block::setStatus(STATUS status)
{
	mstatus = status;
}
void Block::setColor(COLOR_No color)
{
	mcolor = color;
}
void Block::setPlayer(PLAYER_NO player)
{
	mplayer = player;
}
void Block::setMoveStat(MOVESTATUS movestatus)
{
	mmovestatus = movestatus;
}
int Block::getT() const
{
	return mt;
}
Point Block::getPoint() const
{
	return mpoint;
}
void Block::addT(int add)
{
	mt += add;
}
void Block::setPoint(Point point)
{
	mpoint = point;
}

void Block::resetT()
{
	mt = 0;
}

Block::Block(Block& block, Point point, MOVESTATUS movestatus)
{
	*this = block;
	mpoint = point;
	mmovestatus = movestatus;
}

Block::Block(Block& block, Point point, MOVESTATUS movestatus, Point vertex)
{
	*this = block;
	mpoint = point;
	mmovestatus = movestatus;
	mvertex = vertex;
}

Block::Block()
	: mstatus(BLANK)
	, mcolor(BRACK)
	, mplayer(P0)
	, mt(0)
	, mpoint{ 0,0 }
	, mmovestatus(TOSCORE)
	, mvertex{ 0,0 }
{
}

















Color::Color(int dep)
	:depth(dep)
{
}

void Color::setColor(SDL_Renderer* Renderer, COLOR_No colorNo)
{
	switch (colorNo)
	{
	case BRACK:
		brack(Renderer);
		break;
	case WHITE:
		white(Renderer);
		break;
	case GRAY:
		gray(Renderer);
		break;
	case RED:
		red(Renderer);
		break;
	case BRUE:
		brue(Renderer);
		break;
	case GREEN:
		green(Renderer);
		break;
	case LIGHTGREEN:
		lightgreen(Renderer);
		break;
	case YELLOW:
		yellow(Renderer);
		break;
	case PURPLE:
		purple(Renderer);
		break;
	case ORENGE:
		orenge(Renderer);
		break;
	case LIGHTBRUE:
		lightbrue(Renderer);
		break;
	case B_RED:
		b_red(Renderer);
		break;
	case B_BRUE:
		b_brue(Renderer);
		break;
	case B_GREEN:
		b_green(Renderer);
		break;
	case B_YELLOW:
		b_yellow(Renderer);
		break;
	case B_PURPLE:
		b_purple(Renderer);
		break;
	case B_ORENGE:
		b_orenge(Renderer);
		break;
	case B_LIGHTBRUE:
		b_lightbrue(Renderer);
		break;
	case W_RED:
		w_red(Renderer);
		break;
	case W_BRUE:
		w_brue(Renderer);
		break;
	case W_GREEN:
		w_green(Renderer);
		break;
	case W_YELLOW:
		w_yellow(Renderer);
		break;
	case W_PURPLE:
		w_purple(Renderer);
		break;
	case W_ORENGE:
		w_orenge(Renderer);
		break;
	case W_LIGHTBRUE:
		w_lightbrue(Renderer);
		break;
	case SHADOW_C:
		shadow(Renderer);
		break;
	case FIELD:
		field(Renderer);
		break;
	default:
		break;
	}
}

DrawBlock::DrawBlock()
	:color(0),
	darkcolor(-20)
{
}

Vector DrawBlock::changePoint(Vector pos)
{
	Vector ret;
	ret.x = pos.x * BlockLength::WIDTH + FieldPos::X;
	ret.y = pos.y * BlockLength::HEIGHT + FieldPos::Y;
	return ret;
}

void DrawBlock::drawBlock(SDL_Renderer* Renderer, Vector point, COLOR_No colorNo)
{
	if (colorNo == NOTHING) return;
	SDL_Rect block{
	point.x,			// Top left x
	point.y,			// Top left y
	BlockLength::WIDTH,		// Width
	BlockLength::HEIGHT	// Height
	};
	darkcolor.setColor(Renderer, colorNo);
	SDL_RenderFillRect(Renderer, &block);
	SDL_Rect block1{
	point.x + 1,			// Top left x
	point.y + 1,			// Top left y
	BlockLength::WIDTH - 2,		// Width
	BlockLength::HEIGHT - 2	// Height
	};
	color.setColor(Renderer, colorNo);
	SDL_RenderFillRect(Renderer, &block1);
}



