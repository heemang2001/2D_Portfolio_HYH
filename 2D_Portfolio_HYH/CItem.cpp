#include "CItem.h"

void CItem::UpdateMoveLeft(float fElpsedTime)
{
	mX = mX - mSpeed * fElpsedTime;
}

void CItem::UpdateMoveRight(float fElpsedTime)
{
	mX = mX + mSpeed * fElpsedTime;
}

void CItem::UpdateMoveUp(float fElpsedTime)
{
	mY = mY - mSpeed * fElpsedTime;
}

void CItem::UpdateMoveDown(float fElpsedTime)
{ 
	mY = mY + mSpeed * fElpsedTime;
}

void CItem::Clipping(float fElpsedTime)
{
	if (CUnit::mY - mRadius <= 0) // 위 끝
	{
		m_IsClipingItem = false;		
	}

	else if (CUnit::mY + mRadius >= mpPGE->ScreenHeight()) // 아래 끝
	{
		m_IsClipingItem = true;		
	}
}

void CItem::CreateItem()
{
	m_pItemSprite[0] = new olc::Sprite("resources/power01.png");
	m_pItemSprite[1] = new olc::Sprite("resources/power02.png");
	m_pItemSprite[2] = new olc::Sprite("resources/power03.png");
	m_pItemSprite[3] = new olc::Sprite("resources/power04.png");
	m_pItemSprite[4] = new olc::Sprite("resources/power05.png");
	m_pItemSprite[5] = new olc::Sprite("resources/power06.png");
	m_pItemSprite[6] = new olc::Sprite("resources/power07.png");
	m_pItemSprite[7] = new olc::Sprite("resources/power08.png");
	//m_IsItemAlive = true;
}

void CItem::DestroyItem()
{
	for (int i = 0; i < 20; i++)
	{
		if (m_pItemSprite[i] != nullptr)
		{
			delete m_pItemSprite[i];
			m_pItemSprite[i] = nullptr;
		}
	}
}

void CItem::DisplayItem(olc::PixelGameEngine * tpDc)
{
	tpDc->DrawSprite(mX-13.5f, mY-12.0f, m_pItemSprite[m_nItemSpriteIndex], 1);

	m_nItemSpriteIndex++;

	if (m_nItemSpriteIndex >= 8)
	{
		m_nItemSpriteIndex = 0;		
	}	
}

void CItem::SetPGE(olc::PixelGameEngine * mpPge)
{
	mpPGE = mpPge;
}

void CItem::SetIsClipingItem(bool IsClipingItem)
{
	m_IsClipingItem = IsClipingItem;
}

void CItem::SetCollipse(bool IsCollipse)
{
	m_IsCollipse = IsCollipse;
}

void CItem::SetIsMoving(bool IsMoving)
{
	m_IsMoving = IsMoving;
}

bool CItem::GetIsClipingItem()
{
	return m_IsClipingItem;
}

bool CItem::GetIsCollipse()
{
	return m_IsCollipse;
}

bool CItem::GetISMoving()
{
	return m_IsMoving;
}
