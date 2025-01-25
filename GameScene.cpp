//--------------------------------------------------------------------------
// �`���v�^�[5
// ���@���F����@����
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
	// �G���h�L�[�������ꂽ���ǂ������A�b�v�g���K�[�Ŕ��f
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
	// ���݂̃}�b�v�̒[�̃}�b�v���W�ł͂Ȃ��A���[���h���W�����߂�
	int leftEdge = mapStPos.x * Stage::MAP_CHIP_WID;
	int rightEdge = leftEdge + Application::SCREEN_SIZE_WID - 1;

	// ��ʂ̉E�[�̃}�b�v�`�b�v���W���ɒB���Ă��邩���ׂ�
	if (playerPos.x >= rightEdge - Stage::MAP_CHIP_WID)
	{
		// �\����ʂ̉E�[�ɒB���Ă���̂ŁA�v���C���[�ʒu�������ɗ���\���J�n�ʒu�����߂�
		int dx = playerPos.x - (Application::SCREEN_SIZE_WID / 2);
		dx /= Stage::MAP_CHIP_WID;
		dx -= mapStPos.x;
		if (dx < 0)dx *= -1;
		stage->MoveMapToRight(dx);
	}
	// ��ʍ��[�̃}�b�v�`�b�v���W���ɒB���Ă��邩�𒲂ׂ�
	if (playerPos.x <= leftEdge - Stage::MAP_CHIP_WID * 2)
	{
		// �\����ʂ̍��[�ɒB���Ă���̂ŁA�v���C���[�ʒu�������ɗ���\���J�n�ʒu�����߂�
		int dx = playerPos.x - (Application::SCREEN_SIZE_WID / 2);
		dx /= Stage::MAP_CHIP_WID;
		dx -= mapStPos.x;
		if (dx < 0)dx *= -1;
		stage->MoveMapToLeft(dx);
	}

}
