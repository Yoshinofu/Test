#pragma once
#include "SDL.h"
#include  "mino.h"
#include "array.h"

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState
{
public:
	// Friend so InputSystem can easily update it
	friend class InputSystem;
	// Get just the boolean true/false value of key
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// Get a state based on current and previous frame
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

class ControllerState
{
public:
	friend class InputSystem;

	// For buttons
	bool GetButtonValue(SDL_GameControllerButton button) const;
	ButtonState GetButtonState(SDL_GameControllerButton button) const;

	const Point& GetLeftStick() const { return mLeftStick; }
	const Point& GetRightStick() const { return mRightStick; }
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }

	bool GetIsConnected() const { return mIsConnected; }
private:
	// Current/previous buttons
	Uint8 mCurrButtons[SDL_CONTROLLER_BUTTON_MAX];
	Uint8 mPrevButtons[SDL_CONTROLLER_BUTTON_MAX];
	// Left/right sticks
	Point mLeftStick;
	Point mRightStick;
	// Left/right trigger
	float mLeftTrigger;
	float mRightTrigger;
	// Is this controller connected?
	bool mIsConnected;
};


// Wrapper that contains current state of input
struct InputState
{
	KeyboardState Keyboard;
	ControllerState Controller;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	// Called right before SDL_PollEvents loop
	void PrepareForUpdate();
	// Called after SDL_PollEvents loop
	void Update();
	// Called to process an SDL event in input system
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }

private:
	float Filter1D(int input);
	Point Filter2D(int inputX, int inputY);
	InputState mState;
	SDL_GameController* mController;
	SDL_Joystick* mJoystick;
};

