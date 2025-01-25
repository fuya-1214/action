//--------------------------------------------------------------------------
// チャプター４
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// Stage class
#include <DxLib.h>
#include "Stage.h"
#include "Application.h"

// コンストラクタ
Stage::Stage(void)
{
}

// デストラクタ
Stage::~Stage(void)
{
}

// 初期化処理(最初の１回のみ実行)
bool Stage::SystemInit(void)
{
	// マップチップデータを読み込む
	int err = LoadDivGraph("image/Stage/TileMap.png", MAP_CHIP_ALL_NUMS, MAP_CHIP_NUMS_X, MAP_CHIP_NUMS_Y, MAP_CHIP_WID, MAP_CHIP_HIG, imgMapChipArray);
	if (err == -1)return false;

	return true;
}

// ゲーム起動時・再開時にする処理
void Stage::GameInit(void)
{
	LoadStageData();          // ステージデータを読み込む

	mapDispStPos.x = mapDispStPos.y = 0;
}

// 更新処理
void Stage::Update(void)
{
}

// 描画処理
void Stage::Draw(void)
{
	// まず背景を黒で塗りつぶす
	DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0, 0, 0), true);
	// マップチップ画像を表示する
	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		if (yy >= DSP_CHIP_NUM_Y)break;
		for (int xx = 0; xx < MAP_MAX_NUM_X; xx++)
		{
			if (xx >= DSP_CHIP_NUM_X)break;
			int chip = dispMapDat[mapDispStPos.y+yy][mapDispStPos.x+xx];
			int dx = MAP_CHIP_WID * xx;
			int dy = MAP_CHIP_HIG * yy;
			DrawGraph(dx, dy, imgMapChipArray[chip], true);
		}
	}
}

// 解放処理(最後の１回のみ実行)
bool Stage::Release(void)
{
	for (int ii = MAP_CHIP_ALL_NUMS - 1; ii >= 0; ii--)
	{
		if (DeleteGraph(imgMapChipArray[ii]) == -1)return false;
	}

	return true;
}

// 外部ファイルからマップデータを読み込む
bool Stage::LoadStageData(void)
{
	int loadBuff[MAP_MAX_NUM_X + 1];

	// マップデータファイルをオープン
	FILE* fp;
	if (fopen_s(&fp, "Stage/Sample.dat", "rb") != 0)return false;

	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		fread(loadBuff, sizeof(int), MAP_MAX_NUM_X, fp);
		memcpy(&dispMapDat[yy], loadBuff, sizeof(int) * MAP_MAX_NUM_X);
	}

	fclose(fp);

	return true;
}

/*
*-------------------------------------------
* マップの左方向に移動(画面は右にスクロール)
* INPUT:
*    int mov : マップスクロールの移動量(チップ数)
* Output:
*    無し
*-------------------------------------------
*/
void Stage::MoveMapToLeft(int mov)
{
	mapDispStPos.x -= mov;
	if (mapDispStPos.x < 0)mapDispStPos.x = 0;
}

/*
*-------------------------------------------
* マップの右方向に移動(画面は左にスクロール)
* INPUT:
*    int mov : マップスクロールの移動量(チップ数)
* Output:
*    無し
*-------------------------------------------
*/
void Stage::MoveMapToRight(int mov)
{
	mapDispStPos.x += mov;
	if (mapDispStPos.x + DSP_CHIP_NUM_X >= MAP_MAX_NUM_X)
	{
		mapDispStPos.x = MAP_MAX_NUM_X - DSP_CHIP_NUM_X;
	}
}
