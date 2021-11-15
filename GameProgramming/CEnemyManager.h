#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H


#include "ClEnemy.h"

//敵管理クラス
class ClEnemyManager
{
	friend ClEnemy;


private:
	static ClEnemyManager* m_Instance;	//インスタンス保持用


	std::vector<ClEnemy*> m_EnemyList;	//敵格納用

	ClEnemy* m_NearTarget;				//一番近い敵格納用
public:
	ClEnemyManager();
	~ClEnemyManager();

	static void Generate();				//生成
	static void Release();				//破棄
	static ClEnemyManager* GetInstance();//インスタンス取得

	void EnemyGenerate(int num);		//敵キャラ生成
	ClEnemy* GetNearEnemy();			//一番近い敵取得
	void Update();						//更新処理
	void Render();						//描画

	void AIUpdate();					//AI更新


};


#endif
