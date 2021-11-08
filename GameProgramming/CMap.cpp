#include "CMap.h"
#include "CColliderMesh.h"

#define OBJ "sky.obj"
#define MTL "sky.mtl"

CColliderMesh mColliderMesh;

CMap::CMap()
{
	mPosition = CVector(0.0f, 1.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	CTransform::Update();

	mModel.Load(OBJ, MTL);	//ÉÇÉfÉãÇÃì«Ç›çûÇ›
	mpModel = &mModel;

	mColliderMesh.Set(NULL, NULL, &mModel);
}
