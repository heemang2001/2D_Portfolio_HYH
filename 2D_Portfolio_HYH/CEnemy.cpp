#include "CEnemy.h"
#include "CBullet.h"
#include "CActor.h"

int CEnemy::m_nDeadEnemy = 0;
float CEnemy::fDirY_Plus = 10.0f;

void CEnemy::UpdateMoveLeft(float fElpsedTime)
{
	mX = mX - mSpeed * fElpsedTime;
}

void CEnemy::UpdateMoveRight(float fElpsedTime)
{
	mX = mX + mSpeed * fElpsedTime;
}

void CEnemy::UpdateMoveUp(float fElpsedTime)
{
	mY = mY - mSpeed * fElpsedTime;
}

void CEnemy::UpdateMoveDown(float fElpsedTime)
{
	mY = mY + mSpeed * fElpsedTime;
}

void CEnemy::Clipping(float fElpsedTime)
{
	if (CUnit::mY >= mpPGE->ScreenHeight()) // �Ʒ� ��
	{		
		{
			cout << "ENEMY clipping" << endl;
			m_IsClipping = true;
			mY = mY - mSpeed * fElpsedTime;
			cout << "���� Ŭ���� �Ҹ�" << endl;
			m_IsAliveEnemy = false;
			m_nDeadEnemy++;
			//DeathEnemy();			
		}
	}	
}

void CEnemy::DisplayMoveEnemy(olc::PixelGameEngine * tpDc)
{
	tpDc->DrawSprite(mX - mRadius -(mRadius/2), mY - 25, m_pEnemySprite[m_nEnemySpriteIndex], 2);
}

void CEnemy::DisplayMoveBoss(olc::PixelGameEngine * tpDc)
{
	tpDc->DrawSprite(mX-160, mY - 70, m_pEnemySprite[m_nEnemySpriteIndex], 2);
}

void CEnemy::DisplayExplosionEnemy(olc::PixelGameEngine * tpDc, float fElapsedtime)
{	
	// ���Ⱑ ���ߵǸ� ���� ��������Ʈ�� 0.03�ʸ��� ����̵� 
	if ((m_nEnemySpriteIndex > 0) && m_fTimeTick >= 0.03f)
	{
		tpDc->DrawSprite(mX - mRadius - (mRadius / 2), mY - 25, m_pEnemySprite[m_nEnemySpriteIndex], 2);

		// m_nEnemySpriteIndex 1~15�� ���� ��������Ʈ 16�� �Ǵ¼��� 0���� Ż��
		if (m_nEnemySpriteIndex < 15)
		{
			m_nEnemySpriteIndex++;
		}
		
		else
		{
			m_nEnemySpriteIndex = 0;
		}		

		m_fTimeTick = 0;
	}

	else if ((m_nEnemySpriteIndex > 0) && m_fTimeTick < 0.03f)
	{
		m_fTimeTick += fElapsedtime;
	}
}

void CEnemy::DoFire(CBullet CBullet[][100], CUnit * tpTarget, int nIndex)
{
	if (m_IsAliveEnemy == true)
	{		
		//cout << "DoFire (ENEMY)" << endl;

		// �߻� ���� ��ġ ����
		if (nullptr == CBullet) return;
		CBullet[nIndex][mCurIndexBullet].mX = this->mX;
		CBullet[nIndex][mCurIndexBullet].mY = this->mY;

		// ������ ������ ������.
		// ���� ���� = (�������� - ��������) ����ȭ
		// ������ ũ�⿡ ���� ���͸� ����
		float tDirX = tpTarget->mX - this->mX;
		float tDirY = tpTarget->mY - this->mY;

		// ������ ũ�⸦ ����
		float tMagnitude = std::sqrtf((tpTarget->mX - this->mX)*(tpTarget->mX - this->mX)
			+ (tpTarget->mY - this->mY)*(tpTarget->mY - this->mY));

		// ����ȭ (�ش� ������ ũ�⸦ 1�� �����)
		tDirX = tDirX / tMagnitude;
		tDirY = tDirY / tMagnitude;

		// źȯ�� ������ �����Ѵ�.
		CBullet[nIndex][mCurIndexBullet].DirX = tDirX;
		CBullet[nIndex][mCurIndexBullet].DirY = tDirY;

		// �߻�
		CBullet[nIndex][mCurIndexBullet].mIsAlive = true;

		if (mCurIndexBullet < BULLET_AMOUNT_BOSS - 1)
		{
			mCurIndexBullet++;
		}
		else
		{
			mCurIndexBullet = 0;
		}
	}	
}

void CEnemy::DoFire_Bossleft(CBullet CBullet[], CUnit * tpTarget)
{
	if (m_IsAliveEnemy == true)
	{
		//cout << "DoFire (BOSS)" << endl;

		// �߻� ���� ��ġ ����
		if (nullptr == CBullet) return;
		CBullet[mCurIndexBullet].mX = this->mX - 100;
		CBullet[mCurIndexBullet].mY = this->mY + 145;

		// ������ ������ ������.
		// ���� ���� = (�������� - ��������) ����ȭ
		// ������ ũ�⿡ ���� ���͸� ����
		float tDirX = tpTarget->mX - this->mX + 100;
		float tDirY = tpTarget->mY - this->mY - 145;

		// ������ ũ�⸦ ����
		float tMagnitude = std::sqrtf((tpTarget->mX - this->mX)*(tpTarget->mX - this->mX)
			+ (tpTarget->mY - this->mY)*(tpTarget->mY - this->mY));

		// ����ȭ (�ش� ������ ũ�⸦ 1�� �����)
		tDirX = tDirX / tMagnitude;
		tDirY = tDirY / tMagnitude;

		// źȯ�� ������ �����Ѵ�.
		CBullet[mCurIndexBullet].DirX = tDirX;
		CBullet[mCurIndexBullet].DirY = tDirY;

		// �߻�
		CBullet[mCurIndexBullet].mIsAlive = true;

		if (mCurIndexBullet < BULLET_AMOUNT_BOSS - 1)
		{
			mCurIndexBullet++;
		}
		else
		{
			mCurIndexBullet = 0;
		}
	}
}

void CEnemy::DoFire_Bossright(CBullet CBullet[], CUnit * tpTarget)
{
	if (m_IsAliveEnemy == true)
	{
		cout << "Dofire_Bossright" << endl;

		// �߻� ���� ��ġ ����
		if (nullptr == CBullet) return;
		CBullet[mCurIndexBullet].mX = this->mX + 100;
		CBullet[mCurIndexBullet].mY = this->mY + 145;

		// ������ ������ ������.		
		float fDirX = 1.0f * std::cosf(fDirY_Plus * (3.14159f / 180.0f));
		float fDirY = 1.0f * std::sinf(fDirY_Plus * (3.14159f / 180.0f));

		// 10���� ���ذ�
		fDirY_Plus = fDirY_Plus + 10.0f;

		// źȯ�� ������ �����Ѵ�.
		CBullet[mCurIndexBullet].DirX = fDirX;
		CBullet[mCurIndexBullet].DirY = fDirY;

		// �߻�
		CBullet[mCurIndexBullet].mIsAlive = true;

		if (mCurIndexBullet < BULLET_AMOUNT_BOSS - 1)
		{
			mCurIndexBullet++;
		}

		else
		{
			mCurIndexBullet = 0;			
		}
	}
}

void CEnemy::DoFireEx(CBullet CBullet[], CUnit * tpTarget)
{
	cout << "Do FireEX" << endl;
}

float CEnemy::GetTimeTick()
{
	return m_fTimeTick;
}

float CEnemy::GetTimeTick_2()
{
	return m_fTimeTick2;
}

bool CEnemy::GetIsAliveEnemy()
{
	return m_IsAliveEnemy;
}

bool CEnemy::GetIsClipping()
{
	return m_IsClipping;
}

int CEnemy::GetEnemyHP()
{
	return m_nEnemyHP;
}

int CEnemy::GetEnemyScore()
{
	return m_nEnemyScore;
}

int CEnemy::GetEnemyDamage()
{
	return m_nEnemyDamage;
}

int CEnemy::GetRandomItemValue()
{
	return m_nRandomItemValue;
}

int CEnemy::GetDeadEnemy()
{
	return m_nDeadEnemy;
}

void CEnemy::SetRandomItemValue(int nRandomItemValue)
{
	m_nRandomItemValue = nRandomItemValue;
}

void CEnemy::SetEnemyHP(int nEnemyHp)
{
	m_nEnemyHP = nEnemyHp;
}

void CEnemy::SetTimeTick(float ftimetick)
{
	m_fTimeTick = ftimetick;
}

void CEnemy::SetTimeTick_2(float ftimetick)
{
	m_fTimeTick2 = ftimetick;
}

void CEnemy::SetPGE(olc::PixelGameEngine * mpPge)
{
	mpPGE = mpPge;
}

void CEnemy::SetIsAliveEnemy(bool IsAliveEnemy)
{
	m_IsAliveEnemy = IsAliveEnemy;
}

void CEnemy::SetEnemyScore(int nEnemyScore)
{
	m_nEnemyScore = nEnemyScore;
}

void CEnemy::SetEnemyDamage(int nDamamge)
{
	m_nEnemyDamage = nDamamge;
}

void CEnemy::SetIsClipping(bool IsClipping)
{
	m_IsClipping = IsClipping;
}

void CEnemy::SetDeadEnemy(int nDeadEnemy)
{
	m_nDeadEnemy = nDeadEnemy;
}

void CEnemy::SetEnemySpriteIndex(int nEnemyspriteindex)
{
	m_nEnemySpriteIndex = nEnemyspriteindex;
}

void CEnemy::DeathBoss()
{
	cout << "���� �Ҹ�" << endl;
}

bool CEnemy::DeathEnemy()
{
	m_nEnemySpriteIndex++;
	cout << "���� �Ҹ�" << endl;
	m_IsAliveEnemy = false;
	m_nRandomItemValue = rand() % 10; // 0 ~ 9	

	return true;
}

void CEnemy::CreateEnemy(olc::Sprite *tpEnemySprites[])
{
	for (int i = 0; i < 50; i++)
	{
		m_pEnemySprite[i] = tpEnemySprites[i];
	}

	m_IsAliveEnemy = true;
}

void CEnemy::DestroyEnemy()
{
	for (int i = 0; i < 50; i++)
	{
		if (m_pEnemySprite[i] != nullptr)
		{
			delete m_pEnemySprite[i];
			m_pEnemySprite[i] = nullptr;
		}
	}
}

CEnemy::CEnemy()
{

}

CEnemy::~CEnemy()
{

}
