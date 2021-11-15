#include "CXPlayer.h"
#include "CKey.h"
#include "CCamera.h"
#include "CUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CEffect.h"
#include "CXEnemy.h"

#define INITIALIZE 0	//������
#define PLAYERHP 100	//�v���C���[HP�����l
#define DODGETIME 30	//�������
#define GRAVITY 0.2	//�d�͉����x
#define JUMP_SPEED 5	//�W�����v����

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
	//�^�O�Ƀv���C���[��ݒ肵�܂�
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
	mHp = PLAYERHP;
	spInstance = this;
}

void CXPlayer::Init(CModelX* model)
{
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
			if (tCheck.cross > 0.0f) {
				mRotation.mY += tCheck.turn * turnspeed;
			}
			if (tCheck.cross < 0.0f) {
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
	//�����_�ݒ�
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
				//�Փ˂��Ă��Ȃ��ʒu�܂Ŗ߂�
				mPosition = mPosition + adjust;
				mJump = 0;
				mJump_Flag = false;
			}
		}
	}
}
