#include "ClEnemy2.h"

CModelX ClEnemy2::mModel;

#define ENEMY2_MODEL "Resource\\felguard\\felguard-X.X"

ClEnemy2::ClEnemy2()
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(ENEMY2_MODEL);
		//mModel.SeparateAnimationSet(0, 0, 700, "Idle");
		
	}
	mModel.SeparateAnimationSet(0, 0, 100, "Idle");
	mModel.SeparateAnimationSet(0, 150, 200, "Attack1");
	mModel.SeparateAnimationSet(0, 200, 260, "Attack_Idle");
	mModel.SeparateAnimationSet(0, 260, 350, "Attack3");
	mModel.SeparateAnimationSet(0, 380, 420, "Walk");
	mModel.SeparateAnimationSet(0, 425, 460, "Run");
	mModel.SeparateAnimationSet(0, 470, 510, "Death1");
	mModel.SeparateAnimationSet(0, 520, 700, "Death2");
	mpModel = &mModel;
	mPosition = CVector(-5.0f, 0.0f, 0.0f);
	mScale = CVector(1.0f, 1.0f, 1.0f);
	Init(&mModel);
	CTransform::Update();
	ChangeAnimation(1, true, 60);

}

ClEnemy2::~ClEnemy2()
{
}

void ClEnemy2::Init(CModelX* model)
{
	CXCharacter::Init(model);
}
