#pragma once

#include "StDefine.h"

class Stage;
class Player;

class GameScene
{
public:
	GameScene(void);
	~GameScene(void);

	bool SystemInit(void);        // ����������(�ŏ��̂P��̂ݎ��s)
	void GameInit(void);          // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);            // �X�V����
	void Draw(void);              // �`�揈��
	bool Release(void);           // �������(�Ō�̂P��̂ݎ��s)

	// ���ɑJ�ڂ���V�[����ID���擾����
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	Stage* stage;         // �X�e�[�W�N���X�̃C���X�^���X�̃|�C���^

	eScene_ID nextSceneID;     // ���ɑJ�ڂ���V�[����ID

	int prevEndKey, nowEndKey;

};
