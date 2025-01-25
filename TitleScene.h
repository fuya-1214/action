#pragma once

#include "StDefine.h"

class TitleScene
{
public:
	
	static constexpr int TITLE_BACK_WID = 768;  // �^�C�g���摜�̉��T�C�Y
	static constexpr int TITLE_BACK_HIG = 480;  // �^�C�g����ʂ̏c�T�C�Y
	
	TitleScene(void);     // �R���X�g���N�^
	~TitleScene(void);    // �f�X�g���N�^

	bool SystemInit(void);        // ����������(�ŏ��̂P��̂ݎ��s)
	void GameInit(void);          // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);            // �X�V����
	void Draw(void);            // �`�揈��
	bool Release(void);           // �������(�Ō�̂P��̂ݎ��s)

	// ���ɑJ�ڂ���V�[����ID���擾����
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	int bgImage;            // �w�i�摜�̃n���h���ԍ�

	eScene_ID nextSceneID;  // ���ɑJ�ڂ���V�[����ID

	int prevSpaceKey, nowSpaceKey;  // �L�[�̏�Ԃ��i�[����ϐ�
};
