#pragma once

#include "StDefine.h"

class TitleScene;
class GameScene;
class GameOverScene;
class Fader;

class SceneManager
{
public:
	SceneManager(void);             // �R���X�g���N�^
	~SceneManager(void);            // �f�X�g���N�^

	bool SystemInit(void);         // ����������(�ŏ��̂P��̂ݎ��s)
	void GameInit(void);           // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);             // �X�V����
	void Draw(void);               // �`�揈��
	bool Release(void);            // �������(�Ō�̂P��̂ݎ��s)

private:
	TitleScene* titleInst;         // �^�C�g���V�[���̃C���X�^���X�̃|�C���^
	GameScene* gameInst;           // �Q�[���V�[���N���X�̃C���X�^���X�̃|�C���^
	GameOverScene* gameOver;            // �Q�[���I�[�o�[�V�[���̃C���X�^���X�̃|�C���^
	Fader* fader;                  // �t�F�[�h�N���X�̃C���X�^���X�̃|�C���^

	eScene_ID scene_ID;            // ���݂̃V�[��ID
	eScene_ID waitScene;           // �V�[���`�F���W�Ŏ��ɑJ�ڂ���V�[����ID
	bool sceneChangeFlg;           // �V�[���`�F���W���s���t���O

	// �V�[���؂�ւ�����
	bool ChangeScene(eScene_ID id);

	void ReleaseScene(eScene_ID id);
};
