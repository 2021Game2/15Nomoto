#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CTaskManager.h"
#include "CBattleParam.h"

class CXPlayer : public CXCharacter
{
private:
	int mHp;	//�v���C���[HP
	bool mIn_Defense;		//�h�䔻��t���O false:�h�䂵�Ă��Ȃ� true:�h�䒆
	bool mIn_Dodge;			//��𔻒�t���O false:������Ă��Ȃ� treu:���
	int mDodge_Time;		//��𔻒莞��
	float mJump;			//�W�����v����
	bool mJump_Flag;		//�W�����v����t���O false:���n���Ă��� true:�W�����v��
	int mInv_Cnt;			//���G����

	/*enum PlayerState {
		State_Idle = 0,
		State_Walk,
		State_Dodge,
		State_Jump,
		State_Light_Attack,
		State_Strong_Attack,
		State_Hit,
		State_Blow,
		State_Death,
	};*/

	enum Anim {
		Anim_None = 0,
		Anim_TPose,
		Anim_Walk,
		Anim_Walk_Backwards,
		Anim_Run,
		Anim_Strafe_left,
		Anim_Strafe_right,
		Anim_Jump,
		Anim_Attack1,
		Anim_Attack2,
		Anim_Attack3,
		Anim_Attack4,
		Anim_Attack5,
		Anim_Attack6,
		Anim_Hit1,
		Anim_Hit2,
		Anim_Hit3,
		Anim_Death1,
		Anim_Death2,
		Anim_Idle1,
		Anim_Idle2,
		Anim_Emotion1,
		Anim_Emotion2,
		Anim_End
	};

public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��
	CCollider mColSphereFoot;	//��

	CXPlayer();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();
	//�Փˏ���
	//m:�����̃R���C�_ o:����̃R���C�_
	void Collision(CCollider* m, CCollider* o);

	static CXPlayer *spInstance;		//�v���C���[�̃C���X�^���X �O���Q�Ɨp
	bool mIn_Light_Attack;	//��U������t���O false:�U�����Ă��Ȃ� true:�U����
	bool mIn_Strong_Attack;	//���U������t���O false:�U�����Ă��Ȃ� true:�U����

	static void Generate();			//����
	static void Release();			//���
	CVector GetPos();				//�ʒu�擾
	CVector GetRot();				//�p�x�擾�imY�A���W�A���j

	static CXPlayer* GetInstance();

	void TaskCollision();

	void ChangeState(Character_State hState);
};

#endif
