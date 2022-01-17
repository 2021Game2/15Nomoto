#ifndef CLENEMY_H
#define CLENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CBattleParam.h"

class ClEnemyManager;

//�G�L�����N���X
class ClEnemy : public CXCharacter {
	friend class ClEnemyManager;
private:
	/*enum EnemyState {
		State_Idle = 0,
		State_Walk,
		State_Run,
		State_Jump,
		State_Attack,
		State_Hit,
		State_Blow,
		State_Death,
	};*/
	enum AIState {
		AI_Idle = 0,
		AI_GetCloser,	//�߂Â�
		AI_LongDistance,//�������Ƃ�
		AI_Attack,		//�U��
	};
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
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereShoulder;//��
	CCollider mColSylinderBody;	//��
private:

	//���W
	CVector m_pos;
	//��]
	CVector m_rot;
	//�ړ��x�N�g��
	CVector m_vec;
	//���a
	float m_rad;

	//���
	Character_State m_State;


	//����

	CVector m_velocity;		//�����x

	CVector m_target;		//�ڕW�_
	CVector m_LookTarget;	//�����ڕW�_
	bool m_IsAutoMove;		//�����ړ��t���O
	bool m_IsLook;			//������]�t���O
	bool m_IsTrace;			//�Ώۂ�ǂ�
	float m_TargetLen;		//�ΏۂƂ̋���
	CVector m_move_dir;		//�ړ�����

	//AI���ʗp
	AIState m_AiState;		//AI���
	float m_score;			//AI���f�p�X�R�A�ێ��p
	float m_NearScore;		//�ߋ������ʗp

	//�Q�[���p
	int		m_Hp;				//�̗�
	CVector m_HitVec;			//�q�b�g���̂̂�����x�N�g��
	int		m_InvCnt;			//���G����
	float	m_KnockBackValue;	//�̂�����W��
	float	m_AttackMoveParam;	//�U�����ړ��p�����[�^
	stCharaParam	m_CharaParam;	//�U�����n�����p�����[�^

public:
	ClEnemy();
	~ClEnemy();

	void Init(CModelX* model);	//������
	void Update();				//�X�V
	void Render();				//�`��
	void StateUpdate();			//��ԍX�V����
	void ChangeState(Character_State hState);//��ԕύX����
	bool IsCanAction();			//�A�N�V�����\�`�F�b�N
	bool IsDamageAction();		//�_���[�W�����`�F�b�N
	void SetPos(CVector hPos);	//�ʒu�ݒ�

	void AutoMoveUpdate();		//�����s���X�V

	void ClearScore();			//����p���l�N���A
	void AttackerCheck();		//�U���Q���`�F�b�N
	bool IsScreen();			//��ʓ��ɂ��邩�ǂ���
	bool IsAttack();			//�U�������U���\���R
	bool IsDamage();			//�_���[�W�������Ă���
	bool PlayerTargetCheck(float* hNearScore);//��^�[�Q�b�g����p
	float PositionCheckScore();	//�ʒu�֌W����X�R�A�Z�o

	float GetScore() const;		//�X�R�A��Ԃ�
	void ChangeAIState(AIState hAiState);//AI�ύX

	CVector GetPos();			//�ʒu�擾

	//�Փˏ���
	//m:�����̃R���C�_ o:����̃R���C�_
	void Collision(CCollider* m, CCollider* o);

	bool	m_IsAttackHit;		//�U������t���O
	static ClEnemy* GetInstance();
	static ClEnemy* spInstance;		//�G�̃C���X�^���X �O���Q�Ɨp
};

#endif