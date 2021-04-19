#pragma once

#include "olcPixelGameEngine.h"

class CScrollBg
{
	olc::PixelGameEngine *mpPGE = nullptr;

	float mScrollSpeed = 0.0f;

	olc::Sprite *mpSpriteA = nullptr;
	olc::Sprite *mpSpriteB = nullptr;	

	float mA_Y = 0.0f;
	float mB_Y = 0.0f;
	float mHeight = 0.0f;

	int nButton = 1;

	olc::Sprite *pSpriteTitleBG = new olc::Sprite("resources/Title_Bg2.png");
	olc::Sprite *pSpriteTitleSTRING = new olc::Sprite("resources/Title_String.png");
	olc::Sprite *pSpriteTitleButton[2]
		= { new olc::Sprite("resources/Title_Button_01.png"), new olc::Sprite("resources/Title_Button_02.png") };
	

public:
	void CreateR(float tScrollSpeed);
	void DestroyR();

	void UpdateR(float tDelta);
	void Display_Start_Bg();
	void Display_Game_Bg();

	void SetPGE(olc::PixelGameEngine *tpPGE);
};

