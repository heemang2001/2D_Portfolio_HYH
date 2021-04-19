#define OLC_PGE_APPLICATION
#include <string>
#include "olcPixelGameEngine.h"
#include "CScrollBg.h"
#include "CUnit.h"
#include "CActor.h"
#include "CBullet.h"
#include "CEnemy.h"
#include "CItem.h"

#define BOSS_Y 45.0f
#define MAPSIZE_ENEMY_Y -1600
#define RADIUS_ENEMY 33
#define BULLET_TIME_ENEMY 2.0f
#define BULLET_TIME_BOSS 0.5f
#define BULLET_TIME_BOSS_2 0.04f
#define BULLET_AMOUNT_ACTOR 100
#define BULLET_AMOUNT_ENEMY 100
#define BULLET_AMOUNT_BOSS 100
#define AMOUNT_ENEMY 15
#define AMOUNT_ITEM AMOUNT_ENEMY
#define DISPLAY_STAGE_FRAME 30
#define SPEED_ENEMY 100.0f

enum SCENE
{
	TITELE = 0,
	READY_PLAYGAME,
	PLAYGAME,
	CLEAR,
	ENDGAME
};

enum STAGE
{
	STAGE_1 = 1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_BOSS
};

// Override base class with your custom functionality
class CPortfolio2D : public olc::PixelGameEngine
{
	CScrollBg mBg_0;			// 배경
	CActor mActor;				// 주인공 기체
	CEnemy mEnemy[AMOUNT_ENEMY];// 적기(잡몹)
	CItem mItem[AMOUNT_ITEM];	// 아이템
	CEnemy mBoss;				// 적기(보스)

	CBullet mBullet_Actor[BULLET_AMOUNT_ACTOR];
	CBullet mBullet_Enemy[AMOUNT_ENEMY][BULLET_AMOUNT_ENEMY];
	CBullet mBullet_Boss_left[BULLET_AMOUNT_BOSS];
	CBullet mBullet_Boss_right[BULLET_AMOUNT_BOSS];

	SCENE mSceneState;
	STAGE mStageState = STAGE::STAGE_1;

	string sScore = "0";

	// 적기체 x좌표 y좌표 랜덤설정
	float fRandXvalue = 0;
	float fRandYvalue = 0;

	float fBulletTimeMinus = 0.0;

	bool IsEndStage = false;	
	bool IsStageClear = false;
	bool IsBoss = false;

	int nCountDeadEnemy = 0;	
	int nDisplayStage = 0;		
	
public:	

	CPortfolio2D()
	{
		// Name you application
		sAppName = "CPortfolio2D";
	}

public:
	bool OnUserCreate() override
	{
		// 스프라이트들 초기화
		SpriteCreate();	

		mSceneState = SCENE::TITELE;
		return true;
	}

	bool OnUserDestroy() override
	{
		// 배경 스프라이트 해제
		mBg_0.DestroyR();

		// 주인공 기체 스프라이트 해제
		mActor.DestroyActor();

		// 아이템 스프라이트 해제
		for (int i = 0; i < AMOUNT_ITEM; i++)
		{
			mItem[i].DestroyItem();
		}

		// 적기 스프라이트 해제
		//for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			mEnemy[0].DestroyEnemy();
		}

		// 주인공, 적 기체 총알 스프라이트 해제
		//for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[0].DestroyBullet();
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		switch (mSceneState)
		{
		case TITELE:
			mBg_0.Display_Start_Bg(); // 시작 배경 Display

			if (GetKey(olc::Key::SPACE).bReleased)
			{
				mSceneState = SCENE::READY_PLAYGAME;
			}

			if (GetKey(olc::Key::ESCAPE).bReleased)
			{
				mSceneState = SCENE::ENDGAME;
			}

			break;

		case READY_PLAYGAME:
			CreatePlayGame(); // 게임 데이터 설정
			mSceneState = SCENE::PLAYGAME;
			break;

		case PLAYGAME: // 게임중

			if (mActor.GetActorIsAlive() == true)
			{
				SetPixelMode(olc::Pixel::MASK);

				UpdatePlayGame(fElapsedTime); // 게임 구현부

				SetPixelMode(olc::Pixel::NORMAL);

				if (GetKey(olc::Key::ESCAPE).bReleased)
				{
					mSceneState = SCENE::ENDGAME;
				}
			}

			// 주인공이 죽으면 R을 누르면 데이터를 초기화하고 다시시작
			// ESC를 누르면 종료
			else
			{
				DrawString(ScreenWidth() / 5 - 75.0f, ScreenHeight() / 2, "Retry R / Exit ESC", olc::MAGENTA, 3);

				if (GetKey(olc::Key::R).bReleased)
				{
					ResetGame();
					mSceneState = SCENE::READY_PLAYGAME;
				}

				if (GetKey(olc::Key::ESCAPE).bReleased)
				{
					mSceneState = SCENE::ENDGAME;
				}
			}
			break;

		case CLEAR: // 보스를 죽이고 게임 클리어시
			GameClear();
			break;

		case ENDGAME: // 게임 종료
			ExitGame();
			break;
		}
		return true;
	}

	void GameClear()
	{
		cout << "###### 게임 클리어 / Enter(종료) #####" << endl;

		DrawString(ScreenWidth() / 5 + 20, ScreenHeight() / 2, "Game Clear!" , olc::RED, 3);

		if (GetKey(olc::Key::ENTER).bHeld)
		{
			mSceneState = SCENE::ENDGAME;
		}		
	}

	void ExitGame()
	{
		cout << "게임 종료" << endl;
		exit(0);
	}

	void ResetGame()
	{
		mStageState = STAGE::STAGE_1;
		nCountDeadEnemy = 0;
		mActor.SetActorIsAlive(true);
		mActor.SetActorScore(0);
		mActor.SetActorBulletPower(0);
		sScore = "0";
		IsStageClear = false;
		fBulletTimeMinus = 0;
		IsBoss = false;

		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			mEnemy[i].SetEnemySpriteIndex(0);
			mEnemy[i].SetDeadEnemy(0);
			mEnemy[i].SetIsAliveEnemy(false);
		}

		mBoss.mIsAlive = false;

		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			mItem[k].mIsAlive = false;

			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				mBullet_Enemy[k][i].mIsAlive = false;
			}
		}

		for (int i = 0; i < BULLET_AMOUNT_BOSS; i++)
		{
			mBullet_Boss_left[i].mIsAlive = false;
			mBullet_Boss_right[i].mIsAlive = false;
		}

		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[i].mIsAlive = false;
		}
	}

	bool CollisionEnemytoEnemyAdjust()
	{		
		float fRandXvalue = 0; // 적기의 x축 위치		
		float fRandYvalue = 0; // 적기의y축 위치	

		bool IsCollison_EE = false;

		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			mEnemy[i].SetEnemySpriteIndex(0);
			mEnemy[i].mDirX = 1.0f; // 방향 아래로
			mEnemy[i].mIsAlive = true;
			mEnemy[i].SetIsAliveEnemy(true);
			mEnemy[i].SetEnemyHP(100);
			mEnemy[i].SetRandomItemValue(-1);

			// 적기체 x좌표 y좌표 랜덤설정
			fRandXvalue = rand() % ScreenWidth() + RADIUS_ENEMY;
			fRandYvalue = rand() % MAPSIZE_ENEMY_Y;

			// 적기체가 화면 x축 밖이랑 겹치면 적기체의 x좌표를 화면 안으로 재조정
			if (fRandXvalue + RADIUS_ENEMY >= ScreenWidth())
			{
				fRandXvalue -= 2 * (RADIUS_ENEMY);
			}

			mEnemy[i].BuildInfo(fRandXvalue, -fRandYvalue, SPEED_ENEMY, RADIUS_ENEMY);

			// 
			for (int k = 0; k < AMOUNT_ENEMY; k++)
			{
				if (i != k) // 자기 자신의 충돌원은 제외
				{
					// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
					float tEEAdd = (RADIUS_ENEMY + RADIUS_ENEMY)*(RADIUS_ENEMY + RADIUS_ENEMY);
					float tEEDistance = (mEnemy[i].mX - mEnemy[k].mX) * (mEnemy[i].mX - mEnemy[k].mX)
						+ (mEnemy[i].mY - mEnemy[k].mY) * (mEnemy[i].mY - mEnemy[k].mY);

					// 적기끼리 충돌원이 겹치는 경우
					if (tEEDistance <= tEEAdd)
					{
						IsCollison_EE = true;

						//cout << "collision_ETOE --> 위치 재조정" << endl;

						// 적기체 x좌표 y좌표 랜덤설정
						fRandXvalue = rand() % ScreenWidth() + RADIUS_ENEMY;
						fRandYvalue = rand() % MAPSIZE_ENEMY_Y;

						// 적기체가 화면 x축 밖이랑 겹치면 적기체의 x좌표를 화면 안으로 재조정
						if (fRandXvalue + RADIUS_ENEMY >= ScreenWidth())
						{
							fRandXvalue -= 2 * (RADIUS_ENEMY);
						}
						mEnemy[i].BuildInfo(fRandXvalue, -fRandYvalue, SPEED_ENEMY, RADIUS_ENEMY);
					}
				}
			}
		}

		return IsCollison_EE;
	}

	void CreatePlayGame()
	{	
		// Called once at the start, so create things here			
		nDisplayStage = 0;

		// TEST STAGE
/*		if (mStageState != STAGE::STAGE_BOSS)
		{
			mStageState = STAGE::STAGE_4;
		}	*/	
		

		// 주인공 기체 초기화
		if (IsStageClear == false) // 처음 시작
		{
			mActor.BuildInfo(240.0f, 750.0f, 150.0f, 21, 100);
		}

		else // 이어서
		{
			mActor.BuildInfo(mActor.mX, mActor.mY, 150.0f, 21, mActor.GetActorLife());
		}			

		float fValueX = 0;
		float fValueY = 0;	

		// 스테이지 따라 적 총알발사간격 조정
		switch (mStageState)
		{
		case STAGE_1:
			break;

		case STAGE_2:
			fBulletTimeMinus = 0.33f;
			break;

		case STAGE_3:
			fBulletTimeMinus = 0.66f;
			break;

		case STAGE_4:
			fBulletTimeMinus = 0.99f;
			break;

		case STAGE_BOSS:
			IsBoss = true;

			break;
		}

		// 적 기체의 일반탄환 데이터 설정
		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				mBullet_Enemy[k][i].mRadius = 4.0f;
				mBullet_Enemy[k][i].mVelocity = 150.0f;
			}
		}

		// 보스 스테이지가 아닌경우에만
 		if (mStageState != STAGE_BOSS)
		{
			// 겹쳐지는 적기체 위치조정 (겹치는 경우가 있는경우 계속 위치조정)
			// + 적기체 초기화
			while (true == CollisionEnemytoEnemyAdjust())
			{
				CollisionEnemytoEnemyAdjust();
			}
		}

		// 보스 스테이지인 경우
		else 
		{
			mBoss.SetEnemySpriteIndex(16); // 보스 스프라이트
			mBoss.mDirX = 1.0f; // 방향 아래로
			mBoss.mIsAlive = true;
			mBoss.SetIsAliveEnemy(true);
			mBoss.SetEnemyHP(500);		 // 보스 HP설정

			mBoss.BuildInfo(240, -400, 30, 150);

			for (int i = 0; i < BULLET_AMOUNT_BOSS; i++)
			{
				mBullet_Boss_left[i].mRadius = 13;
				mBullet_Boss_left[i].mVelocity = 400.0f;

				mBullet_Boss_right[i].mRadius = 4.0f;
				mBullet_Boss_right[i].mVelocity = 200.0f;
			}
		}

		// 주인공 기체의 일반탄환 데이터 설정
		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[i].mRadius = 8.0f;
			mBullet_Actor[i].mVelocity = 250.0f;
		}
	}

	void UpdatePlayGame(float fElapsedTime)
	{
		// Update
		Clear(olc::BLACK);

		// Input
		// bHeld 엔진기능 : 누르고있으면
		if (GetKey(olc::Key::LEFT).bHeld)
		{
			mActor.UpdateMoveLeft(fElapsedTime);
		}

		if (GetKey(olc::Key::RIGHT).bHeld)
		{
			mActor.UpdateMoveRight(fElapsedTime);
		}

		if (GetKey(olc::Key::UP).bHeld)
		{
			mActor.UpdateMoveUp(fElapsedTime);
		}

		if (GetKey(olc::Key::DOWN).bHeld)
		{
			mActor.UpdateMoveDown(fElapsedTime);
		}		

		//cout << "nCountDeadEnemy : " << nCountDeadEnemy << endl;		

		// 적이 죽으면 적을없애고 유저의 점수를 올림
		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			//cout << "nDeadEnemy : " << mEnemy[i].GetIsAliveEnemy() << endl;			

			if ((mEnemy[i].GetIsAliveEnemy() != false) && (mEnemy[i].GetEnemyHP() <= 0))
			{	
				nCountDeadEnemy += mEnemy[i].DeathEnemy();	
				cout << i << " : death"<< endl;
				
				mActor.SetActorScore((mActor.GetActorScore()) + mEnemy[i].GetEnemyScore());
				int nScore = mActor.GetActorScore();
				sScore = to_string(nScore); // C++11에서 추가된 to_string()이용해 string으로 변환
			}

			// 적이 죽었을때 그 위치에 일정확률로 아이템 생성
			// 조건 1 : 적이 죽었을때 특정 난수가 나와야한다.
			// 조건 2 : 아이템이 충돌중이 아니다.
			// 조건 3 : 아이템이 움직이는 중이 아니다.
			// 조건 4 : 적기가 화면밖으로 나가 클리핑처리되지 않았다.			
			if ((mEnemy[i].GetRandomItemValue() == 0 ) && (mItem[i].GetIsCollipse() == false)
				&& (mItem[i].GetISMoving() == false) && (mEnemy[i].GetIsClipping() == false))
			{
				mItem[i].BuildInfo(mEnemy[i].mX, mEnemy[i].mY, 200, 14);
				mItem[i].mDirX = 1.0f;
				mItem[i].mIsAlive = true;
			}
		}
			
		
		if (mStageState == STAGE::STAGE_BOSS && mBoss.GetEnemyHP() <= 0)
		{
			mSceneState = SCENE::CLEAR;
		}
			// 적기가 화면안에 있을때만 Dofire()
			if (mBoss.mY >= BOSS_Y && mBoss.mIsAlive == true)
			{
				// (BULLET_TIME_BOSS)초 간격으로 탄환 발사				
				if (mBoss.GetTimeTick() >= BULLET_TIME_BOSS)
				{					
					// (BULLET_TIME_BOSS)초마다 탄환을 발사하는 구문.
					mBoss.DoFire_Bossleft(mBullet_Boss_left, &mActor);					

					mBoss.SetTimeTick(0.0f);
				}

				else
				{
					// 프레임당 시간 (실제 시간)을 누적해간다.					
					mBoss.SetTimeTick(mBoss.GetTimeTick() + fElapsedTime);
				}

				// (BULLET_TIME_BOSS_2)초 간격으로 탄환 발사				
				if (mBoss.GetTimeTick_2() >= BULLET_TIME_BOSS_2)
				{
					// (BULLET_TIME_BOSS_2)초마다 탄환을 발사하는 구문.					
					mBoss.DoFire_Bossright(mBullet_Boss_right, &mActor);

					mBoss.SetTimeTick_2(0.0f);
				}

				else
				{
					// 프레임당 시간 (실제 시간)을 누적해간다.					
					mBoss.SetTimeTick_2(mBoss.GetTimeTick_2() + fElapsedTime);
				}
			}


		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			// 적기가 화면안에 있을때만 Dofire()
			if ((mEnemy[i].mX >= 0) && (mEnemy[i].mX <= 480) && (mEnemy[i].mY >= 0))
			{
				// (BULLET_TIME_ENEMY - fBulletTimeMinus)초 간격으로 탄환 발사
				// fBulletTimeMinus는 스테이지가 오를수록 커짐 --> 적 탄환발사 간격이 짧아짐
				if (mEnemy[i].GetTimeTick() >= BULLET_TIME_ENEMY - fBulletTimeMinus)
				{
					// (BULLET_TIME_ENEMY - fBulletTimeMinus)초마다 탄환을 발사하는 구문.
					mEnemy[i].DoFire(mBullet_Enemy, &mActor, i);

					//mEnemy.DoFireEx(mBullet_Enemy, &mActor);

					mEnemy[i].SetTimeTick(0.0f);
				}

				else
				{
					// 프레임당 시간 (실제 시간)을 누적해간다.
					//mEnemy.m_fTimeTick = mEnemy.m_fTimeTick + fElapsedTime;
					mEnemy[i].SetTimeTick(mEnemy[i].GetTimeTick() + fElapsedTime);
				}
			}
		}

		// 주인공 기체의 일반탄환 업데이트
		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[i].UpdateMoveBullet(fElapsedTime); // 총알이 움직이게 하는함수
		}

		// bReleased 엔진기능 : 누르고 뗄 때
		if (GetKey(olc::Key::SPACE).bReleased)
		{
			mActor.DoFire(mBullet_Actor);
		}

		
		// 보스 탄환 업데이트
		for (int i = 0; i < BULLET_AMOUNT_BOSS; i++)
		{
			mBullet_Boss_left[i].UpdateMoveBullet(fElapsedTime); // 총알이 움직이게 하는함수
			mBullet_Boss_right[i].UpdateMoveBullet(fElapsedTime);
		}

		// 적 기체의 일반탄환 업데이트
		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				//if (mStageState != STAGE::STAGE_BOSS)
				{
					if (mBullet_Enemy[k][i].mIsAlive == true)
					{
						mBullet_Enemy[k][i].UpdateMoveBullet(fElapsedTime); // 총알이 움직이게 하는함수
					}
				}
			}
		}

		// 엔진 설정
		mActor.SetPGE(this);

		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			mEnemy[i].SetPGE(this);
		}

		for (int i = 0; i < AMOUNT_ITEM; i++)
		{
			mItem[i].SetPGE(this);
		}

		mBoss.SetPGE(this);


		// 클리핑 함수
		mActor.Clipping(fElapsedTime);

		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			mEnemy[i].Clipping(fElapsedTime);				
		}

		//cout << "clipping Enemy : " << mEnemy[0].GetDeadEnemy() << endl;

		for (int i = 0; i < AMOUNT_ITEM; i++)
		{
			mItem[i].Clipping(fElapsedTime);
		}

		DisPlay_StageState();

		// 배경
		mBg_0.UpdateR(fElapsedTime);
		mBg_0.Display_Game_Bg();

		// 스테이지 스트링
		if (nDisplayStage <= DISPLAY_STAGE_FRAME)
		{
			DisplayStageString(mStageState, fElapsedTime);
		}		

		// 주인공
		mActor.DisplayCircle(this);
		mActor.DisplayMoveActor(this);		

		// 보스 스테이지가 아니면 
		if (mStageState != STAGE_BOSS)
		{
			// 적
			for (int i = 0; i < AMOUNT_ENEMY; i++)
			{
				if (mEnemy[i].GetIsAliveEnemy() == true)
				{
					mEnemy[i].DisplayCircle(this);
					mEnemy[i].UpdateMoveDown(fElapsedTime);

					mEnemy[i].DisplayMoveEnemy(this);
				}

				else
				{
					mEnemy[i].DisplayExplosionEnemy(this, fElapsedTime);
				}
			}
		}

		// 보스 스테이지면
		else
		{
			if (mBoss.mIsAlive == true)
			{
				mBoss.DisplayCircle(this);				
				mBoss.DisplayMoveBoss(this);

				if (mBoss.mY <= BOSS_Y)
				{
					mBoss.UpdateMoveDown(fElapsedTime);		
				}				
			}
		}

		// 점수,HP바
		DrawString(25, 25, "SCORE :", olc::YELLOW, 1);
		DrawString(25, 50, "HP", olc::YELLOW, 1);		
		DrawString(100, 25, sScore, olc::WHITE, 1);
		mActor.DisplayActorLife(this);

		// 아이템
		for (int i = 0; i < AMOUNT_ITEM; i++)
		{
			if (mItem[i].mIsAlive == true)
			{
				mItem[i].DisplayCircle(this);
				mItem[i].DisplayItem(this);
				mItem[i].SetIsMoving(true);

				// 아이템은 기본적으로 밑으로 움직이다 아래축에 부딫히면 위로 이동 반복
  				if (mItem[i].GetIsClipingItem() == false)
				{
					mItem[i].UpdateMoveDown(fElapsedTime);
				}

				else
				{
					mItem[i].UpdateMoveUp(fElapsedTime);
				}
			}
		}

		// 주인공 기체의 일반탄환 Display
		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[i].DisplayBullet_Actor(this, olc::YELLOW, &mActor);
		}

		// 보스 탄환 Display
		for (int i = 0; i < BULLET_AMOUNT_BOSS; i++)
		{
			if (mBullet_Boss_left[i].mIsAlive == true)
			{
				mBullet_Boss_left[i].DisplayBullet_Boss(this, olc::RED);
			}

			if (mBullet_Boss_right[i].mIsAlive == true)
			{
				mBullet_Boss_right[i].DisplayBullet_Enemy(this, olc::RED);
			}
			
		}

		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			// 적 기체의 일반탄환 Display
			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				if (mBullet_Enemy[k][i].mIsAlive == true)
				{
					mBullet_Enemy[k][i].DisplayBullet_Enemy(this, olc::YELLOW);
				}
			}
		}

		// 충돌설정
		Collision_Setting();
	}

	void Collision_Setting()
	{
		// collision
		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
			{
				// 적기가 살아있는 경우만
				if (mEnemy[k].GetIsAliveEnemy() != false)
				{
					// 주인공 기체에서 나오는 탄환 충돌설정
					if (true == mBullet_Actor[i].mIsAlive)
					{
						// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
						float tAdd = (mBullet_Actor[i].mRadius + mEnemy[k].mRadius)*(mBullet_Actor[i].mRadius + mEnemy[k].mRadius);
						float tDistance = (mBullet_Actor[i].mX - mEnemy[k].mX) * (mBullet_Actor[i].mX - mEnemy[k].mX)
							+ (mBullet_Actor[i].mY - mEnemy[k].mY) * (mBullet_Actor[i].mY - mEnemy[k].mY);

						if (tDistance <= tAdd)
						{
							cout << "collision_ENEMY" << endl;

							mBullet_Actor[i].mIsAlive = false;

							// 적기가 주인공기체의 탄환에 맞으면 
							// 적기의 현재체력 = 적기의 체력 - 주인공 기체의 공격력						
							mEnemy[k].SetEnemyHP(mEnemy[k].GetEnemyHP() - mActor.GetActorDamage());
							//cout << "적 (" << k << ") 의 HP : " << mEnemy[k].GetEnemyHP() << endl;

							break;
						}
					}
				}
			}
		}


		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			// 보스가 살아있는 경우만
			if (mBoss.GetIsAliveEnemy() != false)
			{
				// 주인공 기체에서 나오는 탄환 충돌설정
				if (true == mBullet_Actor[i].mIsAlive)
				{
					// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
					float tAdd = (mBullet_Actor[i].mRadius + mBoss.mRadius)*(mBullet_Actor[i].mRadius + mBoss.mRadius);
					float tDistance = (mBullet_Actor[i].mX - mBoss.mX) * (mBullet_Actor[i].mX - mBoss.mX)
						+ (mBullet_Actor[i].mY - mBoss.mY) * (mBullet_Actor[i].mY - mBoss.mY);

					if (tDistance <= tAdd)
					{
						cout << "collision_ENEMY" << endl;

						mBullet_Actor[i].mIsAlive = false;

						// 보스가 주인공기체의 탄환에 맞으면 
						// 보스의 현재체력 = 적기의 체력 - 주인공 기체의 공격력						
						mBoss.SetEnemyHP(mBoss.GetEnemyHP() - mActor.GetActorDamage());
						cout << "보스의 HP : " << mBoss.GetEnemyHP() << endl;

						break;
					}
				}
			}
		}


		for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
		{
			// 보스 기체에서 나오는 탄환 충돌설정 (왼쪽탄환)
			if (true == mBullet_Boss_left[i].mIsAlive)
			{
				// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
				float tEAdd = (mBullet_Boss_left[i].mRadius + mActor.mRadius)*(mBullet_Boss_left[i].mRadius + mActor.mRadius);
				float tEDistance = (mActor.mX - mBullet_Boss_left[i].mX) * (mActor.mX - mBullet_Boss_left[i].mX)
					+ (mActor.mY - mBullet_Boss_left[i].mY) * (mActor.mY - mBullet_Boss_left[i].mY);

				if (tEDistance <= tEAdd)
				{
					cout << "collision_ACTOR" << endl;

					// 주인공 기체가 보스의 탄환에 맞으면 
					// 주인공기체의 현재체력 = 주인공 기체의 체력 - 보스의 공격력						
					mActor.SetActorLife(mActor.GetActorLife() - mBoss.GetEnemyDamage());

					cout << "HP : " << mActor.GetActorLife() << endl;

					mBullet_Boss_left[i].mIsAlive = false;

					break;
				}
			}

			// 보스 기체에서 나오는 탄환 충돌설정 (오른쪽탄환)
			if (true == mBullet_Boss_right[i].mIsAlive)
			{
				// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
				float tEAdd = (mBullet_Boss_right[i].mRadius + mActor.mRadius)*(mBullet_Boss_right[i].mRadius + mActor.mRadius);
				float tEDistance = (mActor.mX - mBullet_Boss_right[i].mX) * (mActor.mX - mBullet_Boss_right[i].mX)
					+ (mActor.mY - mBullet_Boss_right[i].mY) * (mActor.mY - mBullet_Boss_right[i].mY);

				if (tEDistance <= tEAdd)
				{
					cout << "collision_ACTOR" << endl;

					// 주인공 기체가 보스의 탄환에 맞으면 
					// 주인공기체의 현재체력 = 주인공 기체의 체력 - 보스의 공격력						
					mActor.SetActorLife(mActor.GetActorLife() - mBoss.GetEnemyDamage());

					cout << "HP : " << mActor.GetActorLife() << endl;

					mBullet_Boss_right[i].mIsAlive = false;

					break;
				}
			}
		}
		

		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				// 적 기체에서 나오는 탄환 충돌설정
				if (true == mBullet_Enemy[k][i].mIsAlive)
				{
					// 루트함수써도 되지만 연산비용이 높아서 제곱으로 함
					float tEAdd = (mBullet_Enemy[k][i].mRadius + mActor.mRadius)*(mBullet_Enemy[k][i].mRadius + mActor.mRadius);
					float tEDistance = (mActor.mX - mBullet_Enemy[k][i].mX) * (mActor.mX - mBullet_Enemy[k][i].mX)
						+ (mActor.mY - mBullet_Enemy[k][i].mY) * (mActor.mY - mBullet_Enemy[k][i].mY);

					if (tEDistance <= tEAdd)
					{
						cout << "collision_ACTOR" << endl;

						// 주인공 기체가 적기체의 탄환에 맞으면 
						// 주인공기체의 현재체력 = 주인공 기체의 체력 - 적 기체의 공격력						
						mActor.SetActorLife(mActor.GetActorLife() - mEnemy[k].GetEnemyDamage());

						cout << "HP : " << mActor.GetActorLife() << endl;

						mBullet_Enemy[k][i].mIsAlive = false;

						break;
					}
				}
			}
		}

		for (int k = 0; k < AMOUNT_ITEM; k++)
		{
			// 아이템과 주인공 충돌설정
			if (true == mItem[k].mIsAlive)
			{
				float tIAdd = (mItem[k].mRadius + mActor.mRadius)*(mItem[k].mRadius + mActor.mRadius);
				float tIDistance = (mActor.mX - mItem[k].mX) * (mActor.mX - mItem[k].mX)
					+ (mActor.mY - mItem[k].mY) * (mActor.mY - mItem[k].mY);

				if (tIDistance <= tIAdd)
				{
					cout << "collision_ITEM" << endl;
					// 아이템과 충돌하면 주인공 파워업
					mActor.SetActorBulletPower(mActor.GetActorBulletPower() + 1);
					mItem[k].mIsAlive = false;
					mItem[k].SetCollipse(true);

					break;
				}
			}

		}
	}

	void DisPlay_StageState()
	{
		if ((mStageState == 1) && (nCountDeadEnemy + mEnemy[0].GetDeadEnemy() == AMOUNT_ENEMY))
		{
			IsStageClear = true;
			mStageState = STAGE::STAGE_2;
			mSceneState = SCENE::READY_PLAYGAME;
		}

		else if ((mStageState == 2) && (nCountDeadEnemy + mEnemy[0].GetDeadEnemy() == AMOUNT_ENEMY*2))
		{
			IsStageClear = true;
			mStageState = STAGE::STAGE_3;
			mSceneState = SCENE::READY_PLAYGAME;
		}

		else if ((mStageState == STAGE::STAGE_3) && (nCountDeadEnemy + mEnemy[0].GetDeadEnemy() == AMOUNT_ENEMY*3))
		{
			IsStageClear = true;
			mStageState = STAGE::STAGE_4;
			mSceneState = SCENE::READY_PLAYGAME;
		}

		// TEST
		//else if ((mStageState == STAGE::STAGE_4) && (nCountDeadEnemy + mEnemy[0].GetDeadEnemy() == AMOUNT_ENEMY * 1))
		else if ((mStageState == STAGE::STAGE_4) && (nCountDeadEnemy + mEnemy[0].GetDeadEnemy() == AMOUNT_ENEMY*4))
		{
 			IsStageClear = true;
			mStageState = STAGE::STAGE_BOSS;
			mSceneState = SCENE::READY_PLAYGAME;
		}

		else if ((mStageState == STAGE::STAGE_BOSS) && (mBoss.mIsAlive == false))
		{
			IsStageClear = true;			
			mSceneState = SCENE::CLEAR;
		}
	}

	int DisplayStageString(STAGE mStageState, float fElapsedTime)
	{		
		//cout << "Stage : " << mStageState << endl;
		string sTempStageStge = to_string(mStageState);
		if (mStageState == STAGE::STAGE_BOSS) sTempStageStge = "BOSS";
		DrawString(ScreenWidth() / 5+80, ScreenHeight() / 2, "Stage - ", olc::WHITE, 2);
		DrawString(ScreenWidth() / 5+ 205, ScreenHeight() / 2, sTempStageStge, olc::WHITE, 2);

		nDisplayStage++;

		return nDisplayStage;
	}

	// 스프라이트 초기화 함수
	void SpriteCreate()
	{
		olc::Sprite *m_pEnemySprite[50] =
		{
		m_pEnemySprite[0] = new olc::Sprite("resources/enemy.png"),
		m_pEnemySprite[1] = new olc::Sprite("resources/enemyexplosion01.png"),
		m_pEnemySprite[2] = new olc::Sprite("resources/enemyexplosion02.png"),
		m_pEnemySprite[3] = new olc::Sprite("resources/enemyexplosion03.png"),
		m_pEnemySprite[4] = new olc::Sprite("resources/enemyexplosion04.png"),
		m_pEnemySprite[5] = new olc::Sprite("resources/enemyexplosion05.png"),
		m_pEnemySprite[6] = new olc::Sprite("resources/enemyexplosion06.png"),
		m_pEnemySprite[7] = new olc::Sprite("resources/enemyexplosion07.png"),
		m_pEnemySprite[8] = new olc::Sprite("resources/enemyexplosion08.png"),
		m_pEnemySprite[9] = new olc::Sprite("resources/enemyexplosion09.png"),
		m_pEnemySprite[10] = new olc::Sprite("resources/enemyexplosion10.png"),
		m_pEnemySprite[11] = new olc::Sprite("resources/enemyexplosion11.png"),
		m_pEnemySprite[12] = new olc::Sprite("resources/enemyexplosion12.png"),
		m_pEnemySprite[13] = new olc::Sprite("resources/enemyexplosion13.png"),
		m_pEnemySprite[14] = new olc::Sprite("resources/enemyexplosion14.png"),
		m_pEnemySprite[15] = new olc::Sprite("resources/enemyexplosion15.png"),
		m_pEnemySprite[16] = new olc::Sprite("resources/boss.png")
		};

		olc::Sprite *m_pEnemyBulletSprite[5] =
		{ new olc::Sprite("resources/bullet_enemy01.png"),
		  new olc::Sprite("resources/bullet_boss01.png")};

		olc::Sprite *m_pActorBulletSprite[AMOUNT_SPRITE_BULLET_ACTOR]
			= { new olc::Sprite("resources/bullet_actor01.png"), //0
				 new olc::Sprite("resources/bullet_actor02.png"), //1
				 new olc::Sprite("resources/bullet_actor03.png"), //2
				 new olc::Sprite("resources/bullet_actor04.png"), //3

				 new olc::Sprite("resources/bullet_actor11.png"),
				 new olc::Sprite("resources/bullet_actor12.png"),
				 new olc::Sprite("resources/bullet_actor13.png"),
				 new olc::Sprite("resources/bullet_actor14.png"),

				 new olc::Sprite("resources/bullet_actor21.png"),
				 new olc::Sprite("resources/bullet_actor22.png"),
				 new olc::Sprite("resources/bullet_actor23.png"),
				 new olc::Sprite("resources/bullet_actor24.png") };

		// 시작배경과 게임배경 초기화
		mBg_0.CreateR(35.0f);
		mBg_0.SetPGE(this);

		// 주인공 기체 스프라이트 초기화
		mActor.CreateActor();

		// 총알 스프라이트 초기화
		for (int i = 0; i < BULLET_AMOUNT_ACTOR; i++)
		{
			mBullet_Actor[i].CreateBullet(m_pEnemyBulletSprite, m_pActorBulletSprite);
		}

		for (int k = 0; k < AMOUNT_ENEMY; k++)
		{
			for (int i = 0; i < BULLET_AMOUNT_ENEMY; i++)
			{
				mBullet_Enemy[k][i].CreateBullet(m_pEnemyBulletSprite, m_pActorBulletSprite);
			}
		}

		for (int i = 0;  i < BULLET_AMOUNT_BOSS; i++)
		{
			mBullet_Boss_left[i].CreateBullet(m_pEnemyBulletSprite, m_pActorBulletSprite);
			mBullet_Boss_right[i].CreateBullet(m_pEnemyBulletSprite, m_pActorBulletSprite);
		}

		// 적기 스프라이트 초기화
		for (int i = 0; i < AMOUNT_ENEMY; i++)
		{
			//mEnemy[i].SetPGE(this);
			mEnemy[i].CreateEnemy(m_pEnemySprite);
		}

		// 보스 스프라이트 초기화
		mBoss.CreateEnemy(m_pEnemySprite);		

		// 아이템 스프라이트 초기화
		for (int i = 0; i < AMOUNT_ITEM; i++)
		{
			mItem[i].CreateItem();
		}
	}

};

int main()
{
	srand(time(NULL));

	CPortfolio2D demo;
	if (demo.Construct(480, 800, 1, 1))
		demo.Start();
	return 0;
}