#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CCharacter.h"
/*
ビルボードクラス
常にカメラの方を向く四角形
*/
class CBillBoard2 : public CCharacter {
	CMatrix mMatrixModelView;
	CMatrix mCameraInverse;
public:
	//三角形2つ
	CTriangle mT[2];
	//マテリアル
	CMaterial mMaterial;
	//コンストラクタ
	CBillBoard2();
	//CBillBoard(位置, 幅, 高さ)
	CBillBoard2(CVector pos, float w, float h);
	//位置と大きさの設定
	//Set(位置, 幅, 高さ)
	void Set(CVector pos, float w, float h);
	//更新
	void Update();
	//描画
	void Render();
	void Render(CMaterial* mpMaterial);
};
#endif

