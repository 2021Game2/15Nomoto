#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"

class CXPlayer : public CXCharacter
{
private:
	int mHp;	//プレイヤーHP
	bool mAttack;	//弱攻撃切り替え用判定フラグ false:右から振りかぶり true:左から振りかぶり
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
};

#endif
