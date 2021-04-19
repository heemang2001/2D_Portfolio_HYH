#include "CBullet.h"
#include "CActor.h"
#include <time.h>

void CBullet::CreateBullet(olc::Sprite * pBulletSprites_Enemy[], olc::Sprite * pBulletSprites_Actor[])
{
	for (int i = 0; i < 5; i++)
	{
		m_pEnemyBulletSprite[i] = pBulletSprites_Enemy[i];
	}	

	for (int i = 0; i < AMOUNT_SPRITE_BULLET_ACTOR; i++)
	{
		m_pActorBulletSprite[i] = pBulletSprites_Actor[i];
	}	
}

void CBullet::DisplayBullet_Actor(olc::PixelGameEngine * tCircle, olc::Pixel op, CActor* CActor)
{
	if (true == mIsAlive)
	{		
		int nRandindex = rand() % 4; // 0 ~ 3
		int nActorPower = CActor->GetActorBulletPower();
		
		// 주인공의 파워에 따라 보여지는 총알이 다름
		switch (nActorPower)
		{
		case 0:
			CActor->SetActorDamage(20); // 데미지 20
			tCircle->DrawCircle(mX, mY, mRadius, op);
			tCircle->DrawSprite(mX - mRadius - 7.0f, mY - mRadius - 13.0f, m_pActorBulletSprite[nRandindex], 1);
			break;

		case 1:
			CActor->SetActorDamage(35); // 데미지 35
			nRandindex += 4; // 4 ~ 7
			tCircle->DrawCircle(mX, mY, mRadius + 2, op);
			tCircle->DrawSprite(mX - mRadius - 7.0f, mY - mRadius - 13.0f, m_pActorBulletSprite[nRandindex], 1);
			break;

		case 2:
			CActor->SetActorDamage(50); // 데미지 50
			nRandindex += 8; // 8 ~ 11
			tCircle->DrawCircle(mX, mY, mRadius + 4, op);
			tCircle->DrawSprite(mX - mRadius - 7.0f, mY - mRadius - 13.0f, m_pActorBulletSprite[nRandindex], 1);
			break;
		}		
	}
}

void CBullet::DisplayBullet_Enemy(olc::PixelGameEngine * tCircle, olc::Pixel op)
{
	if (true == mIsAlive )
	{
		tCircle->DrawCircle(mX, mY, mRadius, op);
		tCircle->DrawSprite(mX - mRadius - 1.0f, mY - mRadius, m_pEnemyBulletSprite[0], 1);
	}
}

void CBullet::DisplayBullet_Boss(olc::PixelGameEngine * tCircle, olc::Pixel op)
{
	if (true == mIsAlive)
	{
		tCircle->DrawCircle(mX, mY, mRadius, op);
		tCircle->DrawSprite(mX - mRadius - 1.0f, mY - mRadius, m_pEnemyBulletSprite[1], 1);
	}
}

void CBullet::UpdateMoveBullet(float fElpsedTime)
{
	if (true == mIsAlive)
	{
		//mY = mY - BULLET_SPEED * fElpsedTime;
		//mY = mY + mVelocity * fElpsedTime;

		mX = mX + DirX * mVelocity * fElpsedTime;
		mY = mY + DirY * mVelocity * fElpsedTime;

		// 총알 클리핑
		if (mY <= 5.0f)
		{
			cout << "clipping_upper" << endl;
			mIsAlive = false;
		}

		if (mY >= 800.0f)
		{
			cout << "clipping_bottom" << endl;
			mIsAlive = false;
		}

		if (mX <= 0.0f)
		{
			cout << "clipping_left" << endl;
			mIsAlive = false;
		}

		if (mX >= 480.0f)
		{
			cout << "clipping_right" << endl;
			mIsAlive = false;
		}
	}
}

void CBullet::DestroyBullet()
{
	for (int i = 0; i < 5; i++)
	{
		if (nullptr != m_pEnemyBulletSprite[i])
		{
			delete m_pEnemyBulletSprite[i];
			m_pEnemyBulletSprite[i] = nullptr;
		}
	}

	for (int i = 0; i < AMOUNT_SPRITE_BULLET_ACTOR; i++)
	{
		if (nullptr != m_pActorBulletSprite[i])
		{
			delete m_pActorBulletSprite[i];
			m_pActorBulletSprite[i] = nullptr;
		}
	}
}

CBullet::CBullet()
{

}

CBullet::~CBullet()
{

}