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
	//�e�L�X�g�t�H���g�̓ǂݍ��݂Ɛݒ�
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);

	//�L�����N�^�[�Ƀ��f����ݒ�
	CRes::sModelX.Load(MODEL_FILE);

	CXPlayer::Generate();
	ClEnemyManager::Generate();

	CXPlayer::GetInstance()->Init(&CRes::sModelX);


	for (int i = 0; i < 5; i++) {
		ClEnemyManager::GetInstance()->EnemyGenerate(1);
	}

	//�J����������
	Camera.Init();
}


void CSceneGame::Update() {


	//Escape�ŏI��
	if (CKey::Push(VK_ESCAPE)) {
		exit(0);
	}
	ClEnemyManager::GetInstance()->Update();

	//�^�X�N�X�V
	CTaskManager::Get()->Update();

	//�Փˏ���
	CCollisionManager::Get()->Collision();

	Camera.Update();

	return;
}

void CSceneGame::Render()
{
	//�J�����N���X�̐ݒ�
	Camera.Render();


	//�^�X�N�`��
	CTaskManager::Get()->Render();
	CTaskManager::Get()->Render2D();

	//�R���C�_�̕`��
	CCollisionManager::Get()->Render();

	//2D�`��J�n
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2D�̕`��I��
	CUtil::End2D();

}

