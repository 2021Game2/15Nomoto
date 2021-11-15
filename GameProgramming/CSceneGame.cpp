#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
//
#include "CRes.h"

#include "Ckey.h"
//
#include "CMaterial.h"
//
#include "CCollisionManager.h"

#include "CXPlayer.h"
#include "CEnemyManager.h"

//CMatrix Matrix;

CSceneGame::~CSceneGame()
{
	CXPlayer::Release();
	ClEnemyManager::Release();
}

void CSceneGame::Init() {
	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	//キャラクターにモデルを設定
	CRes::sModelX.Load(MODEL_FILE);

	CXPlayer::Generate();
	ClEnemyManager::Generate();

	CXPlayer::GetInstance()->Init(&CRes::sModelX);


	for (int i = 0; i < 5; i++) {
		ClEnemyManager::GetInstance()->EnemyGenerate(1);
	}

	//カメラ初期化
	Camera.Init();
}


void CSceneGame::Update() {


	//Escapeで終了
	if (CKey::Push(VK_ESCAPE)) {
		exit(0);
	}
	ClEnemyManager::GetInstance()->Update();

	//タスク更新
	CTaskManager::Get()->Update();

	//衝突処理
	CCollisionManager::Get()->Collision();

	Camera.Update();

	return;
}

void CSceneGame::Render()
{
	//カメラクラスの設定
	Camera.Render();


	//タスク描画
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();

	//コライダの描画
	CCollisionManager::Get()->Render();

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

}

