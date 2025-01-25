//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// TitleScene class
#include <DxLib.h>
#include "TitleScene.h"
#include "Application.h"

TitleScene::TitleScene(void)
{
	bgImage = -1;
}
TitleScene::~TitleScene(void)
{
}

bool TitleScene::SystemInit(void)
{
	bgImage = LoadGraph("image/title_back.png");
	if (bgImage == -1)return false;

	return true;
}

void TitleScene::GameInit(void)
{
	// 次のシーンの初期設定
	nextSceneID = E_SCENE_TITLE;

	prevSpaceKey = nowSpaceKey = 0;
}

void TitleScene::Update(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	// スペースキーが押されたかをアップトリガーをアップトリガー判断
	if (prevSpaceKey == 1 && nowSpaceKey == 0)
	{
		nextSceneID = E_SCENE_GAME;
	}
}

void TitleScene::Draw(void)
{
	DrawGraph((Application::SCREEN_SIZE_WID - TITLE_BACK_WID) / 2, (Application::SCREEN_SIZE_HIG - TITLE_BACK_HIG) / 2, bgImage, true);

}

bool TitleScene::Release(void)
{
	if (DeleteGraph(bgImage) == -1)return false;

	return true;
}
