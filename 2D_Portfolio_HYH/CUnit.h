#pragma once

#include "olcPixelGameEngine.h"
#include <iostream>
using namespace std;

class CPortfolio2D;
class CBullet;

class CUnit
{
	olc::PixelGameEngine *mpPGE = nullptr;	

public:
	float mX = -1.0f;
	float mY = -1.0f;

	float mDirX = 1.0f;
	float mDirY = 1.0f;

	float mSpeed = 0.0f;

	//float mRadius_ = 0.0f;

	bool mIsAlive = false;

	float mVelocity = 0.0f;

	int mCurIndexBullet = 0; // 총알배열 인덱스

	// 충돌 검출용 원의 반지름
	float mRadius = 0.0f;

public:
	virtual void BuildInfo(float fX, float fY, float fSpeed, int nRadius);
	virtual void DoFire(CBullet CBullet[]);
	//void Display(CPortfolio2D* tCircle);
	void DisplayCircle(olc::PixelGameEngine * tCircle);
	virtual void Clipping(float fElpsedTime);
	void SetPGE(olc::PixelGameEngine *mpPge);
	void UpdateAI(float fElapsedTime);	

	virtual void UpdateMoveLeft(float fElpsedTime) = 0;
	virtual void UpdateMoveRight(float fElpsedTime) = 0;
	virtual void UpdateMoveUp(float fElpsedTime) = 0;
	virtual void UpdateMoveDown(float fElpsedTime) = 0;
};

