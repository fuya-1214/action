//--------------------------------------------------------------------------
// �`���v�^�[�S
// ���@���F����@����
//--------------------------------------------------------------------------
// GameOverScene class
#include <DxLib.h>
#include "GameOverScene.h"
#include "Application.h"

GameOverScene::GameOverScene(void)
{
	bgImage = -1;
	gameOver = -1;
}

GameOverScene::~GameOverScene(void)
{
}

bool GameOverScene::SystemInit(void)
{
	// �w�i�摜�̓ǂݍ���
	bgImage = LoadGraph("image/UI/title_back.png");
	if (bgImage == -1)return false;
	// �Q�[���I�[�o�[�摜�̓ǂݍ���
	gameOver = LoadGraph("image/UI/GameOver.png");
	if (gameOver == -1)return false;

	return true;
}

void GameOverScene::GameInit(void)
{
	// ���̃V�[���̏����ݒ�
	nextSceneID = E_SCENE_GAMEOVER;

	prevSpaceKey = nowSpaceKey = 0;
}

void GameOverScene::Update(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	// �X�y�[�X�L�[�������ꂽ�����A�b�v�g���K�[���A�b�v�g���K�[���f
	if (prevSpaceKey == 1 && nowSpaceKey == 0)
	{
		nextSceneID = E_SCENE_TITLE;
	}
}

void GameOverScene::Draw(void)
{
	int dx, dy;
	dx = (Application::SCREEN_SIZE_WID - TITLE_BACK_WID) / 2;
	dy = (Application::SCREEN_SIZE_HIG - TITLE_BACK_HIG) / 2;
	DrawGraph(dx, dy, bgImage, true);

	dx = (Application::SCREEN_SIZE_WID - GAME_OVER_WID) / 2;
	dy = (Application::SCREEN_SIZE_HIG - GAME_OVER_HIG) / 2;
	DrawGraph(dx, dy, gameOver, true);
}

bool GameOverScene::Release(void)
{
	if (DeleteGraph(bgImage) == -1)return false;
	if (DeleteGraph(gameOver) == -1)return false;

	return false;
}
