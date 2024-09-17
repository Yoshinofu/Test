#ifndef Game_h_
#define Game_h_

#include "SDL.h"
#include "SDL_image.h"
#include "draw.h"
#include "constant.h"
#include "font.h"
#include "block.h"
#include "mino.h"
#include "array.h"
#include "times.h"
#include "calculate.h"
#include "input.h"
#include "image.h"
#include "moveblock.h"
#include "ending.h"
#include "start.h"
#include "opening.h"

// Game class
class Game
{
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void resetGame();
	GAMESTATE gamestate = OPENING;

	WindowLength WINDOWLENGTH;
	WindowPos WINDOWPOS;

	// Window created by SDL
	SDL_Window* mWindow;
	// Renderer for 2D drawing
	SDL_Renderer* mRenderer;

	SDL_Surface* mSurface;
	SDL_Surface* mImage;
	TTF_Font* mFont;
	SDL_Texture* mTexture;
	SDL_Texture* mImTexture;


	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;

	Start start;
	Finish finish;
	Times times;
	Scores scores;
	
	MinoLists minolists;
	Array array;
	Mino mino1;
	Mino mino2;
	Calculate calu;
	Keyboard keyboard;
	Controller controller;
	MoveBlocks moveblocks;

	Draw draw;
	Image image;
	Times_Font times_font;
	GameFont gamefont;

	class InputSystem* mInputSystem;

	Opening opening;
	Ending ending;
};

#endif

