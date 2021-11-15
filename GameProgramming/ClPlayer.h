//#ifndef CLPLAYER_H
//#define CLPALYER_H
//
//#include "CXCharacter.h"
//#include "CCollider.h"
//#include "CBattleParam.h"
//
//class ClPlayer : public CXCharacter
//{
//private:
//	enum PlayerState {
//		State_Idle = 0,
//		State_Walk,
//		State_Jump,
//		State_Attack,
//		State_AttackUpdate,
//		State_Damage,
//		State_Death
//	};
//	enum AttackType {
//		AType_Normal = 0,
//		AType_Move,
//		AType_Dash,
//	};
//	enum Anim {
//		Anim_Idle = 0,
//		Anim_Walk,
//		Anim_Hit,
//		Anim_AttackA,
//		Anim_AttackToIdle,
//		Anim_AttackAtoB,
//		Anim_AttackBtoIdle,
//		Anim_AttackBtoC,
//		Anim_AttackCtoIdle,
//		Anim_AttackDash,
//		Anim_AttackDashToIdle,
//		Anim_Death,
//		Anim_End
//	};
//
//	static ClPlayer* m_Instance;
//
//	//コライダの宣言
//	CCollider mColSphereBody;	//体
//	CCollider mColSphereHead;	//頭
//	CCollider mColSphereSword;	//剣
//	CCollider mColSylinderBody;	//体
//
//	//モーション有モデルクラス
//	//座標
//	CVector m_pos;
//	//回転
//	CVector m_rot;
//	//移動ベクトル
//	CVector m_vec;
//	//半径
//	float m_rad;
//
//	PlayerState m_State;
//	AttackType	m_AttackType;
//	//カメラ関連--------------
//	//カメラの位置
//	CVector m_cam_pos;
//	//カメラの回転値
//	CVector m_cam_rot;
//	//カメラの距離
//	float m_cam_dist;
//
//	//------------------------
//	//挙動
//
//	CVector m_velocity;	//加速度
//
//	CVector m_target;	//目標点
//	CVector m_LookTarget;
//	bool m_IsAutoMove;
//	bool m_IsLook;
//
//	CVector m_move_dir;
//
//	int		m_ComboCnt;//コンボカウント
//	bool	m_IsCombo;//コンボ継続フラグ
//	float	m_AttackMoveParam;//攻撃時の移動量計算用係数
//
//	bool	m_IsAttackHit;//攻撃タイミング
//	int		m_InvCnt;		//無敵時間
//	int		m_Hp;
//	CVector m_HitVec;		//ヒット時ののけぞりベクトル
//	float	m_KnockBackValue;	//のけぞり係数
//
//	stAttackParam	m_AttackParam;
//	stCharaParam	m_CharaParam;
//
//public:
//	ClPlayer();
//	~ClPlayer();
//
//	static void Generate();			//生成
//	static void Release();			//解放
//	static ClPlayer* GetInstance();	//インスタンス取得
//
//	void Init(CModelX* model);		//初期化
//	void Update();					//更新
//	void Render();					//描画
//	void StateUpdate();				//ステートの更新類
//	void ChangeState(PlayerState hState);//ステート変更処理
//	bool IsCanAction();				//攻撃可能状態チェック
//	bool IsDamageAction();			//ダメージ中かチェック
//	CVector GetPos();				//位置取得
//	CVector GetRot();				//角度取得（mY、ラジアン）
//	void AutoMoveUpdate();			//自動行動関連更新
//
//	//衝突処理
//	//m:自分のコライダ o:相手のコライダ
//	void Collision(CCollider* m, CCollider* o);
//
//	//被弾処理
//	void TakeDamage(const stAttackParam& hAttackParam, const stCharaParam& hCharaParam);
//
//
//};
//
//#endif