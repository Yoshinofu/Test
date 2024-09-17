#ifndef block_h_
#define block_h_

#include "SDL.h"
#include "constant.h"

class Block
{
private:
	STATUS mstatus;
	COLOR_No mcolor;
	PLAYER_NO mplayer;
	Point mpoint;
	Point mvertex;
	MOVESTATUS mmovestatus;
	int mt;
public:
	Block();
	Block(Block& block, Point point, MOVESTATUS movestatus);
	Block(Block& block, Point point, MOVESTATUS movestatus, Point vertex);
	STATUS getStatus() const;
	COLOR_No getColor() const;
	PLAYER_NO getPlayer() const;
	int getT() const;
	Point getPoint() const;
	MOVESTATUS getMoveStat() const;
	Block getBlock() const;
	Point getVertex() const;
	void addT(int add);
	void setPoint(Point point);
	void setStatus(STATUS status);
	void setColor(COLOR_No color);
	void setPlayer(PLAYER_NO player);
	void resetT();
	void setMoveStat(MOVESTATUS movestatus);
};


class Color
{
private:
	int depth;
public:
	Color(int dep);
	void brack(SDL_Renderer* Renderer)
	{
		SDL_SetRenderDrawColor(
			Renderer,
			20 + depth,		// R
			20 + depth,		// G 
			20 + depth,	// B
			255	// A
		);
	};
	void lightgreen(SDL_Renderer* Renderer)
	{
		SDL_SetRenderDrawColor(Renderer, 40 + depth, 80 + depth, 40 + depth, 255);
	};
	void red(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 200 + depth, 50 + depth, 50 + depth, 255);
	};
	void white(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 230 + depth, 230 + depth, 230 + depth, 255);
	};
	void shadow(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 100 + depth, 115 + depth, 100 + depth, 255);
	};
	void gray(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 130 + depth, 130 + depth, 130 + depth, 255);
	};
	void green(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 50 + depth, 255 + depth, 50 + depth, 255);
	}
	void brue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 50 + depth, 50 + depth, 255 + depth, 255);
	}
	void yellow(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 255 + depth, 255 + depth, 50 + depth, 255);
	}
	void purple(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 200 + depth, 50 + depth, 255 + depth, 255);
	}
	void orenge(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 200 + depth, 150+ depth, 50 + depth, 255);
	}
	void lightbrue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 150 + depth, 150 + depth, 255 + depth, 255);
	}

	void b_red(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 30 + depth, 20 + depth, 20 + depth, 255);
	};
	void b_green(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 20 + depth, 30 + depth, 20 + depth, 255);
	}
	void b_brue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 20 + depth, 20 + depth, 30 + depth, 255);
	}
	void b_yellow(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 30 + depth, 30 + depth, 20 + depth, 255);
	}
	void b_purple(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 30 + depth, 20 + depth, 30 + depth, 255);
	}
	void b_orenge(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 30 + depth, 30 + depth, 20 + depth, 255);
	}
	void b_lightbrue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 25 + depth, 25 + depth, 30 + depth, 255);
	}
	void w_red(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 250 + depth, 210 + depth, 210 + depth, 255);
	};
	void w_green(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 210 + depth, 250 + depth, 210 + depth, 255);
	}
	void w_brue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 210 + depth, 210 + depth, 250 + depth, 255);
	}
	void w_yellow(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 250 + depth, 250 + depth, 210 + depth, 255);
	}
	void w_purple(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 250 + depth, 210 + depth, 250 + depth, 255);
	}
	void w_orenge(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 250 + depth, 230 + depth, 210 + depth, 255);
	}
	void w_lightbrue(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 225 + depth, 225 + depth, 250 + depth, 255);
	}
	void field(SDL_Renderer* Renderer) {
		SDL_SetRenderDrawColor(Renderer, 60 + depth, 90 + depth, 60 + depth, 255);
	}
	void setColor(SDL_Renderer* Renderer, COLOR_No colorNo);
};


class DrawBlock
{
private:
	Color color;
	Color darkcolor;
public:
	DrawBlock();
	void drawBlock(SDL_Renderer* Renderer, Vector point, COLOR_No colorno);
	Vector changePoint(Vector pos);
};



#endif
