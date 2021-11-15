#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H


#include "ClEnemy.h"

//�G�Ǘ��N���X
class ClEnemyManager
{
	friend ClEnemy;


private:
	static ClEnemyManager* m_Instance;	//�C���X�^���X�ێ��p


	std::vector<ClEnemy*> m_EnemyList;	//�G�i�[�p

	ClEnemy* m_NearTarget;				//��ԋ߂��G�i�[�p
public:
	ClEnemyManager();
	~ClEnemyManager();

	static void Generate();				//����
	static void Release();				//�j��
	static ClEnemyManager* GetInstance();//�C���X�^���X�擾

	void EnemyGenerate(int num);		//�G�L��������
	ClEnemy* GetNearEnemy();			//��ԋ߂��G�擾
	void Update();						//�X�V����
	void Render();						//�`��

	void AIUpdate();					//AI�X�V


};


#endif
