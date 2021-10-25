#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
private:
	int mHp;	//プレイヤーHP
	bool mAttack_switch;	//弱攻撃切り替え用判定フラグ false:右から振りかぶり true:左から振りかぶり
	bool mIn_Defense;		//防御判定フラグ false:防御していない true:防御中
	bool mIn_Dodge;			//回避判定フラグ false:回避していない treu:回避中
	int mDodge_Time;		//回避判定時間
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereSword;	//剣

	CXPlayer();

	/*
	初期化(Xモデルクラスのポインタ)
	*/
	void Init(CModelX* model);

	void Update();
	//衝突処理
	//m:自分のコライダ o:相手のコライダ
	void Collision(CCollider* m, CCollider* o);

	static CXPlayer *spThis;		//プレイヤーのインスタンス 外部参照用
	bool mIn_Light_Attack;	//弱攻撃判定フラグ false:攻撃していない true:攻撃中
	bool mIn_Strong_Attack;	//強攻撃判定フラグ false:攻撃していない true:攻撃中
};

#endif
