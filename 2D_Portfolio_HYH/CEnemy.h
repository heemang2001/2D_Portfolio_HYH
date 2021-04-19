#pragma once

#include "olcPixelGameEngine.h"
#include "CUnit.h"

#define BULLET_AMOUNT_BOSS 100
#define BULLET_ANGLE_ENEMY 1
#define BULLET_BOSS_ANGLE 5.0f

class CBullet;
class CActor;
class CItem;

class CEnemy : public CUnit
{
private:	
	olc::PixelGameEngine *mpPGE = nullptr;
	olc::Sprite *m_pEnemySprite[50] = { nullptr };

	int m_nEnemyHP = 100;	
	int m_nEnemySpriteIndex = 0;	
	int m_nEnemyScore = 100;	
	int m_nEnemyDamage = 25;	
	int m_nRandomItemValue = -1;
	int m_nAngleBullet = 0;
	static int m_nDeadEnemy;

	float m_fAngleDgree = 0.0f;
	float m_fTimeTick = 0.0f;
	float m_fTimeTick2 = 0.0f;	
	static float fDirY_Plus;

	bool m_IsClipping = false;
	bool m_IsAliveEnemy = false;
	

public:		
	virtual void UpdateMoveLeft(float fElpsedTime) override;
	virtual void UpdateMoveRight(float fElpsedTime) override;
	virtual void UpdateMoveUp(float fElpsedTime) override;
	virtual void UpdateMoveDown(float fElpsedTime) override;

	virtual void Clipping(float fElpsedTime) override;

	void DisplayMoveEnemy(olc::PixelGameEngine *tpDc);
	void DisplayMoveBoss(olc::PixelGameEngine * tpDc);
	void DisplayExplosionEnemy(olc::PixelGameEngine *tpDc, float fElapsedtime);

	void DoFire(CBullet CBullet[][100], CUnit * tpTarget, int nIndex);
	void DoFire_Bossleft(CBullet CBullet[], CUnit * tpTarget);
	void DoFire_Bossright(CBullet CBullet[], CUnit * tpTarget);
	void DoFireEx(CBullet CBullet[], CUnit *tpTarget);

	float GetTimeTick();
	float GetTimeTick_2();
	bool GetIsAliveEnemy();
	bool GetIsClipping();
	int GetEnemyHP();
	int GetEnemyScore();
	int GetEnemyDamage();
	int GetRandomItemValue();
	int GetDeadEnemy();

	void SetRandomItemValue(int nRandomItemValue);
	void SetEnemyHP(int nEnemyHp);
	void SetTimeTick(float ftimetick);
	void SetTimeTick_2(float ftimetick);
	void SetPGE(olc::PixelGameEngine *mpPge);
	void SetIsAliveEnemy(bool IsAliveEnemy);
	void SetEnemyScore(int nEnemyScore);
	void SetEnemyDamage(int nDamamge);
	void SetIsClipping(bool IsClipping);
	void SetDeadEnemy(int nDeadEnemy);
	void SetEnemySpriteIndex(int nEnemyspriteindex);

	bool DeathEnemy();
	void DeathBoss();
	void CreateEnemy(olc::Sprite *tpEnemySprites[]);
	void DestroyEnemy();
	   
	CEnemy();
	~CEnemy();
};

