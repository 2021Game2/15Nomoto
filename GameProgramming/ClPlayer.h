//#ifndef CLPLAYER_H
//#define CLPALYER_H
//
//#include "CXCharacter.h"
//#include "CCollider.h"
//#include "CBattleParam.h"
//
//class ClPlayer : public CXCharacter
//{
//private:
//	enum PlayerState {
//		State_Idle = 0,
//		State_Walk,
//		State_Jump,
//		State_Attack,
//		State_AttackUpdate,
//		State_Damage,
//		State_Death
//	};
//	enum AttackType {
//		AType_Normal = 0,
//		AType_Move,
//		AType_Dash,
//	};
//	enum Anim {
//		Anim_Idle = 0,
//		Anim_Walk,
//		Anim_Hit,
//		Anim_AttackA,
//		Anim_AttackToIdle,
//		Anim_AttackAtoB,
//		Anim_AttackBtoIdle,
//		Anim_AttackBtoC,
//		Anim_AttackCtoIdle,
//		Anim_AttackDash,
//		Anim_AttackDashToIdle,
//		Anim_Death,
//		Anim_End
//	};
//
//	static ClPlayer* m_Instance;
//
//	//�R���C�_�̐錾
//	CCollider mColSphereBody;	//��
//	CCollider mColSphereHead;	//��
//	CCollider mColSphereSword;	//��
//	CCollider mColSylinderBody;	//��
//
//	//���[�V�����L���f���N���X
//	//���W
//	CVector m_pos;
//	//��]
//	CVector m_rot;
//	//�ړ��x�N�g��
//	CVector m_vec;
//	//���a
//	float m_rad;
//
//	PlayerState m_State;
//	AttackType	m_AttackType;
//	//�J�����֘A--------------
//	//�J�����̈ʒu
//	CVector m_cam_pos;
//	//�J�����̉�]�l
//	CVector m_cam_rot;
//	//�J�����̋���
//	float m_cam_dist;
//
//	//------------------------
//	//����
//
//	CVector m_velocity;	//�����x
//
//	CVector m_target;	//�ڕW�_
//	CVector m_LookTarget;
//	bool m_IsAutoMove;
//	bool m_IsLook;
//
//	CVector m_move_dir;
//
//	int		m_ComboCnt;//�R���{�J�E���g
//	bool	m_IsCombo;//�R���{�p���t���O
//	float	m_AttackMoveParam;//�U�����̈ړ��ʌv�Z�p�W��
//
//	bool	m_IsAttackHit;//�U���^�C�~���O
//	int		m_InvCnt;		//���G����
//	int		m_Hp;
//	CVector m_HitVec;		//�q�b�g���̂̂�����x�N�g��
//	float	m_KnockBackValue;	//�̂�����W��
//
//	stAttackParam	m_AttackParam;
//	stCharaParam	m_CharaParam;
//
//public:
//	ClPlayer();
//	~ClPlayer();
//
//	static void Generate();			//����
//	static void Release();			//���
//	static ClPlayer* GetInstance();	//�C���X�^���X�擾
//
//	void Init(CModelX* model);		//������
//	void Update();					//�X�V
//	void Render();					//�`��
//	void StateUpdate();				//�X�e�[�g�̍X�V��
//	void ChangeState(PlayerState hState);//�X�e�[�g�ύX����
//	bool IsCanAction();				//�U���\��ԃ`�F�b�N
//	bool IsDamageAction();			//�_���[�W�����`�F�b�N
//	CVector GetPos();				//�ʒu�擾
//	CVector GetRot();				//�p�x�擾�imY�A���W�A���j
//	void AutoMoveUpdate();			//�����s���֘A�X�V
//
//	//�Փˏ���
//	//m:�����̃R���C�_ o:����̃R���C�_
//	void Collision(CCollider* m, CCollider* o);
//
//	//��e����
//	void TakeDamage(const stAttackParam& hAttackParam, const stCharaParam& hCharaParam);
//
//
//};
//
//#endif