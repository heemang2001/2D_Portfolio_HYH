#include "CActor.h"
#include "CBullet.h"

void CActor::DoFire(CBullet CBullet[])
{
	cout << "Do Fire (CActor)" << endl;	

	// 발사 시작 위치 지정
	if (nullptr == CBullet) return;
	CBullet[mCurIndexBullet].mX = this->mX;
	CBullet[mCurIndexBullet].mY = this->mY - 50;

	// 발사
	CBullet[mCurIndexBullet].mIsAlive = true;

	CBullet[mCurIndexBullet].DirX = 0.0f;
	CBullet[mCurIndexBullet].DirY = -1.0f;

	if (mCurIndexBullet < 50 - 1)
	{
		mCurIndexBullet++;
	}

	else
	{
		mCurIndexBullet = 0;
	}

	//cout << "CActor BulletIndex : " << mCurIndexBullet << endl;
}

void CActor::DisplayMoveActor(olc::PixelGameEngine * tpDc)
{	
	tpDc->DrawSprite(mX - mRadius - 5.0f, mY - 50.0f, mpActorMoveSprite[nActorMoveIndex], 2);
}

void CActor::DisplayActorLife(olc::PixelGameEngine * tpDc)
{
	tpDc->DrawRect(50,50,125,7,olc::RED);

	switch (m_nActorLife)
	{
	case 100:
		tpDc->FillRect(50, 50, 125, 7, olc::RED);
		break;

	case 75:
		tpDc->FillRect(50, 50, 90, 7, olc::RED);
		break;

	case 50:
		tpDc->FillRect(50, 50, 60, 7, olc::RED);
		break;

	case 25:
		tpDc->FillRect(50, 50, 30, 7, olc::RED);
		break;

	case 0:
		tpDc->FillRect(50, 50, 0, 7, olc::RED);
		m_IsActorAlive = false;
		break;

	case -25:
		tpDc->FillRect(50, 50, 0, 7, olc::RED);
		m_IsActorAlive = false;
		break;
	}	
}

void CActor::SetActorLife(int nActorLife)
{
	m_nActorLife = nActorLife;
}

void CActor::SetActorScore(int nScore)
{
	m_nActorScore = nScore;
}

void CActor::SetActorIsAlive(bool IsAlive)
{
	m_IsActorAlive = IsAlive;
}

void CActor::SetActorBulletPower(int nBulletPower)
{
	m_nActorBulletPower = nBulletPower;
}

void CActor::SetActorDamage(int nDamage)
{
	m_nActorDamage = nDamage;
}

void CActor::CreateActor()
{
	mpActorMoveSprite[0] = new olc::Sprite("resources/test/tile000.png");
	mpActorMoveSprite[1] = new olc::Sprite("resources/test/tile002.png");
	mpActorMoveSprite[2] = new olc::Sprite("resources/test/tile004.png");
	mpActorMoveSprite[3] = new olc::Sprite("resources/test/tile006.png");
	mpActorMoveSprite[4] = new olc::Sprite("resources/test/tile008.png");
	mpActorMoveSprite[5] = new olc::Sprite("resources/test/tile010.png");
	mpActorMoveSprite[6] = new olc::Sprite("resources/test/tile012.png");
}

void CActor::DestroyActor()
{
	for (int i = 0; i < 7; i++)
	{
		if (nullptr != mpActorMoveSprite[i])
		{
			delete mpActorMoveSprite[i];
			mpActorMoveSprite[i] = nullptr;
		}
	}
}

void CActor::BuildInfo(float fX, float fY, float fSpeed, int nRadius, int nActorLife)
{
	mX = fX;
	mY = fY;
	mSpeed = fSpeed;
	mRadius = nRadius;
	m_nActorLife = nActorLife;
}

void CActor::UpdateMoveLeft(float fElpsedTime)
{
	mX = mX - mSpeed * fElpsedTime;

	if (nActorMoveIndex > 0)
	{
		//cout << "nActorMoveIndex = " << nActorMoveIndex << endl;
		nActorMoveIndex--;
	}	

	else
	{
		//cout << "nActorMoveIndex = " << nActorMoveIndex << endl;
		nActorMoveIndex = 0;
	}
}

void CActor::UpdateMoveRight(float fElpsedTime)
{
	mX = mX + mSpeed * fElpsedTime;

	if (nActorMoveIndex < 6)
	{
		//cout << "nActorMoveIndex = " << nActorMoveIndex << endl;
		nActorMoveIndex++;
	}	

	else
	{
		//cout << "nActorMoveIndex = " << nActorMoveIndex << endl;
		nActorMoveIndex = 6;
	}
}

void CActor::UpdateMoveUp(float fElpsedTime)
{
	mY = mY - mSpeed * fElpsedTime;
}

void CActor::UpdateMoveDown(float fElpsedTime)
{
	mY = mY + mSpeed * fElpsedTime;
}

int CActor::GetActorLife()
{
	return m_nActorLife;
}

int CActor::GetActorDamage()
{
	return m_nActorDamage;
}

int CActor::GetActorScore()
{
	return m_nActorScore;
}

int CActor::GetActorBulletPower()
{
	if (m_nActorBulletPower >= 2) { m_nActorBulletPower = 2; }

	return m_nActorBulletPower;
}

bool CActor::GetActorIsAlive()
{
	return m_IsActorAlive;
}

CActor::CActor()
{

}

CActor::~CActor()
{		

}