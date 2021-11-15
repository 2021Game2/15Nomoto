
#include "ClEnemy.h"
#include "CUtil.h"
#include "CXPlayer.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CKey.h"
#include "CRes.h"
#include "main.h"

#define GRAVITY	(9.8f/60.0f/4.0f) 
#define BORDER_DIST 15.0f//�����������E�l
#define NEAR_ATTACK_DIST 5.0f //�ߋ����U���͈�

static const float move_speed = 0.03f;

ClEnemy::ClEnemy()
	:mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSylinderBody(this, nullptr, CVector(), 1.0f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
	, mColSphereShoulder(this, nullptr, CVector(0.0f, 1.0f, 0.0f), 1.5f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
	, m_State(ClEnemy::State_Idle)
	, m_pos(0.0f, 0.0f, 0.0f)
	, m_rot(0.0f, 0.0f, 0.0f)
	, m_vec(0.0f, 0.0f, 0.0f)
	, m_rad(0.5f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_target(0.0f, 0.0f, 0.0f)
	, m_LookTarget(0.0f, 0.0f, 0.0f)
	, m_IsAutoMove(false)
	, m_IsLook(false)
	, m_IsTrace(false)
	, m_TargetLen(0.0f)
	, m_move_dir(0.0f, 0.0f, 0.0f)
	, m_AiState(ClEnemy::AI_Idle)
	, m_score(0)
	, m_Hp(10)
	, m_HitVec(0.0f, 0.0f, 0.0f)
	, m_InvCnt(0)
	, m_KnockBackValue(0.0f)
	, m_IsAttackHit(false)
	, m_AttackMoveParam(0.0f)
{
	Init(&CRes::sKnight);
	ChangeState(State_Idle);
	mTag = EENEMY;
	ChangeAnimation(Anim_Idle1, true, 300);
	mColSphereSword0.mTag = CCollider::ESWORD;
	mColSphereSword1.mTag = CCollider::ESWORD;
	mColSphereSword2.mTag = CCollider::ESWORD;
	mColSphereBody.mTag = CCollider::EBODY;

	mColSphereShoulder.mTag = CCollider::ESWORD;
	//mColSphereSword0.IsRender = true;
	//mColSphereSword1.IsRender = true;
	//mColSphereSword2.IsRender = true;
	//mColSphereBody.IsRender = true;
	mColSylinderBody.mType = CCollider::ESYLINDER;
	mColSylinderBody.mTag = CCollider::EBODY;
	mColSylinderBody.mHeight = 5.0f;
	//mColSphereShoulder.IsRender = true;
}

ClEnemy::~ClEnemy()
{

}
void ClEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//�����s��̐ݒ�
	mColSphereBody.mpMatrix = &mpCombinedMatrix[1];
	mColSylinderBody.mpMatrix = &mpCombinedMatrix[1];
	//��
	mColSphereHead.mpMatrix = &mpCombinedMatrix[1];
	//��
	mColSphereShoulder.mpMatrix = &mpCombinedMatrix[1];
	//��
	mColSphereSword0.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword1.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword2.mpMatrix = &mpCombinedMatrix[26];
}

bool ClEnemy::IsCanAction()
{
	return !(m_State == State_Attack || m_State == State_Hit || m_State == State_Blow || m_State == State_Death);
}
bool ClEnemy::IsDamageAction()
{
	return (m_State == State_Hit || m_State == State_Blow || m_State == State_Death);
}
void ClEnemy::Update()
{
	AutoMoveUpdate();

	//�����L�[������͕����x�N�g����ݒ�
	CVector SideVec = Camera.GetMat().GetXVec();
	CVector FrontVec = Camera.GetMat().GetZVec();
	//�����ړ��̓J�b�g����
	SideVec.mY = 0.0f;
	FrontVec.mY = 0.0f;
	//���K������
	SideVec.Normalize();
	FrontVec.Normalize();

	float speed = 0.15f;//�ړ����x���b��ŃZ�b�g



	m_move_dir = m_move_dir.Normalize();

	//�ړ�����
	if (IsCanAction()) {
		if (m_move_dir.LengthSq() > 0 && m_TargetLen > 0.1f) {


			//���ʂ�3�����x�N�g���v�Z�ŎZ�o�����ق������m�����v�Z�ʂ����O����ꍇ�͋[���v�Z�Ōy�ʉ�
			//�[���x�N�g���v�Z
			Check tCheck = CUtil::GetCheck2D(m_move_dir.mX, m_move_dir.mZ, 0, 0, m_rot.mY);

			//��]���x�@degree�ɒ���
			float turnspeed = 0.5f;

			//�}�ȐU��Ԃ��}��
			if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

			//�ړ������փL��������������
			if (tCheck.cross > 0.0f) {
				m_rot.mY += tCheck.turn * turnspeed;
			}
			if (tCheck.cross < 0.0f) {
				m_rot.mY -= tCheck.turn * turnspeed;
			}

			//���W�ړ�
			m_pos += m_move_dir * move_speed;

			if (m_State != State_Jump) {
				ChangeState(State_Walk);
			}
		}
		else if (m_State != State_Jump) {
			ChangeState(State_Idle);
		}
	}

	//�̂�����v�Z
	if (m_State == State_Hit || m_State == State_Blow) m_pos += m_HitVec * m_KnockBackValue;

	if (m_State == State_Jump) {
		m_vec.mY -= GRAVITY;
	}
	m_pos += m_vec;

	//�W�����v���[�V�����`�F�b�N
	if (m_State == State_Jump) {
		//		if (m_vec.mY <= 0.0f && m_model.GetAnimationJam()!=Anim_Jump_Down) {
		//			m_model.ChangeAnimation(Anim_Jump_Down);
		//		}
	}

	//��ԍX�V
	StateUpdate();


	//�����_�ݒ�
	Camera.SetTarget(mPosition);

	//���f���̍��W��ݒ�
	mPosition = m_pos;
	//�\����180�x���]���Ă�̂Œ���
	CVector adjust_rot = m_rot;
	adjust_rot.mY += M_PI;
	mRotation = (adjust_rot) * (180.0f / M_PI);

	//���X�V
	CXCharacter::Update();

	m_move_dir.Set(0, 0, 0);

	//�U���Ҕ���p�̕]���X�V
	AttackerCheck();

	//CharaParam�X�V
	m_CharaParam.pos = m_pos;
	//���G���ԍX�V
	if (--m_InvCnt <= 0) m_InvCnt = 0;
}


void ClEnemy::Render()
{
	//���f���̕`��
	CXCharacter::Render();


}

void ClEnemy::AutoMoveUpdate()
{
	CXPlayer* tPlayer = CXPlayer::GetInstance();

	//��Ұ��݃`�F�b�N
	//static int no = 0;
	//if (CKey::Once('V')) {
	//	ChangeAnimation(no, true, 60);
	//	printf("no=%d\n", no);
	//	++no;
	//	no = no % Anim_End;
	//}

	//�����_���Ŏ����ړ�����X�V�e�X�g
	if (CKey::Push('Z')) {
		m_IsAutoMove = true;
		m_target = m_pos;
		m_target.mX += -30.0f + (float)(rand() % 60);
		m_target.mZ += -30.0f + (float)(rand() % 60);
	}
	//��������X�V�e�X�g
	//if (CKey::Push('X')) {
	//	m_IsLook = true;
	//	m_target = m_pos;
	//	m_target.mX += -30.0f + (float)(rand() % 60);
	//	m_target.mZ += -30.0f + (float)(rand() % 60);
	//}

	//�ǐՏ���
	if (m_IsTrace && !IsDamageAction()) {
		CVector vec = (CXPlayer::GetInstance()->GetPos() - m_pos);
		m_TargetLen = vec.Length();
		m_target = m_pos + vec * 0.8f;
		if (m_TargetLen <= NEAR_ATTACK_DIST) {
			//�����_���ōU���Ɉڍs
			if (rand() % 200 == 0) {
				ChangeAIState(AI_Attack);
			}
		}
		else if (m_TargetLen > BORDER_DIST) {
			ChangeAIState(AI_Idle);
		}
		else {
			m_IsLook = true;
			m_IsAutoMove = true;
		}
	}

	//�����ړ�����
	if (m_IsAutoMove) {
		CVector tmp = m_target - m_pos;
		float tLen = tmp.Length();
		tmp.mY = 0.0f;
		m_move_dir = tmp;
		if (tLen <= move_speed * 2.0f) {
			m_IsAutoMove = false;
		}
	}




	//�Ώۂ����鏈��
	if (m_IsLook && IsCanAction()) {
		Check tCheck = CUtil::GetCheck2D(m_target.mX, m_target.mZ, m_pos.mX, m_pos.mZ, m_rot.mY);
		float turnspeed = 0.5f;

		//�}�ȐU��Ԃ��}��
		if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;

		//�ړ������փL��������������
		if (tCheck.cross > 0.0f) {
			m_rot.mY += tCheck.turn * turnspeed;
		}
		if (tCheck.cross < 0.0f) {
			m_rot.mY -= tCheck.turn * turnspeed;
		}
	}

}




void ClEnemy::ChangeState(EnemyState hState)
{

	if (m_Hp <= 0) hState = State_Death;
	if (m_State != hState) {
		int tmp = rand() % 3;

		switch (hState) {
		case State_Idle:
			ChangeAnimation(Anim_Idle1, true, 300);
			break;
		case State_Walk:
			//�����A�j���[�V����
			ChangeAnimation(Anim_Walk, true, 70);
			break;
		case State_Run:
			//����A�j���[�V����
			ChangeAnimation(Anim_Walk, true, 50);
			break;
		case State_Jump:
			ChangeAnimation(Anim_Jump, false, 50);
			break;
		case State_Attack:
			m_AttackParam.Damage = 1;
			m_AttackParam.KnockBackValue = 0.1f;
			m_AttackParam.Type = HitType_Small;
			m_AttackMoveParam = 0.0f;
			if (tmp == 0) ChangeAnimation(Anim_Attack1, false, 80);
			if (tmp == 1) ChangeAnimation(Anim_Attack2, false, 95);
			if (tmp == 2) {
				ChangeAnimation(Anim_Attack6, false, 70);
				m_AttackParam.Damage = 2;
				m_AttackParam.KnockBackValue = 0.5f;
				m_AttackParam.Type = HitType_Large;
				m_AttackMoveParam = 0.08f;
			}
			m_IsAttackHit = true;
			break;
		case State_Hit:
			ChangeAIState(AI_Idle);
			ChangeAnimation(Anim_Hit1, false, 40);
			break;
		case State_Blow:
			ChangeAIState(AI_Idle);
			ChangeAnimation(Anim_Hit2, false, 40);
			break;
		case State_Death:
			ChangeAnimation(Anim_Death1, false, 100);
			break;
		}
		m_State = hState;
	}
}

void ClEnemy::SetPos(CVector hPos) {
	m_pos = hPos;
}

void ClEnemy::ClearScore() {
	m_score = 0;
}
void ClEnemy::AttackerCheck() {
	m_score = 0;

	//��ʓ��ɂ���Ȃ�v���X
	if (IsScreen()) {
		m_score += 5.0f;
	}
	//���łɍU���s�����Ȃ̂Ń`�F�b�N�ɂЂ�������悤�Ƀv���X
	if (IsAttack()) {
		m_score += 100000.0f;
	}
	//�_���[�W���Ȃ���Z
	if (IsDamage()) {
		m_score += 100.0f;
	}
	//�ʒu�֌W����X�R�A���Z
	m_score += PositionCheckScore();

	//����ł���Ό��Z
	if (m_Hp <= 0) {
		m_score = -100000.0f;
	}
	//	printf("score=%f\n", m_score);


}
bool ClEnemy::IsScreen() {
	CVector tScreenVec;
	//��ʓ�����
	if (Camera.WorldToScreen(&tScreenVec, m_pos)) {
		if (tScreenVec.mX <= WINDOW_WIDTH && tScreenVec.mY <= WINDOW_HEIGHT) {
			return true;
		}
	}
	else {
		return false;
	}

	return true;
}
bool ClEnemy::IsAttack() {
	return (m_AiState == AI_GetCloser || m_AiState == AI_Attack);
}
bool ClEnemy::IsDamage() {
	return (m_State == State_Hit || m_State == State_Blow);
}

//�v���C���[�Ƃ̋����ɉ����Ē��߂��ǂ����̔��ʏ��X�V
bool ClEnemy::PlayerTargetCheck(float* hNearScore) {
	if (m_State == State_Death) return false;
	CVector tpos = CXPlayer::GetInstance()->GetPos();
	float len = CVector(tpos - m_pos).Length();
	len = max(100.0f, len);
	m_NearScore = 100.0f - len;
	if (*hNearScore < m_NearScore) {
		*hNearScore = m_NearScore;//�X�V
		return true;
	}

	return false;

}
float ClEnemy::PositionCheckScore() {
	CXPlayer* target = CXPlayer::GetInstance();
	if (target == NULL) return 0.0f;

	float tScore = 0.0f;


	CVector tPos = target->GetPos();
	CVector tRot = target->GetRot();
	CVector tDir = tPos - m_pos;

	float len = tDir.Length();
	CVector RotVec(sinf(m_rot.mY), 0, cosf(m_rot.mY));
	RotVec.Normalize();

	//2D���ʏ�̈ʒu�֌W���v�Z
	Check tCheck = CUtil::GetCheck2D(tPos.mX, tPos.mZ, m_pos.mX, m_pos.mZ, m_rot.mY);
	//�w��ɂ���Ȃ�}�C�i�X
	if (tCheck.dot < 0.0f) tScore -= 10.0f;
	//���ʂɋ߂��قǃX�R�A�A�b�v
	tScore += tCheck.cos * 10.0f;

	if (len <= BORDER_DIST) {
		tScore += BORDER_DIST - len;
	}
	else {
		tScore -= 100000.0f;//���E�͈͊O�Ƃ��đ傫���}�C�i�X
	}

	//	printf("score=%f", tScore);
	//	tCheck.print();



	return tScore;
}

float ClEnemy::GetScore() const
{
	return m_score;
}
void ClEnemy::ChangeAIState(AIState hAiState) {
	if (m_Hp <= 0) {
		hAiState = AI_Idle;
	}
	if (IsDamageAction()) {
		m_IsLook = false;
		m_IsAutoMove = false;
		m_IsTrace = false;
		m_AiState = AI_Idle;
	}

	if (m_AiState != hAiState) {
		switch (hAiState) {
		case AI_Idle:
			m_IsLook = false;
			m_IsAutoMove = false;
			m_IsTrace = false;
			break;
		case AI_GetCloser:
			m_IsTrace = true;
			break;
		case AI_Attack:
			m_IsLook = true;
			m_IsAutoMove = false;
			ChangeState(State_Attack);
			break;
		}
		m_AiState = hAiState;
		m_score = 0.0f;
	}
}
void ClEnemy::StateUpdate()
{
	switch (m_State) {
	case State_Attack:
		//�U�����̈ړ��W���ňړ�����
		if (m_AttackMoveParam > 0.0f) {
			CVector tmp(sinf(m_rot.mY), 0, cosf(m_rot.mY));
			m_CharaParam.MoveDir = tmp;
			m_pos += tmp * m_AttackMoveParam;
		}
		//�q�b�g����
		if (IsAnimationEnd()) {
			ChangeState(State_Idle);
			m_IsAttackHit = false;
		}
		break;
	case State_Hit:
	case State_Blow:
		//�q�b�g����
		if (IsAnimationEnd()) {
			ChangeState(State_Idle);
		}
		break;

	}

	switch (m_AiState) {
	case AI_Attack:
		if (IsAnimationEnd()) {
			ChangeState(State_Idle);
		}
		break;
	}
}
CVector ClEnemy::GetPos()
{
	return m_pos;
}
void ClEnemy::Collision(CCollider* m, CCollider* o)
{
	if (m->mType == CCollider::ESPHERE)
	{
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EPLAYER && (m->mTag == CCollider::ESWORD) && m_IsAttackHit)
			{
				if (CCollider::Collision(m, o))
				{
					CXPlayer* tPlayer = (CXPlayer*)o->mpParent;
				}
			}
		}
	}
}

void ClEnemy::TakeDamage(const stAttackParam& hAttackParam, const stCharaParam& hCharaParam)
{
	if (m_InvCnt <= 0) {
		m_Hp -= hAttackParam.Damage;
		m_InvCnt = 15;//���G���Ԑݒ�@�v����
		if (m_Hp <= 0) {
			ChangeState(State_Death);
		}
		else {
			m_KnockBackValue = hAttackParam.KnockBackValue;
			if (hAttackParam.Type == HitType_Small) {
				m_HitVec = (m_pos - hCharaParam.pos).Normalize();
				ChangeState(State_Hit);
			}
			else if (hAttackParam.Type == HitType_Large) {
				m_HitVec = hCharaParam.MoveDir;
				ChangeState(State_Blow);
			}
		}
	}
}






