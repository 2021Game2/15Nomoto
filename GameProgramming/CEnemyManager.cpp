#include "CEnemyManager.h"
#include "ClPlayer.h"
#include <algorithm>
#include "CRes.h"

//スコア並べ替え用
bool comp(const ClEnemy* lh, const ClEnemy* rh) {

	return lh->GetScore() > rh->GetScore();
}

ClEnemyManager* ClEnemyManager::m_Instance;

ClEnemyManager::ClEnemyManager()
	:m_NearTarget(NULL)
{
	CRes::sKnight.Load("knight\\knight_low.x");
	CRes::sKnight.SeparateAnimationSet(0, 0, 5, "Tpose");
	CRes::sKnight.SeparateAnimationSet(0, 10, 80, "walk");
	CRes::sKnight.SeparateAnimationSet(0, 90, 160, "walk_backwards");
	CRes::sKnight.SeparateAnimationSet(0, 170, 220, "run");
	CRes::sKnight.SeparateAnimationSet(0, 230, 300, "strafe_left");
	CRes::sKnight.SeparateAnimationSet(0, 300, 370, "strafe_right");
	CRes::sKnight.SeparateAnimationSet(0, 380, 430, "jump");
	CRes::sKnight.SeparateAnimationSet(0, 440, 520, "attack_1");
	CRes::sKnight.SeparateAnimationSet(0, 520, 615, "attack_2");
	CRes::sKnight.SeparateAnimationSet(0, 615, 795, "attack_3");
	CRes::sKnight.SeparateAnimationSet(0, 795, 850, "attack_4");
	CRes::sKnight.SeparateAnimationSet(0, 850, 970, "attack_5");
	CRes::sKnight.SeparateAnimationSet(0, 970, 1040, "attack_6");
	CRes::sKnight.SeparateAnimationSet(0, 1040, 1080, "hit_1");
	CRes::sKnight.SeparateAnimationSet(0, 1080, 1120, "hit_2");
	CRes::sKnight.SeparateAnimationSet(0, 1120, 1160, "hit_3");
	CRes::sKnight.SeparateAnimationSet(0, 1160, 1260, "death_1");
	CRes::sKnight.SeparateAnimationSet(0, 1270, 1370, "death_2");
	CRes::sKnight.SeparateAnimationSet(0, 1380, 1530, "idle_1");
	CRes::sKnight.SeparateAnimationSet(0, 1530, 1830, "Idle_2");
	CRes::sKnight.SeparateAnimationSet(0, 1830, 1930, "emotion_1");
	CRes::sKnight.SeparateAnimationSet(0, 1930, 2040, "emotion_2");

}
ClEnemyManager::~ClEnemyManager() {
	for (size_t i = 0; i < m_EnemyList.size(); i++) {
		delete m_EnemyList[i];
	}
}

void ClEnemyManager::Generate()
{
	m_Instance = new ClEnemyManager;
}
void ClEnemyManager::Release()
{
	if (m_Instance) {
		delete m_Instance;
		m_Instance = NULL;
	}
}

ClEnemyManager* ClEnemyManager::GetInstance()
{
	return m_Instance;
}

void ClEnemyManager::EnemyGenerate(int num)
{
	for (int i = 0; i < 1; i++) {
		CVector tPos;
		tPos.Set(0, 0, 0);
		//		tPos.mY += -3.0f + (float)(rand() % 6);
		tPos.mX += -30.0f + (float)(rand() % 60);
		tPos.mZ += -30.0f + (float)(rand() % 60);

		ClEnemy* tmp = new ClEnemy;
		tmp->SetPos(tPos);
		tmp->Update();
		m_EnemyList.push_back(tmp);
	}
}
ClEnemy* ClEnemyManager::GetNearEnemy()
{
	return m_NearTarget;
}
void ClEnemyManager::Update() {
	AIUpdate();

	for (size_t i = 0; i < m_EnemyList.size(); i++) {
		m_EnemyList[i]->Update();
	}
}
void ClEnemyManager::Render() {
	for (size_t i = 0; i < m_EnemyList.size(); i++) {
		m_EnemyList[i]->Render();
	}

}

void ClEnemyManager::AIUpdate()
{
	static const int AttackerNum = 2;
	float tNearScore = 0.0f;

	for (size_t i = 0; i < m_EnemyList.size(); i++) {
		if (i == 0) {
			m_NearTarget = m_EnemyList[i];
		}
		//アタッカー選別
		m_EnemyList[i]->AttackerCheck();
		//プレイヤーの対象になるエネミー選別
		if (m_EnemyList[i]->PlayerTargetCheck(&tNearScore)) {
			m_NearTarget = m_EnemyList[i];//近い敵を入れる
		}
	}

	//優先順（スコア順）に並べ替え
	std::sort(m_EnemyList.begin(), m_EnemyList.end(), comp);


	//スコア上位AttackerNum数に攻撃行動命令を出す
	for (size_t i = 0; i < m_EnemyList.size(); i++) {
		if (m_EnemyList.size() > i) {
			if (m_EnemyList[i]) {
				if (i < AttackerNum) {
					if (m_EnemyList[i]->GetScore() >= -100.0f) {
						m_EnemyList[i]->ChangeAIState(ClEnemy::AI_GetCloser);
					}
				}
				else {
					//優先度がさがったのでIdleに戻す
					m_EnemyList[i]->ChangeAIState(ClEnemy::AI_Idle);
				}
			}
		}
	}


}
