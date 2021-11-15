#ifndef CBATTLEPARAM_H
#define CBATTLEPARAM_H

#include "CVector.h"

//�U�����󂯂��Ƃ��̑召����p
enum EHitType {
	HitType_Small = 0,
	HitType_Large,
};

//�U����ԃp�����[�^
struct stAttackParam {
	int Damage;				//�_���[�W�l
	float KnockBackValue;	//�m�b�N�o�b�N��
	EHitType Type;			//�q�b�g���̃^�C�v
};

//���p�����[�^�@�U�����ɑ���ɓn���p�����[�^
struct stCharaParam {
	CVector pos;		//�ʒu���
	CVector MoveDir;	//�U�����̕����ێ��p
};

#endif
