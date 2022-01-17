#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter.h"

class CXCharacter : public CCharacter {
public:
	CModelX* mpModel;	//モデルデータ
	int mAnimationIndex;	//アニメーション番号
	bool mAnimationLoopFlg;	//true:アニメーションを繰り返す
	float mAnimationFrame; //アニメーションの再生フレーム
	float mAnimationFrameSize;//アニメーションの再生フレーム数
	CMatrix* mpCombinedMatrix;	//合成行列退避
	CXCharacter();
	~CXCharacter()
	{
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	//初期化処理
	void Init(CModelX* model);
	//アニメーションの変更
	void ChangeAnimation(int index, bool loop, float framesize);
	bool IsAnimationEnd();
	//更新処理
	void Update(CMatrix& m);
	void Update();
	//描画処理
	void Render();

	enum Character_State {
		State_Idle = 0,
		State_Walk,
		State_Run,
		State_Dodge,
		State_Jump,
		State_Attack,
		State_Light_Attack,
		State_Strong_Attack,
		State_Hit,
		State_Blow,
		State_Death,
	};
};

#endif
