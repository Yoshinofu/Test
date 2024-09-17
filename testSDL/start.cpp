#include "start.h"

Start::Start(Times* ptimes)
	:times(ptimes)
	,font(nullptr)
	,texture(nullptr)
{
}
Start::~Start()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
}

void Start::draw(SDL_Surface* surface, SDL_Renderer* renderer)
{
	float count = 4 - times->getSeconds();
	if (count <= 0) {
		flag = true; 
		times->reset();
		return;
	}
	font = TTF_OpenFont("font.ttf", size);
	std::string str = std::to_string(int(count));
	surface = TTF_RenderUTF8_Blended(font, str.c_str(), { 255,255,255,255 });
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	int iw, ih;
	SDL_QueryTexture(texture, NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { WindowLength::WIDTH / 2 - iw / 2,
						   WindowLength::HEIGHT / 2 - ih / 2 ,iw,ih };
	SDL_RenderCopy(renderer, texture, &txtRect, &pasteRect);
}

void Start::reset()
{
	flag = false;
}

bool Start::isStart()
{
	return flag;
}


void Finish::init(SDL_Renderer* renderer, SDL_Surface* surface)
{
	int width = WindowLength::WIDTH;
	int height = WindowLength::HEIGHT;
	text[0] = { width / 3, height / 3}; //WIN
	text[1] = { width / 3 * 2, height / 3}; //LOSE
	text[2] = { width / 3, height / 4 * 3}; //PLAYER1
	text[3] = { width / 3 * 2, height / 4 * 3}; //PLAYER2
	text[4] = { width / 3, ( text[0].y + text[2].y ) / 2}; //SCORE1
	text[5] = { width / 3 * 2, text[4].y}; //SCORE2
 	text[6] = { width / 2, height / 3}; //DRAW
	text[7] = { width / 2, height / 2 }; //FINISH

	font = TTF_OpenFont("font.ttf", size);
	surface = TTF_RenderUTF8_Blended(font, "WIN", { 255,0,0,255 });
	texture[0] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderUTF8_Blended(font, "LOSE", { 0,0,255,255 });
	texture[1] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderUTF8_Blended(font, "DRAW", { 255,255,255,255 });
	texture[6] = SDL_CreateTextureFromSurface(renderer, surface);
	font = TTF_OpenFont("font.ttf", size - 50);
	surface = TTF_RenderUTF8_Blended(font, "PLAYER1", { 200,100,100,255 });
	texture[2] = SDL_CreateTextureFromSurface(renderer, surface);
	surface = TTF_RenderUTF8_Blended(font, "PLAYER2", { 100,100,200,255 });
	texture[3] = SDL_CreateTextureFromSurface(renderer, surface);
	font = TTF_OpenFont("font.ttf", size * 2);
	surface = TTF_RenderUTF8_Blended(font, "FINISH", { 255,255,255,255 });
	texture[7] = SDL_CreateTextureFromSurface(renderer, surface);
}

void Finish::draw(SDL_Surface* surface, SDL_Renderer* renderer, int num)
{
	if (*gamestate == FINISH) {
		if (drawFinish(renderer, num)) return;
		*gamestate = RESULT;
	}
	if (*gamestate != RESULT) return;
	if (t == 0) drawInit(surface, renderer);
	t++;
	image->back(renderer, 200);
	if (scores->winer() == P0) {
		for (int i = 2; i < 7; i++) {
			subDraw(renderer, i);
		}
		return;
	}
	for (int i = 0; i < 6; i++) {
		subDraw(renderer, i);
	}
}

void Finish::drawInit(SDL_Surface* surface, SDL_Renderer* renderer)
{
	font = TTF_OpenFont("font.ttf", size);
	std::string str = std::to_string(scores->getRemBlocks(P1));
	surface = TTF_RenderUTF8_Blended(font, str.c_str(), { 200,100,100,255 });
	texture[4] = SDL_CreateTextureFromSurface(renderer, surface);
	str = std::to_string(scores->getRemBlocks(P2));
	surface = TTF_RenderUTF8_Blended(font, str.c_str(), { 100,100,200,255 });
	texture[5] = SDL_CreateTextureFromSurface(renderer, surface);

	if (scores->winer() == P2) {
		text[1].x = WindowLength::WIDTH / 3; //LOSE
		text[0].x = WindowLength::WIDTH / 3 * 2; //WIN
	}
}

void Finish::subDraw(SDL_Renderer* renderer, int num)
{
	int iw, ih;
	SDL_QueryTexture(texture[num], NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { text[num].x - iw / 2, text[num].y - ih / 2, iw, ih};
	SDL_RenderCopy(renderer, texture[num], &txtRect, &pasteRect);
}

bool Finish::drawFinish(SDL_Renderer* renderer, int num)
{
	if (t >= 60) { t = 0; return false; }
	if (num == 0) t++;
	image->back(renderer, 100);
	int iw, ih;
	SDL_QueryTexture(texture[7], NULL, NULL, &iw, &ih);
	SDL_Rect txtRect = { 0,0,iw,ih };
	SDL_Rect pasteRect = { text[7].x - iw / 2, text[7].y- ih / 2,iw,ih};
	SDL_RenderCopy(renderer, texture[7], &txtRect, &pasteRect);
	return true;
}

bool Finish::input(const InputState& state)
{
	if (*gamestate != RESULT) return false;
	if (state.Keyboard.GetKeyState(SDL_SCANCODE_SPACE) == EPressed){
		*gamestate = OPENING;
		t = 0;
		return true;
	}
	return false;
}

Finish::Finish(Scores* pscores, Image* pimage, GAMESTATE* pgamestate)
	:scores(pscores)
	,image(pimage)
	,gamestate(pgamestate)
	,font(nullptr)
	,texture{ nullptr }
{
}

Finish::~Finish()
{
	TTF_CloseFont(font);
	for (int i = 0; i < 8; i++) {
		SDL_DestroyTexture(texture[i]);
	}
}