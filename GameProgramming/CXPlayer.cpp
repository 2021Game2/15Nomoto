#include "CXPlayer.h"
#include "CKey.h"
#include "CCamera.h"
#include "CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CEffect.h"
#include "CXEnemy.h"
#include "ClEnemy.h"
#include "CCollisionManager.h"
#include "CRes.h"

#define INITIALIZE 0	//������
#define PLAYERHP 10	//�v���C���[HP�����l
#define DODGETIME 30	//�������
#define GRAVITY 0.2	//�d�͉����x
#define JUMP_SPEED 5	//�W�����v����
#define INVTIME 30		//���G����
#define COMBO_TIME 30	//�A���U����t����

CXPlayer *CXPlayer::spInstance = 0;

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	, mColSphereFoot(this, nullptr, CVector(0.0f, 0.0f, 0.0f), 0.8f)
	, mHp(INITIALIZE)
	, mIn_Light_Attack(false)
	, mIn_Strong_Attack(false)
	, mIn_Defense(false)
	, mIn_Dodge(false)
	, mDodge_Time(INITIALIZE)
	, mJump(INITIALIZE)
	, mJump_Flag(false)
	, mInv_Cnt(INITIALIZE)
	, mAttack_Combo(false)
	, mAttack_Combo_Time(INITIALIZE)
	, mAttack_Combo_Count(INITIALIZE)
{
	//�^�O�Ƀv���C���[��ݒ肵�܂�
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
	mColSphereBody.mTag = mColSphereHead.mTag =  CCollider::EBODY;
	mHp = PLAYERHP;
	spInstance = this;

	CRes::sModelX.SeparateAnimationSet(0, 0, 5, "Tpose");
	CRes::sModelX.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sModelX.SeparateAnimationSet(0, 90, 160, "walk_backwards");
	CRes::sModelX.SeparateAnimationSet(0, 170, 220, "run");
	CRes::sModelX.SeparateAnimationSet(0, 230, 300, "strafe_left");
	CRes::sModelX.SeparateAnimationSet(0, 300, 370, "strafe_right");
	CRes::sModelX.SeparateAnimationSet(0, 380, 430, "jump");
	CRes::sModelX.SeparateAnimationSet(0, 440, 520, "attack_1");
	CRes::sModelX.SeparateAnimationSet(0, 520, 615, "attack_2");
	CRes::sModelX.SeparateAnimationSet(0, 615, 795, "attack_3");
	CRes::sModelX.SeparateAnimationSet(0, 795, 850, "attack_4");
	CRes::sModelX.SeparateAnimationSet(0, 850, 970, "attack_5");
	CRes::sModelX.SeparateAnimationSet(0, 970, 1040, "attack_6");
	CRes::sModelX.SeparateAnimationSet(0, 1040, 1080, "hit_1");
	CRes::sModelX.SeparateAnimationSet(0, 1080, 1120, "hit_2");
	CRes::sModelX.SeparateAnimationSet(0, 1120, 1160, "hit_3");
	CRes::sModelX.SeparateAnimationSet(0, 1160, 1260, "death_1");
	CRes::sModelX.SeparateAnimationSet(0, 1270, 1370, "death_2");
	CRes::sModelX.SeparateAnimationSet(0, 1380, 1530, "idle_1");
	CRes::sModelX.SeparateAnimationSet(0, 1530, 1830, "Idle_2");
	CRes::sModelX.SeparateAnimationSet(0, 1830, 1930, "emotion_1");
	CRes::sModelX.SeparateAnimationSet(0, 1930, 2040, "emotion_2");

}

void CXPlayer::Init(CModelX* model)
{
	model->mFrame[0]->mTransformMatrix = model->mFrame[0]->mTransformMatrix * CMatrix().RotateY(180);
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
	//��
	mColSphereSword.mpMatrix = &mpCombinedMatrix[22];
	//��
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
	return mPosition;
}
CVector CXPlayer::GetRot()
{
	return mRotation;
}

void CXPlayer::Update()
{
	if (mHp > 0) {
		if (mAnimationIndex == 8)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mAttack_Combo_Time = COMBO_TIME;
				mAttack_Combo_Count += 1;
			}
		}
		else if (mAnimationIndex == 9) 
		{
			if (mAnimationFrame >= mAnimationFrameSize) 
			{
				ChangeAnimation(0, true, 60);
				mAttack_Combo_Time = COMBO_TIME;
				mAttack_Combo_Count += 1;
			}
		}
		else if (mAnimationIndex == 10) 
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mAttack_Combo_Count = 0;
			}
		}
		else if (mAnimationIndex == 12)
		{
			if (mAnimationFrame >= mAnimationFrameSize)
			{
				ChangeAnimation(0, true, 60);
				mIn_Strong_Attack = false;
			}
		}
		else if (mAnimationIndex == 14) 
		{
			if (mAnimationFrame >= mAnimationFrameSize) 
			{
				ChangeAnimation(0, true, 60);
			}
		}
		else
		{
			//�J�������_�ړ��@�ʏ̖��o�ړ�

			//�J�����̍��E�ƑO��̃x�N�g�����擾
			CVector SideVec = Camera.GetMat().GetXVec();
			CVector FrontVec = Camera.GetMat().GetZVec();

			CVector Vertical;
			//�����ړ��̓J�b�g����
			SideVec.mY = 0.0f;
			FrontVec.mY = 0.0f;
			//���K������
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

			if (CKey::Once('J'))
			{
				if (mAttack_Combo == false)
				{
					ChangeState(State_Light_Attack);
					mIn_Light_Attack = true;
				}
				else if (mAttack_Combo_Count == 1)
				{
					ChangeState(State_Light_Attack2);
				}
				else if (mAttack_Combo_Count == 2)
				{
					ChangeState(State_Light_Attack3);
				}
			}
			else if (CKey::Push('K'))
			{
				ChangeState(State_Strong_Attack);
				mIn_Strong_Attack = true;
			}
			else if (mJump_Flag == true) 
			{
				ChangeState(State_Jump);
			}
			else if (mDodge_Time > 0) 
			{
				ChangeState(State_Dodge);
			}
			else if (Move.Length() != 0.0f)
			{
				ChangeState(State_Walk);
			}
			else
			{
				ChangeState(State_Idle);
			}

			if (CKey::Once(' ')&&mJump_Flag==false)
			{
				mJump = JUMP_SPEED;
				mJump_Flag = true;
			}

			mJump -= GRAVITY;

			Vertical.mY += mJump;

			Move += Vertical;

			//�ړ��ʐ��K���@��������Ȃ��Ǝ΂߈ړ��������Ȃ��Ă��܂��̂Œ���
			//�W�����v���Ȃǂ�Y���𐳋K�����Ȃ��悤����
			Move.Normalize();
			//���s�ړ���
			Move = Move * speed;


			//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
			//�[���x�N�g���v�Z
			Check tCheck = CUtil::GetCheck2D(Move.mX, Move.mZ, 0, 0, mRotation.mY * (M_PI / 180.0f));

			//��]���x�@degree�ɒ���
			float turnspeed = (180.0f / M_PI) * 0.5f;

			//�}�ȐU��Ԃ��}��
			if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

			//�ړ������փL��������������
			if (tCheck.cross > 0.0f) 
			{
				mRotation.mY += tCheck.turn * turnspeed;
			}
			if (tCheck.cross < 0.0f)
			{
				mRotation.mY -= tCheck.turn * turnspeed;
			}

			//���W�ړ�
			mPosition += Move;

			if (CKey::Push('I'))
			{
				mIn_Defense = true;
			}
			else 
			{
				mIn_Defense = false;
			}

			if (CKey::Once('L'))
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
	//�����_�ݒ�
	Camera.SetTarget(mPosition);

	if (mInv_Cnt > 0) {
		mInv_Cnt--;
	}
	if (mAttack_Combo_Time>0) {
		mAttack_Combo_Time--;
		mAttack_Combo = true;
	}
	else {
		mAttack_Combo = false;
		mAttack_Combo_Count = 0;
	}

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
				if (m->mTag == CCollider::ESWORD)
				{
					if (o->mpParent->mTag == EENEMY)
					{
						o->mpParent->Collision(o, m);
					}
				}
				if (o->mTag == CCollider::ESWORD)
				{
					if(m->mTag==CCollider::EBODY)
					{
						if(mHp>=0)
						{
							if (CCollider::Collision(m, o))
							{
								if (mInv_Cnt <= 0)
								{
									if (mIn_Defense == false)
									{
										if (mIn_Dodge == false)
										{
											mHp -= 1;
											mInv_Cnt = INVTIME;
											ChangeState(State_Hit);
											
										}
									}
								}
							}
						}
						else {
							if (mHp <= 0)
							{
								ChangeState(State_Death);
								return;
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
				//�Փ˂��Ă��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
				mJump = 0;
				mJump_Flag = false;
			}
		}
	}
}

void CXPlayer::TaskCollision()
{
	mColSphereBody.ChangePriority();
	mColSphereFoot.ChangePriority();
	mColSphereHead.ChangePriority();
	mColSphereSword.ChangePriority();

	CCollisionManager::Get()->Collision(&mColSphereBody, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereFoot, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereHead, COLLISIONRANGE);
	CCollisionManager::Get()->Collision(&mColSphereSword, COLLISIONRANGE);
}

void CXPlayer::ChangeState(Character_State hState) {
	switch (hState)
	{
	case State_Idle:
		ChangeAnimation(Anim_Idle1, true, 300);
		break;
	case State_Walk:
		ChangeAnimation(Anim_Walk, true, 50);
		break;
	case State_Dodge:
		ChangeAnimation(Anim_Attack6, false, 30);
		break;
	case State_Jump:
		ChangeAnimation(Anim_Jump, false, 50);
		break;
	case State_Light_Attack:
		ChangeAnimation(Anim_Attack1, false, 50);
		break;
	case State_Light_Attack2:
		ChangeAnimation(Anim_Attack2, false, 50);
		break;
	case State_Light_Attack3:
		ChangeAnimation(Anim_Attack3, false, 50);
		break;
	case State_Strong_Attack:
		ChangeAnimation(Anim_Attack5, false, 70);
		break;
	case State_Hit:
		ChangeAnimation(Anim_Hit1, false, 40);
		break;
	case State_Blow:
		ChangeAnimation(Anim_Hit2, false, 40);
		break;
	case State_Death:
		ChangeAnimation(Anim_Death1, false, 60);
		break;
	}
}