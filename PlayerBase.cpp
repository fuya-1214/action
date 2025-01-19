//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// PlayerBase class
#include <DxLib.h>
#include "PlayerBase.h"
#include "Application.h"

PlayerBase::PlayerBase()
{
}

PlayerBase::~PlayerBase()
{
}

bool PlayerBase::SystemInit(void)
{
	// プレイヤー個別のパラメータ設定処理
	SetPlayerParam();

	std::string path = "image/";
	path += imgFName;
//	int err = LoadDivGraph(path.c_str(), PLAYER_PTN_MAX, ANIM_NUMS, static_cast<int>(DIRECTION::E_DIR_MAX), imgSize.wid, imgSize.hig, img[0]);
//	if (err == -1)return false;

	dir = static_cast<int>(DIRECTION::E_DIR_RIGHT);

	return true;
}

void PlayerBase::GameInit(void)
{
//	pos.x = imgSize.wid / 2 + Application::WINDOW_WID;
//	pos.y = imgSize.hig / 2 + Application::WINDOW_HIG;


	animCounter = 0;
	aliveFlg = true;
}

void PlayerBase::Update(void)
{
	animCounter++;
	if (animCounter > (ANIM_NUMS * ANIM_INTERVAL) * 10)animCounter = 0;

	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		pos.x += speed;
		dir = static_cast<int>(DIRECTION::E_DIR_RIGHT);
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		pos.x -= speed;
		dir = static_cast<int>(DIRECTION::E_DIR_LEFT);
	}
}

void PlayerBase::Draw(void)
{
	int animNo = (animCounter / ANIM_INTERVAL) % ANIM_NUMS;
//	DrawGraph(pos.x - imgSize.wid / 2 + Application::WINDOW_WID / 2, pos.y - imgSize.hig / 2 + Application::WINDOW_HIG / 2, img[dir][animNo], true);
}

bool PlayerBase::Release(void)
{
	for (int yy = static_cast<int>(DIRECTION::E_DIR_MAX); yy > 0; yy--)
	{
		for (int xx = ANIM_NUMS; xx > 0; xx--)
		{
			if (DeleteGraph(img[yy - 1][xx - 1]) == -1)return false;
		}
	}

	return true;
}
