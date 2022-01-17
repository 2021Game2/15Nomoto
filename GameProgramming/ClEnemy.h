#ifndef CLENEMY_H
#define CLENEMY_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CBattleParam.h"

class ClEnemyManager;

//敵キャラクラス
class ClEnemy : public CXCharacter {
	friend class ClEnemyManager;
private:
	/*enum EnemyState {
		State_Idle = 0,
		State_Walk,
		State_Run,
		State_Jump,
		State_Attack,
		State_Hit,
		State_Blow,
		State_Death,
	};*/
	enum AIState {
		AI_Idle = 0,
		AI_GetCloser,	//近づく
		AI_LongDistance,//距離をとる
		AI_Attack,		//攻撃
	};
	enum Anim {
		Anim_None = 0,
		Anim_TPose,
		Anim_Walk,
		Anim_Walk_Backwards,
		Anim_Run,
		Anim_Strafe_left,
		Anim_Strafe_right,
		Anim_Jump,
		Anim_Attack1,
		Anim_Attack2,
		Anim_Attack3,
		Anim_Attack4,
		Anim_Attack5,
		Anim_Attack6,
		Anim_Hit1,
		Anim_Hit2,
		Anim_Hit3,
		Anim_Death1,
		Anim_Death2,
		Anim_Idle1,
		Anim_Idle2,
		Anim_Emotion1,
		Anim_Emotion2,
		Anim_End
	};
	CCollider mColSphereSword0;	//剣
	CCollider mColSphereSword1;	//剣
	CCollider mColSphereSword2;	//剣
public:
	//コライダの宣言
	CCollider mColSphereBody;	//体
	CCollider mColSphereHead;	//頭
	CCollider mColSphereShoulder;//肩
	CCollider mColSylinderBody;	//体
private:

	//座標
	CVector m_pos;
	//回転
	CVector m_rot;
	//移動ベクトル
	CVector m_vec;
	//半径
	float m_rad;

	//状態
	Character_State m_State;


	//挙動

	CVector m_velocity;		//加速度

	CVector m_target;		//目標点
	CVector m_LookTarget;	//向き目標点
	bool m_IsAutoMove;		//自動移動フラグ
	bool m_IsLook;			//自動回転フラグ
	bool m_IsTrace;			//対象を追う
	float m_TargetLen;		//対象との距離
	CVector m_move_dir;		//移動方向

	//AI判別用
	AIState m_AiState;		//AI状態
	float m_score;			//AI判断用スコア保持用
	float m_NearScore;		//近距離判別用

	//ゲーム用
	int		m_Hp;				//体力
	CVector m_HitVec;			//ヒット時ののけぞりベクトル
	int		m_InvCnt;			//無敵時間
	float	m_KnockBackValue;	//のけぞり係数
	float	m_AttackMoveParam;	//攻撃時移動パラメータ
	stCharaParam	m_CharaParam;	//攻撃時渡す情報パラメータ

public:
	ClEnemy();
	~ClEnemy();

	void Init(CModelX* model);	//初期化
	void Update();				//更新
	void Render();				//描画
	void StateUpdate();			//状態更新処理
	void ChangeState(Character_State hState);//状態変更処理
	bool IsCanAction();			//アクション可能チェック
	bool IsDamageAction();		//ダメージ中かチェック
	void SetPos(CVector hPos);	//位置設定

	void AutoMoveUpdate();		//自動行動更新

	void ClearScore();			//判定用数値クリア
	void AttackerCheck();		//攻撃参加チェック
	bool IsScreen();			//画面内にいるかどうか
	bool IsAttack();			//攻撃中か攻撃予備軍
	bool IsDamage();			//ダメージをうけている
	bool PlayerTargetCheck(float* hNearScore);//被ターゲット判定用
	float PositionCheckScore();	//位置関係からスコア算出

	float GetScore() const;		//スコアを返す
	void ChangeAIState(AIState hAiState);//AI変更

	CVector GetPos();			//位置取得

	//衝突処理
	//m:自分のコライダ o:相手のコライダ
	void Collision(CCollider* m, CCollider* o);

	bool	m_IsAttackHit;		//攻撃判定フラグ
	static ClEnemy* GetInstance();
	static ClEnemy* spInstance;		//敵のインスタンス 外部参照用
};

#endif