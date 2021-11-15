#ifndef CTASK_H
#define CTASK_H
/*
タスククラス
タスクリストの要素
*/
class CTask {
public:
	CTask *mpNext;//次のポインタ
	CTask *mpPrev;//前のポインタ
	int mPriority;	//優先度
	bool mEnabled;	//有効フラグ
	//デフォルトコンストラクタ
	CTask()
		: mpNext(0), mpPrev(0), mPriority(0), mEnabled(true) {}
	CTask(int Priority)
		: mpNext(0), mpPrev(0), mPriority(Priority), mEnabled(true) {}
	//デストラクタ virtualにしないと子クラスのデストラクタが呼ばれない
	virtual ~CTask() {}
	//更新
	virtual void Update() {}
	//描画
	virtual void Render() {}
	virtual void Render2D() {}
	//衝突処理
	virtual void TaskCollision() {}
};

#endif
