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
	if (CUnit::mX - mRadius <= 0) // ���� ��
	{
		mX = mX + mSpeed * fElpsedTime;

		if (CUnit::mY - mRadius <= 0) // �� ��
		{
			mY = mY + mSpeed * fElpsedTime;
		}

		if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // �Ʒ� ��
		{
			mY = mY - mSpeed * fElpsedTime;
		}
	}

	else if (CUnit::mX + mRadius >= mpPGE->ScreenWidth()) // ������ ��
	{
		mX = mX - mSpeed * fElpsedTime;

		if (CUnit::mY - mRadius <= 0) // �� ��
		{
			mY = mY + mSpeed * fElpsedTime;
		}

		if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // �Ʒ� ��
		{
			mY = mY - mSpeed * fElpsedTime;
		}
	}

	else if (CUnit::mY - mRadius <= 0) // �� ��
	{
		mY = mY + mSpeed * fElpsedTime;
	}

	else if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // �Ʒ� ��
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
	// ������ ��迡 �ٴٸ��� �������� ������ �ٲ۴�.
	if (mX + mRadius >= mpPGE->ScreenWidth())
	{
		mDirX = -1.0f;
	}

	// ���� ��迡 �ٴٸ��� ���������� ������ �ٲ۴�.
	if (mX - mRadius <= 0.0f)
	{
		mDirX = 1.0f;
	}

	// ������ġX = (������ġX) + (����*ũ��*�����Ӵ�ð�) 
	mX = mX + mDirX * 50 * fElapsedTime;
}

void CUnit::BuildInfo(float fX, float fY, float fSpeed, int nRadius)
{
	mX = fX;
	mY = fY;
	mSpeed = fSpeed;
	mRadius = nRadius;	
}