#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include "CCharacter.h"
/*
ビルボードクラス
常にカメラの方を向く四角形
*/
class CBillBoard : public CCharacter {
public:
	//三角形2つ
	CTriangle mT[2];
	//マテリアル
	CMaterial mMaterial;
	//拡縮
	float mBillBoardScale;
	//UV
	CVector mUv[4];
	//法線
	CVector mN[4];
	//コンストラクタ
	CBillBoard();
	//CBillBoard(位置, スケール, 回転)
	CBillBoard(CVector pos, float scale, float rotate);
	//位置と大きさの設定
	//Set(位置, スケール, 回転)
	void Set(CVector pos, float scale, float rotate);
	//更新
	void Update();
	//描画
	void Render();
	void Render(CMaterial *mpMaterial);
};
#endif
