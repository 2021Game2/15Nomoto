#include "CXEnemy.h"
#include "CXPlayer.h"

CXEnemy::CXEnemy()
	: mColSphereBody(this, nullptr, CVector(0.5f, -1.0f, 0.0f), 1.0f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 1.f, 0.0f), 1.5f)
	, mColSphereSword0(this, nullptr, CVector(0.7f, 3.5f, -0.2f), 0.5f)
	, mColSphereSword1(this, nullptr, CVector(0.5f, 2.5f, -0.2f), 0.5f)
	, mColSphereSword2(this, nullptr, CVector(0.3f, 1.5f, -0.2f), 0.5f)
{
	mTag = EENEMY;
	mColSphereSword0.mTag = mColSphereSword1.mTag =
		mColSphereSword2.mTag = CCollider::EENEMYSWORD;
}

void CXEnemy::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[1];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[1];
	//剣
	mColSphereSword0.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword1.mpMatrix = &mpCombinedMatrix[26];
	mColSphereSword2.mpMatrix = &mpCombinedMatrix[26];

}

void CXEnemy::Collision(CCollider* m, CCollider* o)
{
	if (m->mType == CCollider::ESPHERE)
	{
		if (o->mType == CCollider::ESPHERE)
		{
			if (o->mpParent->mTag == EPLAYER)
			{
				if (o->mTag == CCollider::EPLAYERSWORD)
				{
					if (CXPlayer::spThis->mIn_Light_Attack == true)
					{
						if (CCollider::Collision(m, o))
						{
							//30フレームかけてダウンし、繰り返さない
							ChangeAnimation(11, false, 30);
						}
					}
					else if (CXPlayer::spThis->mIn_Strong_Attack == true)
					{
						if (CCollider::Collision(m, o))
						{
							ChangeAnimation(11, false, 30);
						}
					}
				}
			}
		}
	}
}
