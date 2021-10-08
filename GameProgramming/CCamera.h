#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
/*
カメラクラス
*/
#define DEF_CAMERA_DIST 10.0f
#define DEF_CAMERA_HEAD_ADJUST 3.0f
class CCamera {
public:
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;

	CMatrix Matrix;

	//重複するがカメラ制御用
	CVector mPos;		//位置
	CVector mTarget;	//ターゲット
	float	mAngleX;	//アングル
	float	mAngleY;	//アングル
	float	mDist;	//距離

	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);

	void SetTarget(const CVector& target);

	//カメラ初期化
	void Init();

	//カメラ更新処理
	void Update();

	//カメラ適用
	void Render();
};

//カメラの外部参照
extern CCamera Camera;
#endif
