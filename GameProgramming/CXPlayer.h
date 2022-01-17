#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CTaskManager.h"
#include "CBattleParam.h"

class CXPlayer : public CXCharacter
{
private:
	int mHp;	//プレイヤーHP
	bool mIn_Defense;		//防御判定フラグ false:防御していない true:防御中
	bool mIn_Dodge;			//回避判定フラグ false:回避していない treu:回避中
	int mDodge_Time;		//回避判定時間
	float mJump;			//ジャンプ初速
	bool mJump_Flag;		//ジャンプ判定フラグ false:着地している true:ジャンプ中
	int mInv_Cnt;			//無敵時間

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
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword;	//剣
	CCollider mColSphereFoot;	//足

	CXPlayer();

	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);

	void Update();
	//衝突処理
	//m:自分のコライダ o:相手のコライダ
	void Collision(CCollider* m, CCollider* o);

	static CXPlayer *spInstance;		//プレイヤーのインスタンス 外部参照用
	bool mIn_Light_Attack;	//弱攻撃判定フラグ false:攻撃していない true:攻撃中
	bool mIn_Strong_Attack;	//強攻撃判定フラグ false:攻撃していない true:攻撃中

	static void Generate();			//生成
	static void Release();			//解放
	CVector GetPos();				//位置取得
	CVector GetRot();				//角度取得（mY、ラジアン）

	static CXPlayer* GetInstance();

	void TaskCollision();

	void ChangeState(Character_State hState);
};

#endif
