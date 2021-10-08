#include "CMap.h"

#define OBJ "sky.obj"
#define MTL "sky.mtl"

CMap::CMap()
{
	mPosition = CVector(0.0f, 1.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();

	mModel.Load(OBJ, MTL);	//���f���̓ǂݍ���
	mpModel = &mModel;
}