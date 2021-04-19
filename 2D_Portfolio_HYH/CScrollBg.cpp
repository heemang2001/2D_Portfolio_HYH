#include "CScrollBg.h"
//#include "olcPixelGameEngine.h"

void CScrollBg::CreateR(float tScrollSpeed)
{
	mpSpriteA = new olc::Sprite("resources/back01.png");
	mpSpriteB = new olc::Sprite("resources/back01.png");

	// 
	mA_Y = 0.0f;
	mB_Y = -800.0f;

	mHeight = 800.0f;

	mScrollSpeed = tScrollSpeed;
}

void CScrollBg::DestroyR()
{
	if (nullptr != mpSpriteA)
	{
		delete mpSpriteA;
		mpSpriteA = nullptr;
	}

	if (nullptr != mpSpriteB)
	{
		delete mpSpriteB;
		mpSpriteB = nullptr;
	}
}

void CScrollBg::UpdateR(float tDelta)
{
	// update
	mA_Y = mA_Y + mScrollSpeed * tDelta;
	mB_Y = mB_Y + mScrollSpeed * tDelta;

	// 스크롤 오차 보정이 더 필요하다.
	// 저글링
	if (mA_Y >= mHeight)
	{
		mA_Y = - mHeight + (mA_Y - mHeight);
	}

	if (mB_Y >= mHeight)
	{
		mB_Y = - mHeight + (mB_Y - mHeight);
	}
}

void CScrollBg::Display_Start_Bg()
{
	mpPGE->DrawSprite(0, mA_Y, mpSpriteA);
	mpPGE->DrawSprite(0, mB_Y, mpSpriteB);

	mpPGE->Clear(olc::BLACK);

	mpPGE->SetPixelMode(olc::Pixel::MASK);

	mpPGE->DrawSprite(-20, -40, pSpriteTitleBG, 2);
	mpPGE->DrawSprite(mpPGE->ScreenWidth() / 7, mpPGE->ScreenHeight() / 4, pSpriteTitleSTRING, 2);
	mpPGE->DrawString(mpPGE->ScreenWidth() / 3 - 5, mpPGE->ScreenHeight() / 2 + 170, "PRESS SPACE", olc::WHITE, 2);

	if (nButton <= 1)
	{
		mpPGE->DrawSprite(mpPGE->ScreenWidth() / 3, mpPGE->ScreenHeight() / 2 + 120, pSpriteTitleButton[0], 2);
		nButton++;
	}

	else if (nButton > 1)
	{
		mpPGE->DrawSprite(mpPGE->ScreenWidth() / 3 - 2, mpPGE->ScreenHeight() / 2 + 120, pSpriteTitleButton[1], 2);
		nButton--;
	}

	mpPGE->SetPixelMode(olc::Pixel::NORMAL);
}

void CScrollBg::Display_Game_Bg()
{
	mpPGE->DrawSprite(0, mA_Y, mpSpriteA);
	mpPGE->DrawSprite(0, mB_Y, mpSpriteB);
}

void CScrollBg::SetPGE(olc::PixelGameEngine * tpPGE)
{
	mpPGE = tpPGE;
}
