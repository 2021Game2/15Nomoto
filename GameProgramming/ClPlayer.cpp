//#include "ClPlayer.h"
////#include "Map.h"
//#include "CUtil.h"
//#include "CCamera.h"
//#include "CEnemyManager.h"
//#include "CKey.h"
//#define _USE_MATH_DEFINES
//#include <math.h>
//
//#define GRAVITY	(9.8f/60.0f/4.0f) 
//
//
//ClPlayer* ClPlayer::m_Instance;
//static const float move_speed = 0.1f;
//
//ClPlayer::ClPlayer()
//	:mColSphereBody(this, nullptr, CVector(), 0.5f)
//	, mColSylinderBody(this, nullptr, CVector(), 1.0f)
//	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
//	, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
//	, m_State(ClPlayer::State_Idle)
//	, m_AttackType(ClPlayer::AType_Normal)
//	, m_pos(0.0f, 0.0f, 0.0f)
//	, m_rot(0.0f, 0.0f, 0.0f)
//	, m_vec(0.0f, 0.0f, 0.0f)
//	, m_rad(0.5f)
//	, m_cam_pos(0.0f, 0.0f, 0.0f)
//	, m_cam_rot(0.0f, 0.0f, 0.0f)
//	, m_cam_dist(5)
//	, m_velocity(0.0f, 0.0f, 0.0f)
//	, m_target(0.0f, 0.0f, 0.0f)
//	, m_LookTarget(0.0f, 0.0f, 0.0f)
//	, m_IsAutoMove(false)
//	, m_IsLook(false)
//	, m_move_dir(0.0f, 0.0f, 0.0f)
//	, m_ComboCnt(0)
//	, m_IsCombo(false)
//	, m_AttackMoveParam(0.0f)
//	, m_IsAttackHit(false)
//	, m_InvCnt(0)
//	, m_Hp(10)
//	, m_HitVec(0.0f, 0.0f, 0.0f)
//	, m_KnockBackValue(0.0f)
//{
//	//タグにプレイヤーを設定します
//	mTag = EPLAYER;
//	mColSphereSword.mTag = CCollider::ESWORD;
//	mColSphereBody.mTag = CCollider::EBODY;
//	//mColSphereBody.IsRender = true;
//	mColSylinderBody.mTag = CCollider::EBODY;
//	mColSylinderBody.mType = CCollider::ESYLINDER;
//	mColSylinderBody.mHeight = 6.0f;
//}
//
//ClPlayer::~ClPlayer()
//{
//
//}
//
//void ClPlayer::Generate()
//{
//	m_Instance = new ClPlayer;
//}
//void ClPlayer::Release()
//{
//	if (m_Instance) {
//		delete m_Instance;
//		m_Instance = NULL;
//	}
//}
//
//ClPlayer* ClPlayer::GetInstance()
//{
//	return m_Instance;
//}
//
//void ClPlayer::Init(CModelX* model)
//{
//	CXCharacter::Init(model);
//	//合成行列の設定
//	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
//	mColSylinderBody.mpMatrix = &mpCombinedMatrix[1];
//	//頭
//	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
//	//剣
//	mColSphereSword.mpMatrix = &mpCombinedMatrix[22];
//
//	mRotation.mY = 0.01f;
//}
//
//bool ClPlayer::IsCanAction()
//{
//	return !(m_State == State_Attack || m_State == State_AttackUpdate || m_State == State_Damage || m_State == State_Death);
//}
//bool ClPlayer::IsDamageAction()
//{
//	return (m_State == State_Damage || m_State == State_Death);
//}
//CVector ClPlayer::GetPos() {
//	return m_pos;
//}
//CVector ClPlayer::GetRot()
//{
//	return m_rot;
//}
//void ClPlayer::Update()
//{
//
//	AutoMoveUpdate();
//
//
//
//	//方向キーから入力方向ベクトルを設定
//	CVector SideVec = Camera.GetMat().GetXVec();
//	CVector FrontVec = Camera.GetMat().GetZVec();
//	//高さ移動はカットする
//	SideVec.mY = 0.0f;
//	FrontVec.mY = 0.0f;
//	//正規化する
//	SideVec.Normalize();
//	FrontVec.Normalize();
//
//	float speed = 0.15f;
//
//	if (IsCanAction()) {
//		if (CKey::Push('A')) m_move_dir -= SideVec;
//		if (CKey::Push('D')) m_move_dir += SideVec;
//		if (CKey::Push('W')) m_move_dir += FrontVec;
//		if (CKey::Push('S')) m_move_dir -= FrontVec;
//	}
//
//	//if (m_IsAttackHit && m_AttackParam.Type == HitType_Small) {
//	//	//攻撃中相手の方向を向く
//	//	ClEnemy* tEnemy = ClEnemyManager::GetInstance()->GetNearEnemy();
//	//	if (tEnemy) {
//	//		m_move_dir = (tEnemy->GetPos() - m_pos);
//	//	}
//
//	//}
//
//	m_move_dir = m_move_dir.Normalize();
//
//	if (CKey::Push(VK_SPACE)) {
//		//m_velocity.y = 0.5f;
//		m_vec.mY = 0.7f;
//		ChangeState(State_Jump);
//	}
//
//	if (CKey::Once('J')) {
//		if (IsCanAction()) {
//			ChangeState(State_Attack);
//		}
//		else {
//			if (m_State == State_AttackUpdate) {
//				m_IsCombo = true;
//			}
//		}
//	}
//
//
//	if (m_move_dir.LengthSq() > 0) {
//		//普通に3次元ベクトル計算で算出したほうが正確だが計算量を懸念する場合は擬似計算で軽量化
//		//擬似ベクトル計算
//		Check tCheck = CUtil::GetCheck2D(m_move_dir.mX, m_move_dir.mZ, 0, 0, m_rot.mY);
//
//		//回転速度　degreeに直す
//		float turnspeed = 0.5f;
//
//		//急な振り返りを抑制
//		if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;
//
//		//移動方向へキャラを向かせる
//		if (tCheck.cross > 0.0f) {
//			m_rot.mY += tCheck.turn * turnspeed;
//		}
//		if (tCheck.cross < 0.0f) {
//			m_rot.mY -= tCheck.turn * turnspeed;
//		}
//	}
//
//
//	if (IsCanAction()) {
//		if (m_move_dir.LengthSq() > 0) {
//
//			//座標移動
//			m_pos += m_move_dir * move_speed;
//
//			if (m_State != State_Jump) {
//				ChangeState(State_Walk);
//			}
//		}
//		else if (m_State != State_Jump) {
//			ChangeState(State_Idle);
//		}
//	}
//
//	//のけぞり計算
//	if (m_State == State_Damage) m_pos += m_HitVec * m_KnockBackValue;
//
//
//	if (m_State == State_Jump) {
//		m_vec.mY -= GRAVITY;
//	}
//	m_pos += m_vec;
//
//	//ジャンプモーションチェック
//	if (m_State == State_Jump) {
//		//		if (m_vec.mY <= 0.0f && m_model.GetAnimationJam()!=Anim_Jump_Down) {
//		//			m_model.ChangeAnimation(Anim_Jump_Down);
//		//		}
//	}
//
//	StateUpdate();
//
//
//
//	//カメラ操作
//	//注視点設定
//	Camera.SetTarget(mPosition);
//
//	//モデルの座標を設定
//	mPosition = m_pos;
//	mRotation = m_rot * (180.0f / M_PI);
//
//	CXCharacter::Update();
//
//	m_move_dir.Set(0, 0, 0);
//
//	//CharaParam更新
//	m_CharaParam.pos = m_pos;
//
//	//無敵時間更新
//	if (--m_InvCnt <= 0) m_InvCnt = 0;
//}
//
//
//void ClPlayer::Render()
//{
//	CXCharacter::Render();
//
//}
//
//void ClPlayer::AutoMoveUpdate()
//{
//	//実験用
//	//static int no = 0;
//	//if (CKey::Once('V')) {
//	//	ChangeAnimation(no, true, 120);
//	//	printf("no=%d\n", no);
//	//	++no;
//	//	no = no % Anim_End;
//	//}
//	//if (CKey::Once('Z')) {
//	//	m_IsAutoMove = true;
//	//	m_target = m_pos;
//	//	m_target.mX += -30.0f + (float)(rand() % 60);
//	//	m_target.mZ += -30.0f + (float)(rand() % 60);
//	//}
//	//if (CKey::Once('X')) {
//	//	m_IsLook = true;
//	//	m_IsAutoMove = true;
//	//	//m_target = m_pos;
//	//	//m_target.mX += -30.0f + (float)(rand() % 60);
//	//	//m_target.mZ += -30.0f + (float)(rand() % 60);
//
//	//	m_target = clEnemyManager::GetInstance()->GetNearEnemy()->GetPos();
//
//	//}
//
//	//敵生成　ランダム箇所に配置
//	if (CKey::Once('C')) {
//
//		ClEnemyManager::GetInstance()->EnemyGenerate(1);
//	}
//
//	//自動移動処理
//	if (m_IsAutoMove) {
//		CVector tmp = m_target - m_pos;
//		float tLen = tmp.Length();
//		tmp.mY = 0.0f;
//		m_move_dir = tmp;
//		if (tLen <= move_speed * 2.0f) {
//			m_IsAutoMove = false;
//		}
//	}
//	//視線ロック処理
//	if (m_IsLook && IsDamageAction()) {
//		Check tCheck = CUtil::GetCheck2D(m_target.mX, m_target.mZ, m_pos.mX, m_pos.mZ, m_rot.mY);
//		float turnspeed = 0.5f;
//
//		//急な振り返りを抑制
//		if (tCheck.turn > 1.5f) tCheck.turn = 1.5f;
//
//		//移動方向へキャラを向かせる
//		if (tCheck.cross > 0.0f) {
//			m_rot.mY += tCheck.turn * turnspeed;
//		}
//		if (tCheck.cross < 0.0f) {
//			m_rot.mY -= tCheck.turn * turnspeed;
//		}
//	}
//
//}
//
//
//
//
//void ClPlayer::ChangeState(PlayerState hState)
//{
//	switch (hState) {
//	case State_Idle:
//		ChangeAnimation(Anim_Idle, true, 60);
//		break;
//	case State_Walk:
//		//走りアニメーション
//		ChangeAnimation(Anim_Walk, true, 60);
//		break;
//	case State_Jump:
//		break;
//	case State_Attack:
//		ChangeAnimation(Anim_AttackA, false, 15);
//		m_IsCombo = false;
//		m_AttackType = AType_Normal;
//		m_AttackMoveParam = 0.05f;
//		m_IsAttackHit = true;
//		m_AttackParam.Damage = 1;
//		m_AttackParam.Type = HitType_Small;
//		m_AttackParam.KnockBackValue = 0.05f;
//		hState = State_AttackUpdate;
//
//		break;
//	case State_Damage:
//		ChangeAnimation(Anim_Hit, false, 20);
//		break;
//	case State_Death:
//		ChangeAnimation(Anim_Death, false, 20);
//		break;
//	}
//
//	m_State = hState;
//}
//
//
//void ClPlayer::StateUpdate()
//{
//	switch (m_State) {
//	case State_AttackUpdate:
//		//攻撃時の移動係数で移動処理
//		if (m_AttackMoveParam > 0.0f) {
//			CVector tmp(sinf(m_rot.mY), 0, cosf(m_rot.mY));
//			m_CharaParam.MoveDir = tmp;
//			m_pos += tmp * m_AttackMoveParam;
//		}
//		if (IsAnimationEnd()) {
//			switch (mAnimationIndex) {
//			case Anim_AttackToIdle:
//			case Anim_AttackBtoIdle:
//			case Anim_AttackCtoIdle:
//			case Anim_AttackDashToIdle:
//				ChangeState(State_Idle);
//				m_IsCombo = false;
//				return;
//				break;
//			}
//			if (m_IsCombo) {
//				switch (mAnimationIndex) {
//				case Anim_AttackA:
//					ChangeAnimation(Anim_AttackAtoB, false, 20);
//					//						m_AttackMoveParam = 0.0f;
//					m_AttackMoveParam = 0.07f;
//					m_AttackParam.KnockBackValue = 0.1f;
//					break;
//				case Anim_AttackAtoB:
//					ChangeAnimation(Anim_AttackBtoC, false, 30);
//					m_AttackMoveParam = 0.2f;
//					m_AttackParam.Damage = 3;
//					m_AttackParam.KnockBackValue = 0.2f;
//					m_AttackParam.Type = HitType_Large;
//
//					break;
//				}
//
//				m_IsCombo = false;
//			}
//			else {
//				bool IsUpdate = false;
//				switch (mAnimationIndex) {
//				case Anim_AttackA:
//					ChangeAnimation(Anim_AttackToIdle, false, 20);
//					IsUpdate = true;
//					break;
//
//				case Anim_AttackAtoB:
//					ChangeAnimation(Anim_AttackBtoIdle, false, 20);
//					IsUpdate = true;
//					break;
//
//				case Anim_AttackBtoC:
//					ChangeAnimation(Anim_AttackCtoIdle, false, 20);
//					IsUpdate = true;
//					break;
//
//				case Anim_AttackDash:
//					ChangeAnimation(Anim_AttackDashToIdle, false, 20);
//					IsUpdate = true;
//					break;
//				}
//				if (IsUpdate) {
//					m_AttackMoveParam = 0.0f;
//					m_IsAttackHit = false;
//				}
//			}
//		}
//
//		break;
//	case State_Damage:
//		if (IsAnimationEnd()) {
//			ChangeState(State_Idle);
//		}
//		break;
//	}
//}
//
//
//void ClPlayer::Collision(CCollider* m, CCollider* o)
//{
//	//カプセル同士はまだ不完全
//	//if (m->mType == CCollider::ECAPSULE)
//	//{
//	//	if (o->mType == CCollider::ECAPSULE)
//	//	{
//	//		//本体同士のコリジョン判定
//	//		if (m->mpParent->mTag == EPLAYER && o->mpParent->mTag == EENEMY && m->mTag == CCollider::EBODY && o->mTag == CCollider::EBODY)
//	//		{
//	//			CVector adjust;
//	//			if (CCollider::CollisionCapsule(m, o, &adjust)) {
//
//	//				CVector tmp = (o->mPosition * *o->mpMatrix) - (m->mPosition * *m->mpMatrix);
//	//				float len = tmp.Length();
//	//				float rad = m->mRadius + o->mRadius;
//	//				float t = (rad - len) * 1.1f;
//	//				CVector Push = (tmp * t);
//	//				Push.mY = 0.0f;
//	//				clEnemy* tEnemy = (clEnemy*)o->mpParent;
//	//				//					tEnemy->SetPos(tEnemy->GetPos() + adjust);
//	//				tEnemy->SetPos(tEnemy->GetPos() + Push);
//	//			}
//	//		}
//
//	//	}
//	//}
//	//シリンダー同士の判定
//	if (m->mType == CCollider::ESYLINDER)
//	{
//		if (o->mType == CCollider::ESYLINDER)
//		{
//			//本体同士のコリジョン判定
//			if (m->mpParent->mTag == EPLAYER && o->mpParent->mTag == EENEMY && m->mTag == CCollider::EBODY && o->mTag == CCollider::EBODY)
//			{
//				CVector adjust;
//				if (CCollider::CollisionSylinder(m, o, &adjust)) {
//					ClEnemy* tEnemy = (ClEnemy*)o->mpParent;
//					tEnemy->SetPos(tEnemy->GetPos() + adjust);
//				}
//			}
//
//		}
//	}
//
//
//	if (m->mType == CCollider::ESPHERE)
//	{
//		if (o->mType == CCollider::ESPHERE)
//		{
//			//攻撃用
//			if (o->mpParent->mTag == EENEMY && m->mTag == CCollider::ESWORD && m_State == State_AttackUpdate && m_IsAttackHit)
//			{
//				if (CCollider::Collision(m, o))
//				{
//					ClEnemy* tEnemy = (ClEnemy*)o->mpParent;
//					tEnemy->TakeDamage(m_AttackParam, m_CharaParam);
//				}
//			}
//		}
//	}
//}
//
//void ClPlayer::TakeDamage(const stAttackParam& hAttackParam, const stCharaParam& hCharaParam)
//{
//	if (m_InvCnt <= 0) {
//		m_Hp -= hAttackParam.Damage;
//		m_InvCnt = 30;//無敵時間設定　要調整
//		if (m_Hp <= 0) {
//			ChangeState(State_Death);
//		}
//		else {
//			m_KnockBackValue = hAttackParam.KnockBackValue;
//			m_HitVec = (m_pos - hCharaParam.pos).Normalize();
//			ChangeState(State_Damage);
//		}
//	}
//}