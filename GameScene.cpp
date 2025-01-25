//--------------------------------------------------------------------------
// チャプター5
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// GameScene class
#include <DxLib.h>
#include "GameScene.h"
#include "Stage.h"
#include "Player.h"
#include "CommonUtility.h"

GameScene::GameScene(void)
{
	stage = nullptr;
	player = nullptr;
}

GameScene::~GameScene(void)
{
}

bool GameScene::SystemInit(void)
{
	stage = new Stage();
	if (stage == nullptr)return false;

	player = new Player(stage);
	if (player == nullptr)return false;

	stage->SystemInit();
	player->SystemInit();

	return true;
}

void GameScene::GameInit(void)
{
	stage->GameInit();
	player->GameInit();

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
	player->Update();

	POSITION playerPos = CommonUtility::Round(player->GetPlayerPos());
	if (playerPos.y >= Application::SCREEN_SIZE_HIG)
	{
		player->SetPlayerFlgOff();
	}

	MapScrollProc();
}

void GameScene::Draw(void)
{
	stage->Draw();
	player->Draw();
}

bool GameScene::Release(void)
{
	player->Release();
	delete player;
	player = nullptr;

	stage->Release();
	delete stage;
	stage = nullptr;

	return true;
}

void GameScene::MapScrollProc(void)
{
	POSITION mapStPos = stage->GetMapDispStPos();
	POSITION playerPos = CommonUtility::Round(player->GetPlayerPos());
	// 現在のマップの端のマップ座標ではなく、ワールド座標を求める
	int leftEdge = mapStPos.x * Stage::MAP_CHIP_WID;
	int rightEdge = leftEdge + Application::SCREEN_SIZE_WID - 1;

	// 画面の右端のマップチップ座標内に達しているか調べる
	if (playerPos.x >= rightEdge - Stage::MAP_CHIP_WID)
	{
		// 表示画面の右端に達しているので、プレイヤー位置が中央に来る表示開始位置を求める
		int dx = playerPos.x - (Application::SCREEN_SIZE_WID / 2);
		dx /= Stage::MAP_CHIP_WID;
		dx -= mapStPos.x;
		if (dx < 0)dx *= -1;
		stage->MoveMapToRight(dx);
	}
	// 画面左端のマップチップ座標内に達しているかを調べる
	if (playerPos.x <= leftEdge - Stage::MAP_CHIP_WID * 2)
	{
		// 表示画面の左端に達しているので、プレイヤー位置が中央に来る表示開始位置を求める
		int dx = playerPos.x - (Application::SCREEN_SIZE_WID / 2);
		dx /= Stage::MAP_CHIP_WID;
		dx -= mapStPos.x;
		if (dx < 0)dx *= -1;
		stage->MoveMapToLeft(dx);
	}

}
