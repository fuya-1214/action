//--------------------------------------------------------------------------
// チャプター5
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// GameScene class
#include <DxLib.h>
#include "GameScene.h"
#include "Stage.h"

GameScene::GameScene(void)
{
	stage = nullptr;
}

GameScene::~GameScene(void)
{
}

bool GameScene::SystemInit(void)
{
	stage = new Stage();
	if (stage == nullptr)return false;

	stage->SystemInit();

	return true;
}

void GameScene::GameInit(void)
{
	stage->GameInit();

	nextSceneID = E_SCENE_GAME;

	prevEndKey = nowEndKey = 0;
}

void GameScene::Update(void)
{
	prevEndKey = nowEndKey;
	nowEndKey = CheckHitKey(KEY_INPUT_E);
	// エンドキーが押されたかどうかをアップトリガーで判断
	if (prevEndKey == 1 && nowEndKey == 0)
	{
		nextSceneID = E_SCENE_GAMEOVER;
	}

	stage->Update();

}

void GameScene::Draw(void)
{
	stage->Draw();
}

bool GameScene::Release(void)
{
	stage->Release();
	delete stage;
	stage = nullptr;

	return true;
}

