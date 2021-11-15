#include "CXPlayer.h"
#include "CKey.h"
#include "CCamera.h"
#include "CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CEffect.h"
#include "CXEnemy.h"

#define INITIALIZE 0	//初期化
#define PLAYERHP 100	//プレイヤーHP初期値
#define DODGETIME 30	//回避時間
#define GRAVITY 0.2	//重力加速度
#define JUMP_SPEED 5	//ジャンプ初速

CXPlayer *CXPlayer::spInstance = 0;

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	, mColSphereFoot(this, nullptr, CVector(0.0f,0.0f,0.0f), 0.8f)
	, mHp(INITIALIZE)
	, mAttack_switch(false)
	, mIn_Light_Attack(false)
	, mIn_Strong_Attack(false)
	, mIn_Defense(false)
	, mIn_Dodge(false)
	, mDodge_Time(INITIALIZE)
	, mJump(INITIALIZE)
	, mJump_Flag(false)
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_rot(0.0f, 0.0f, 0.0f)
	, m_vec(0.0f, 0.0f, 0.0f)
	, m_rad(0.5f)
{
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
	mHp = PLAYERHP;
	spInstance = this;
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
	//剣
	mColSphereSword.mpMatrix = &mpCombinedMatrix[22];
	//足
	mColSphereFoot.mpMatrix = &mpCombinedMatrix[0];

	mRotation.mY = 0.01f;
}

void CXPlayer::Generate() 
{
	spInstance = new CXPlayer;
}

void CXPlayer::Release()
{
	if (spInstance) {
		delete spInstance;
		spInstance = NULL;
	}
}

CXPlayer* CXPlayer::GetInstance() 
{
	return spInstance;
}
CVector CXPlayer::GetPos() {
	return m_pos;
}
CVector CXPlayer::GetRot()
{
	return m_rot;
}

void CXPlayer::Update()
{
	if (mHp > 0) {
		if (mAnimationIndex == 3)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(4, false, 20);
			}
		}
		else if (mAnimationIndex == 4)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mAttack_switch = true;
				mIn_Light_Attack = false;
			}
		}
		else if (mAnimationIndex == 5)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(6, false, 20);
			}
		}
		else if (mAnimationIndex == 6)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mAttack_switch = false;
				mIn_Light_Attack = false;
			}
		}
		else if (mAnimationIndex == 7)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(8, false, 30);
			}
		}
		else if (mAnimationIndex == 8)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mIn_Strong_Attack = false;
			}
		}
		else
		{
			//カメラ視点移動　通称無双移動

			//カメラの左右と前後のベクトルを取得
			CVector SideVec = Camera.GetMat().GetXVec();
			CVector FrontVec = Camera.GetMat().GetZVec();

			CVector Vertical;
			//高さ移動はカットする
			SideVec.mY = 0.0f;
			FrontVec.mY = 0.0f;
			//正規化する
			SideVec.Normalize();
			FrontVec.Normalize();
			Vertical.Normalize();

			float speed = 0.15f;
			CVector Move(0, 0, 0);


			if (CKey::Push('A'))
			{
				//			mRotation.mY += 2.0f;
				if (mIn_Dodge == true)
				{
					Move -= SideVec * 2;
				}
				else
				{
					Move -= SideVec;
				}
			}
			else if (CKey::Push('D'))
			{
				//			mRotation.mY -= 2.0f;
				if (mIn_Dodge == true)
				{
					Move += SideVec * 2;
				}
				else
				{
					Move += SideVec;
				}
			}
			if (CKey::Push('W'))
			{
				//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
				if (mIn_Dodge == true)
				{
					Move += FrontVec * 2;
				}
				else
				{
					Move += FrontVec;
				}
			}
			else if (CKey::Push('S'))
			{
				//			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
				if (mIn_Dodge == true)
				{
					Move -= FrontVec * 2;
				}
				else
				{
					Move -= FrontVec;
				}
			}

			if (CKey::Push('J') && mAttack_switch == false)
			{
				ChangeAnimation(3, true, 20);
				mIn_Light_Attack = true;
			}
			else if (CKey::Push('J') && mAttack_switch == true) {
				ChangeAnimation(5, true, 20);
				mIn_Light_Attack = true;
			}
			else if (CKey::Push('K')) {
				ChangeAnimation(7, true, 30);
				mIn_Strong_Attack = true;
			}
			else if (Move.Length() != 0.0f)
			{
				ChangeAnimation(1, true, 60);
			}
			else
			{
				ChangeAnimation(0, true, 60);
			}

			if (CKey::Once(' ')&&mJump_Flag==false)
			{
				mJump = JUMP_SPEED;
				mJump_Flag = true;
			}

			mJump -= GRAVITY;

			Vertical.mY += mJump;

			Move += Vertical;

			//移動量正規化　これをしないと斜め移動が早くなってしまうので注意
			//ジャンプ時などはY軸を正規化しないよう注意
			Move.Normalize();
			//平行移動量
			Move = Move * speed;


			//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
			//擬似ベクトル計算
			Check tCheck = CUtil::GetCheck2D(Move.mX, Move.mZ, 0, 0, mRotation.mY * (M_PI / 180.0f));

			//回転速度　degreeに直す
			float turnspeed = (180.0f / M_PI) * 0.5f;

			//急な振り返りを抑制
			if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

			//移動方向へキャラを向かせる
			if (tCheck.cross > 0.0f) {
				mRotation.mY += tCheck.turn * turnspeed;
			}
			if (tCheck.cross < 0.0f) {
				mRotation.mY -= tCheck.turn * turnspeed;
			}

			//座標移動
			mPosition += Move;

			if (CKey::Push('I'))
			{
				mIn_Defense = true;
			}
			else 
			{
				mIn_Defense = false;
			}

			if (CKey::Push('L'))
			{
				mDodge_Time = DODGETIME;
			}
			if (mDodge_Time > 0)
			{
				mDodge_Time--;
				mIn_Dodge = true;
			}
			else
			{
				mIn_Dodge = false;
			}
		}
	}
	//注視点設定
	Camera.SetTarget(mPosition);


	CXCharacter::Update();
}

void CXPlayer::Collision(CCollider* m, CCollider* o)
{
	if (m->mType == CCollider::ESPHERE)
	{
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EENEMY)
			{
				if (o->mTag == CCollider::ESWORD)
				{
					if (CCollider::Collision(m, o))
					{
						if (mIn_Defense == false) 
						{
							if (mIn_Dodge == false)
							{
								mHp -= 5;
								if (mHp <= 0) {
									ChangeAnimation(11, false, 30);
								}
								if (mAnimationIndex == 11) {
									if (mAnimationFrame >= mAnimationFrameSize)
									{
										ChangeAnimation(12, false, 30);
									}
								}
							}
						}
					}
				}
			}
		}
		if (o->mType == CCollider::ETRIANGLE)
		{
			CVector adjust;
			if (CCollider::CollisionTriangleSphere(o, m, &adjust))
			{
				//衝突していない位置まで戻す
				mPosition = mPosition + adjust;
				mJump = 0;
				mJump_Flag = false;
			}
		}
	}
}
