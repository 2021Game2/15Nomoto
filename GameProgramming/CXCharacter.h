#ifndef CXCHARACTER_H
#define CXCHARACTER_H

#include "CModelX.h"
#include "CMatrix.h"
#include "CCharacter.h"

class CXCharacter : public CCharacter {
public:
	CModelX* mpModel;	//���f���f�[�^
	int mAnimationIndex;	//�A�j���[�V�����ԍ�
	bool mAnimationLoopFlg;	//true:�A�j���[�V�������J��Ԃ�
	float mAnimationFrame; //�A�j���[�V�����̍Đ��t���[��
	float mAnimationFrameSize;//�A�j���[�V�����̍Đ��t���[����
	CMatrix* mpCombinedMatrix;	//�����s��ޔ�
	CXCharacter();
	~CXCharacter()
	{
		SAFE_DELETE_ARRAY(mpCombinedMatrix);
	}
	//����������
	void Init(CModelX* model);
	//�A�j���[�V�����̕ύX
	void ChangeAnimation(int index, bool loop, float framesize);
	bool IsAnimationEnd();
	//�X�V����
	void Update(CMatrix& m);
	void Update();
	//�`�揈��
	void Render();

	enum Character_State {
		State_Idle = 0,
		State_Walk,
		State_Run,
		State_Dodge,
		State_Jump,
		State_Attack,
		State_Light_Attack,
		State_Strong_Attack,
		State_Hit,
		State_Blow,
		State_Death,
	};
};

#endif
