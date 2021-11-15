#ifndef CBATTLEPARAM_H
#define CBATTLEPARAM_H

#include "CVector.h"

//攻撃を受けたときの大小判定用
enum EHitType {
	HitType_Small = 0,
	HitType_Large,
};

//攻撃状態パラメータ
struct stAttackParam {
	int Damage;				//ダメージ値
	float KnockBackValue;	//ノックバック量
	EHitType Type;			//ヒット時のタイプ
};

//情報パラメータ　攻撃時に相手に渡すパラメータ
struct stCharaParam {
	CVector pos;		//位置情報
	CVector MoveDir;	//攻撃時の方向保持用
};

#endif
