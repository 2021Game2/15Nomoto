#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CBillBoard.h"
#include "CBillBoard2.h"
#include "CSound.h"
#include "CMap.h"
#include "ClEnemy2.h"

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
private:
	ClEnemy2 enemy2;
	//マップのインスタンス
	CMap mMap;

public:

	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//描画処理のオーバーライド
	void Render();
};

#endif
