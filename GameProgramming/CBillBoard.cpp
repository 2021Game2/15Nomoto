#include "CBillBoard.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

//Taskのプライオリティを一番後ろにくるようにCCharacterの引数を１に
CBillBoard::CBillBoard()
	:CCharacter(1), mBillBoardScale(1.0f)
{
}


CBillBoard::CBillBoard(CVector pos, float scale, float rotate)
	: CCharacter(1), mBillBoardScale(scale)
{
	Set(pos, scale, rotate);
}

void CBillBoard::Set(CVector pos, float scale, float rotate) {
	//位置
	mPosition = pos;
	//大きさの設定
	mBillBoardScale = scale;
	mRotation.mZ = rotate;
	for (int i = 0; i < 4; i++) {
		mN[i] = CVector(0.0f, 0.0f, 1.0f);
	}

	//色を白色を設定
	mMaterial.mDiffuse[0] = mMaterial.mDiffuse[1] =
		mMaterial.mDiffuse[2] = mMaterial.mDiffuse[3] = 1.0f;
}


void CBillBoard::Update() {
	////カメラへの方向ベクトルの取得
	//CVector dir = Camera.mEye - mPosition;
	////Y軸の回転値を求める
	//mRotation.mY = atan2f(dir.mX, dir.mZ) * 180.0f / M_PI;
	////X軸の回転値を求める
	//mRotation.mX = asinf(-dir.mY / dir.Length()) * 180.0f / M_PI;
	////行列の更新
	//CTransform::Update();
}

void CBillBoard::Render()
{
	Render(&mMaterial);
}
//Render(マテリアルのポインタ)
void CBillBoard::Render(CMaterial *mpMaterial) {
	CMatrix mat;
	mat = Camera.GetMat();

	float	x1, x2, y1, y2, s, c;
	CVector		v[4];

	//mRotation.mZ += 0.1f;//テストで回転
	//mBillBoardScale += 0.5f;//テストで縮尺

	s = sinf(mRotation.mZ) * mBillBoardScale;
	c = cosf(mRotation.mZ) * mBillBoardScale;
	//	頂点設定
	x1 = s - c;
	x2 = c + s;
	y1 = c + s;
	y2 = c - s;

	//左上左下右上右下の順

	v[0].mX = (mat.m00 * x1 + mat.m10 * y1) + mPosition.mX;
	v[0].mY = (mat.m01 * x1 + mat.m11 * y1) + mPosition.mY;
	v[0].mZ = (mat.m02 * x1 + mat.m12 * y1) + mPosition.mZ;
	v[1].mX = -(mat.m00 * x2 + mat.m10 * y2) + mPosition.mX;
	v[1].mY = -(mat.m01 * x2 + mat.m11 * y2) + mPosition.mY;
	v[1].mZ = -(mat.m02 * x2 + mat.m12 * y2) + mPosition.mZ;
	v[2].mX = (mat.m00 * x2 + mat.m10 * y2) + mPosition.mX;
	v[2].mY = (mat.m01 * x2 + mat.m11 * y2) + mPosition.mY;
	v[2].mZ = (mat.m02 * x2 + mat.m12 * y2) + mPosition.mZ;
	v[3].mX = -(mat.m00 * x1 + mat.m10 * y1) + mPosition.mX;
	v[3].mY = -(mat.m01 * x1 + mat.m11 * y1) + mPosition.mY;
	v[3].mZ = -(mat.m02 * x1 + mat.m12 * y1) + mPosition.mZ;


	//行列の保存
	glPushMatrix();
	//拡縮、回転、移動させる
//	glMultMatrixf(mMatrix.mM[0]);
	//ライトオフ
	glDisable(GL_LIGHTING);
	//描画色の設定
	glColor4fv(mpMaterial->mDiffuse);
	//マテリアル適用
	mpMaterial->Enabled();
	//	glDisable(GL_CULL_FACE);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glNormal3f(mN[i].mX, mN[i].mY, mN[i].mZ);
		glTexCoord2f(mUv[i].mX, mUv[i].mY);
		glVertex3f(v[i].mX, v[i].mY, v[i].mZ);
	}

	glEnd();

	//マテリアル解除
	mpMaterial->Disabled();
	//ライトオン
	glEnable(GL_LIGHTING);
	//行列を戻す
	glPopMatrix();
}
