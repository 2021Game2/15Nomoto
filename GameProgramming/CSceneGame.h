#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include "CBillBoard.h"
#include "CBillBoard2.h"
#include "CSound.h"
#include "CMap.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
private:

	//�}�b�v�̃C���X�^���X
	CMap mMap;

public:

	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�`�揈���̃I�[�o�[���C�h
	void Render();
};

#endif
