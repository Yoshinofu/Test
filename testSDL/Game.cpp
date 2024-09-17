#include "Game.h"

Game::Game()
	: mWindow(nullptr)
	, mRenderer(nullptr)
	, mFont(nullptr)
	, mSurface(nullptr)
	, mTexture{nullptr}
	, mImage(nullptr)
	, mImTexture(nullptr)
	, mTicksCount(0)
	, mIsRunning(true)
	, array()
	, times()
	, times_font(mSurface, mFont, mTexture, &times)
	, image(mImage, mImTexture)
	, mino1(P1)
	, mino2(P2)
	, calu(&array, &mino1, &mino2, &times)
	, minolists(P1,P2)
	, keyboard(&array, &mino2)
	, controller(&array, &mino1)
	, mInputSystem()
	, moveblocks()
	, ending()
	, start(&times)
	, finish(&scores, &image, &gamestate)
{
}

bool Game::Initialize()
{
	//óêêîèâä˙í≤êÆ
	srand(int(time(NULL)));
	for (int i = 0; i < 10; i++) {
		int a = rand();
	}

	//ÉQÅ[ÉÄèâä˙âª
	resetGame();

	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	int ttfResult = TTF_Init();
	if (sdlResult != 0 || ttfResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game", // Window title
		WINDOWPOS.X,	// Top left x-coordinate of window
		WINDOWPOS.Y,	// Top left y-coordinate of window
		WINDOWLENGTH.WIDTH,	// Width of window
		WINDOWLENGTH.HEIGHT,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Initialize input system
	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	//// Create SDL renderer
	mRenderer = SDL_CreateRenderer(
		mWindow, // Window to create renderer for
		-1,		 // Usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	gamefont.init(mRenderer, mSurface);
	image.backInit(mRenderer);
	opening.init(mRenderer, mSurface);
	finish.init(mRenderer, mSurface);


	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	mInputSystem->PrepareForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mIsRunning = false;
			break;
		default:
			break;
		}
	}

	mInputSystem->Update();
	const InputState& state = mInputSystem->GetState();


	// If escape is pressed, also end loop
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_ESCAPE)
		== EPressed){
		mIsRunning = false;
	}

	if (opening.input(state)) return;
	if (finish.input(state)) { resetGame(); return; }

	// UpdateInput
	if (!start.isStart()) return;
	if (gamestate == FINISH) return;
	if (gamestate == ENDING) return;
	if (gamestate == RESULT) return;


	if (!mino1.flag.getGameover()) {
		controller.refInput(state);
		mino1.adaptArray(array);
	}
	if (!mino2.flag.getGameover()) {
		keyboard.refInput(state);
		mino2.adaptArray(array);
	}
}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f){
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	if (gamestate == ENDING) return;
	if (gamestate == RESULT) return;
	if (gamestate == FINISH) return;
	if (gamestate == OPENING)return;

	times.update(deltaTime, start.isStart());
	if (!start.isStart()) return;

	times.update(deltaTime);
	//UpdateGame
	if (times.TimeLimit() && gamestate != FINISH) {
		moveblocks.addAllStacked(array);
		array.clearStacked();
		ending.setflag(true);
		gamestate = FINISH;
		return;
	}

	calu.calculate(minolists, moveblocks);
}

void Game::GenerateOutput()
{
	if (gamestate == OPENING) {
		gamestate = opening.draw(mRenderer);
		return;
	}

	// Set draw color
	SDL_SetRenderDrawColor(mRenderer, 30, 30, 30, 255);
	SDL_RenderClear(mRenderer);

	//Make back buffer
	draw.all(mRenderer, array, minolists);
	gamefont.draw(mRenderer);

	finish.draw(mSurface, mRenderer, int(moveblocks.getSize()));
	
	if (gamestate != RESULT) {
		moveblocks.draw(mRenderer, scores);
		times_font.draw(mRenderer, scores);
	}

	if (!start.isStart()) {
		image.back(mRenderer, 200);
		start.draw(mSurface, mRenderer);
	}

	// Swap front buffer and back buffer
	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown()
{
	mInputSystem->Shutdown();
	delete mInputSystem;

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	SDL_FreeSurface(mSurface);
	SDL_FreeSurface(mImage);
	SDL_DestroyTexture(mTexture);
	
	SDL_DestroyTexture(mImTexture);
	TTF_CloseFont(mFont);

	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}


//sub

void Game::resetGame()
{
	//èâä˙âª
	array.init();
	minolists.init();
	mino1.init(P1, minolists.getMinoNo(P1, 0));
	mino2.init(P2, minolists.getMinoNo(P2, 0));

	//êFåàíË
	COLOR_No P1color = COLOR_No(int(time(NULL)) % 2 + 1);
	COLOR_No P2color = COLOR_No(3 - P1color);
	array.setPlayerColor(P1, P1color);
	mino1.setColor(array.getPlayerColor(P1));
	mino1.adaptArray(array);
	array.setPlayerColor(P2, P2color);
	mino2.setColor(array.getPlayerColor(P2));
	mino2.adaptArray(array);
	moveblocks.init(P1color, P2color);
	times.reset();
	scores.reset();
	start.reset();
	opening.reset();
}