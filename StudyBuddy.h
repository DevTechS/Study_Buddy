#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <math.h>
#include <algorithm>

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_image.h>

#include <chrono>
#include <thread>

#define PI 3.14159265
#define TaskbarHeight 30

using namespace std;

class StudyBuddy {
public:
	int desktopWidth = GetSystemMetrics(SM_CXSCREEN);
	int desktopHeight = GetSystemMetrics(SM_CYSCREEN);

	SDL_Event event;
	SDL_Window* window;
	SDL_Window* window2;
	SDL_Renderer* renderer;
	SDL_Renderer* renderer2;

	SDL_Texture* face;
	SDL_Texture* eye;
	SDL_Texture* eyeH;
	SDL_Texture* eyeC;
	SDL_Texture* mouth;
	SDL_Texture* mouthT;
	SDL_Texture* mouthS;
	SDL_Texture* body;
	SDL_Texture* pawDown;
	SDL_Texture* pawUp;
	SDL_Texture* tail;
	SDL_Texture* alarmclock;
	SDL_Texture* timerWindow;
	SDL_Texture* digits[10];

	int HeadSize = 250;
	int BodyW = round(HeadSize * 1100 / 700);
	int BodyH = round(HeadSize * 483 / 700);
	int TailW = round(HeadSize * 117 / 700);
	int TailH = round(HeadSize * 181 / 700);
	int EyeSize = round(HeadSize * 62.0 / 700);
	int mouthW = round(HeadSize * 184.0 / 700);
	int mouthH = round(HeadSize * 178.0 / 700);
	int PawW = round(HeadSize * 202 / 700);
	int PawH = round(HeadSize * 188 / 700);
	int ClockW = 176;
	int ClockH = 216;

	double BodyX_V = desktopWidth + 450;
	double BodyY_V = desktopHeight - 150 - TaskbarHeight;
	double BodyOffsetX_V = 0;
	double BodyOffsetY_V = 0;
	double BodyT_V = 0;

	double TailOffsetX_V = 0;
	double TailOffsetY_V = 0;
	double TailT_V = 0;

	double HeadOffsetX_V = 0;
	double HeadOffsetY_V = 0;
	double HeadT_V = 0;

	double EyeOffsetX_V = 0;
	double EyeOffsetY_V = 0;

	double MouthOffsetX_V = 0;
	double MouthOffsetY_V = 0;

	double Paw0OffsetX_V = 0;
	double Paw0OffsetY_V = 0;
	double Paw0T_V = 0;

	double Paw1OffsetX_V = 0;
	double Paw1OffsetY_V = 0;
	double Paw1T_V = 0;

	double Paw2OffsetX_V = 0;
	double Paw2OffsetY_V = 0;
	double Paw2T_V = 0;

	double Paw3OffsetX_V = 0;
	double Paw3OffsetY_V = 0;
	double Paw3T_V = 0;

	double ClockX_V = desktopWidth + 50;
	double ClockY_V = desktopHeight - 213 - TaskbarHeight;
	double ClockT_V = 0;

	double BodyX = desktopWidth + 450;
	double BodyY = desktopHeight - 150 - TaskbarHeight;
	double BodyOffsetX = 0;
	double BodyOffsetY = 0;
	double BodyT = 0;

	double TailOffsetX = 0;
	double TailOffsetY = 0;
	double TailT = 0;

	double HeadOffsetX = 0;
	double HeadOffsetY = 0;
	double HeadT = 0;

	double EyeOffsetX = 0;
	double EyeOffsetY = 0;

	double MouthOffsetX = 0;
	double MouthOffsetY = 0;

	double Paw0OffsetX = 0;
	double Paw0OffsetY = 0;
	double Paw0T = 0;

	double Paw1OffsetX = 0;
	double Paw1OffsetY = 0;
	double Paw1T = 0;

	double Paw2OffsetX = 0;
	double Paw2OffsetY = 0;
	double Paw2T = 0;

	double Paw3OffsetX = 0;
	double Paw3OffsetY = 0;
	double Paw3T = 0;

	double ClockX = desktopWidth + 50;
	double ClockY = desktopHeight - 213 - TaskbarHeight;
	double ClockT = 0;

	double TimerWindowW = 848;
	double TimerWindowH = 388;
	double TimerWindowX = desktopWidth - 1600;
	double TimerWindowY = desktopHeight - 550 - TaskbarHeight;

	bool ShowTimerWindow = 0;

	int Hours = 0;
	int Minutes = 0;
	int ButtonTimer = 0;

	int InactivityTimer = 0;

	POINT mouse;
	POINT Oldmouse;
	bool mousePressed = 0;

	double HeadX = 0;
	double HeadY = 0;

	int EyeState = 0; // 0-Default, 1-Happy
	int Paw0State = 0; // 0-Down, 1-Up
	int Paw1State = 0;
	int Paw2State = 0;
	int Paw3State = 0;
	int MouthState = 0; // 0-happy, 1-toung, 2-sad

	int Tick = 0;
	int AnimationTick = 0;
	int Trick = 0;

	int BlinkTimer = 240;

	bool fidgeting = 0;

	double PetCounter = 0;
	double PetLevel = 0;
	double TrickCounter = 0;

	int Stage = 0;

	bool clickingClock = 0;
	bool clickingTimerWindow = 0;

	std::chrono::system_clock::time_point TimerStartTime;

	bool MakeWindowTransparent(SDL_Window* window, COLORREF colorKey);

	bool MakeWindowTransparentAlpha(SDL_Window* window, COLORREF colorKey, short A);

	void renderLoop();

	void UpdatePos();

	void Idle();
	void Petting();
	void Wave();
	void Scratch();
	void Sleepy();
	void Playful();
	void Jump();
	void PushClock();
	void PullClock();
	void Walk();
	void WalkBack();

	int StartBuddy();
private:
};