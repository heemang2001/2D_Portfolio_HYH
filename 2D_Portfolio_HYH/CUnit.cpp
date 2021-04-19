#include "CUnit.h"
#include "CBullet.h"
#include "olcPixelGameEngine.h"

void CUnit::DoFire(CBullet CBullet[])
{
	cout << "Do Fire (CUnit)" << endl;
}

void CUnit::DisplayCircle(olc::PixelGameEngine * tCircle)
{
	tCircle->DrawCircle(mX, mY, mRadius, olc::WHITE);	
}

void CUnit::Clipping(float fElpsedTime)
{
	if (CUnit::mX - mRadius <= 0) // 왼쪽 끝
	{
		mX = mX + mSpeed * fElpsedTime;

		if (CUnit::mY - mRadius <= 0) // 위 끝
		{
			mY = mY + mSpeed * fElpsedTime;
		}

		if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // 아래 끝
		{
			mY = mY - mSpeed * fElpsedTime;
		}
	}

	else if (CUnit::mX + mRadius >= mpPGE->ScreenWidth()) // 오른쪽 끝
	{
		mX = mX - mSpeed * fElpsedTime;

		if (CUnit::mY - mRadius <= 0) // 위 끝
		{
			mY = mY + mSpeed * fElpsedTime;
		}

		if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // 아래 끝
		{
			mY = mY - mSpeed * fElpsedTime;
		}
	}

	else if (CUnit::mY - mRadius <= 0) // 위 끝
	{
		mY = mY + mSpeed * fElpsedTime;
	}

	else if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // 아래 끝
	{
		mY = mY - mSpeed * fElpsedTime;
	}
}

void CUnit::SetPGE(olc::PixelGameEngine * mpPge)
{
	mpPGE = mpPge;
}

void CUnit::UpdateAI(float fElapsedTime)
{
	// 오른쪽 경계에 다다르면 왼쪽으로 방향을 바꾼다.
	if (mX + mRadius >= mpPGE->ScreenWidth())
	{
		mDirX = -1.0f;
	}

	// 왼쪽 경계에 다다르면 오른쪽으로 방향을 바꾼다.
	if (mX - mRadius <= 0.0f)
	{
		mDirX = 1.0f;
	}

	// 현재위치X = (이전위치X) + (방향*크기*프레임당시간) 
	mX = mX + mDirX * 50 * fElapsedTime;
}

void CUnit::BuildInfo(float fX, float fY, float fSpeed, int nRadius)
{
	mX = fX;
	mY = fY;
	mSpeed = fSpeed;
	mRadius = nRadius;	
}