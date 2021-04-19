#pragma once

#include <iostream>
using namespace std;

#include "olcPixelGameEngine.h"

#define AMOUNT_SPRITE_BULLET_ACTOR 15

class CActor;

class CBullet
{
private:
	olc::Sprite *m_pEnemyBulletSprite[5] = { nullptr };
	olc::Sprite *m_pActorBulletSprite[AMOUNT_SPRITE_BULLET_ACTOR] = { nullptr };

	

public:
	float mX = 0;
	float mY = 0;

	float DirX = 0.0f;
	float DirY = 0.0f;

	float mVelocity = 0.0f;

	bool mIsAlive = false;

	// 충돌 검출용 원의 반지름
	float mRadius = 0.0f;

public:
	//void DisplayBullet_Actor01(olc::PixelGameEngine * tCircle, olc::Pixel op);
	void CreateBullet(olc::Sprite * pBulletSprites_Enemy[], olc::Sprite * pBulletSprites_Actor[]);
	void DisplayBullet_Actor(olc::PixelGameEngine * tCircle, olc::Pixel, CActor* CActor);
	void DisplayBullet_Enemy(olc::PixelGameEngine * tCircle, olc::Pixel);
	void DisplayBullet_Boss(olc::PixelGameEngine * tCircle, olc::Pixel);
	void UpdateMoveBullet(float fElpsedTime);
	void DestroyBullet();

	CBullet();
	~CBullet();
};

