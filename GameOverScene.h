#pragma once

#include "StDefine.h"

class GameOverScene
{
public:
	static constexpr int TITLE_BACK_WID = 768;   // �^�C�g���摜�̉��T�C�Y
	static constexpr int TITLE_BACK_HIG = 480;   // �^�C�g���摜�̏c�T�C�Y
	static constexpr int GAME_OVER_WID = 768;   // �Q�[���I�[�o�[�摜�̏c�T�C�Y
	static constexpr int GAME_OVER_HIG = 147;    // �Q�[���I�[�o�[�摜�̉��T�C�Y

	GameOverScene(void);
	~GameOverScene(void);

	bool SystemInit(void);
	void GameInit(void) ;
	void Update(void);
	void Draw(void);
	bool Release(void);

	// ���ɑJ�ڂ���V�[����ID���擾����
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	int bgImage;                  // �w�i�摜�̃n���h���ԍ�
	int gameOver;                // �Q�[���I�[�o�[�摜�̃n���h���ԍ�

	eScene_ID nextSceneID;        // ���ɑJ�ڂ���V�[����ID

	int prevEKey, nowEKey;
};