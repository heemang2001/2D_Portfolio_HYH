#pragma once

#include "olcPixelGameEngine.h"
#include "CUnit.h"

class CBullet; // 클래스 전방선언

class CActor : public CUnit
{
private:
	olc::Sprite *mpActorMoveSprite[7] = { nullptr };	
	int nActorMoveIndex = 3; // 초기 스프라이트 인덱스	
	int m_nActorDamage = 20;
	int m_nActorLife = 100;
	int m_nActorScore = 0;
	int m_nActorBulletPower = 0;
	bool m_IsActorAlive = true;

public:	
	virtual void BuildInfo(float fX, float fY, float fSpeed, int nRadius, int nActorLife);
	virtual void DoFire(CBullet CBullet[]) override;

	virtual void UpdateMoveLeft(float fElpsedTime) override;
	virtual void UpdateMoveRight(float fElpsedTime) override;
	virtual void UpdateMoveUp(float fElpsedTime) override;
	virtual void UpdateMoveDown(float fElpsedTime) override;

	int GetActorLife();	
	int GetActorDamage();
	int GetActorScore();
	int GetActorBulletPower();
	bool GetActorIsAlive();
	
	//void DisplayMoveActor(olc::PixelGameEngine *tpDc, olc::Sprite *mpActorMoveSprite, int nMoveIndex);
	void DisplayMoveActor(olc::PixelGameEngine *tpDc);
	void DisplayActorLife(olc::PixelGameEngine * tpDc);
	void SetActorLife(int nActorLife);
	void SetActorScore(int nScore);
	void SetActorIsAlive(bool IsAlive);
	void SetActorBulletPower(int nBulletPower);	
	void SetActorDamage(int nDamage);

	void CreateActor();
	void DestroyActor();

	CActor();
	~CActor();
};

