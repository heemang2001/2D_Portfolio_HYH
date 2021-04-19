#pragma once

#include "CUnit.h"

class CItem : public CUnit
{
private:
	olc::PixelGameEngine *mpPGE = nullptr;
	olc::Sprite *m_pItemSprite[20] = { nullptr };
	
	int m_nItemSpriteIndex = 0;
	bool m_IsClipingItem = false;
	bool m_IsCollipse = false;
	bool m_IsMoving = false;
	//bool m_IsItemAlive = false;

public:
	virtual void UpdateMoveLeft(float fElpsedTime);
	virtual void UpdateMoveRight(float fElpsedTime);
	virtual void UpdateMoveUp(float fElpsedTime);
	virtual void UpdateMoveDown(float fElpsedTime);
	virtual void Clipping(float fElpsedTime);

	void CreateItem();
	void DestroyItem();
	void DisplayItem(olc::PixelGameEngine * tpDc);

	void SetPGE(olc::PixelGameEngine *mpPge);	
	void SetIsClipingItem(bool IsClipingItem);
	void SetCollipse(bool IsCollipse);
	void SetIsMoving(bool IsMoving);

	bool GetIsClipingItem();
	bool GetIsCollipse();
	bool GetISMoving();
};

