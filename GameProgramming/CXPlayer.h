#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
private:
	int mHp;	//�v���C���[HP
	bool mAttack_switch;	//��U���؂�ւ��p����t���O false:�E����U�肩�Ԃ� true:������U�肩�Ԃ�
	bool mIn_Defense;		//�h�䔻��t���O false:�h�䂵�Ă��Ȃ� true:�h�䒆
	bool mIn_Dodge;			//��𔻒�t���O false:������Ă��Ȃ� treu:���
	int mDodge_Time;		//��𔻒莞��
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��

	CXPlayer();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();
	//�Փˏ���
	//m:�����̃R���C�_ o:����̃R���C�_
	void Collision(CCollider* m, CCollider* o);

	static CXPlayer *spThis;		//�v���C���[�̃C���X�^���X �O���Q�Ɨp
	bool mIn_Light_Attack;	//��U������t���O false:�U�����Ă��Ȃ� true:�U����
	bool mIn_Strong_Attack;	//���U������t���O false:�U�����Ă��Ȃ� true:�U����
};

#endif
