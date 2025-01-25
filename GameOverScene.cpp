//--------------------------------------------------------------------------
// チャプター４
// 氏　名：八代　風弥
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
	// 背景画像の読み込み
	bgImage = LoadGraph("image/UI/title_back.png");
	if (bgImage == -1)return false;
	// ゲームオーバー画像の読み込み
	gameOver = LoadGraph("image/UI/GameOver.png");
	if (gameOver == -1)return false;

	return true;
}

void GameOverScene::GameInit(void)
{
	// 次のシーンの初期設定
	nextSceneID = E_SCENE_GAMEOVER;

	prevSpaceKey = nowSpaceKey = 0;
}

void GameOverScene::Update(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	// スペースキーが押されたかをアップトリガーをアップトリガー判断
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
