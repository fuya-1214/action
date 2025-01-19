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
	int err = LoadDivGraph("image/Stage/TileMap.png", MAP_CHIP_ALL_NUM, MAP_CHIP_NUMS_X, MAP_CHIP_NUMS_Y, MAP_CHIP_WID, MAP_CHIP_HIG, imgMapChipArray);
	if (err == -1)return false;

	return true;
}

// ゲーム起動時・再開時にする処理
void Stage::GameInit(void)
{
	LoadGroundData();          // 地上マップデータを読み込む

	ChangeMap(MAP_TYPE::E_MTYPE_GROUND);

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
	for (int yy = 0; yy < dispMapSize.y; yy++)
	{
		if (yy >= DSP_CHIP_NUM_Y)break;
		for (int xx = 0; xx < dispMapSize.x; xx++)
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
	for (int ii = MAP_CHIP_ALL_NUM - 1; ii >= 0; ii--)
	{
		if (DeleteGraph(imgMapChipArray[ii]) == -1)return false;
	}

	return true;
}

// 外部ファイルからマップデータを読み込む
bool Stage::LoadGroundData(void)
{
	int loadBuff[MAP_GROUND_NUM_X + 1];

	// マップデータファイルをオープン
	FILE* fp;
	if (fopen_s(&fp, "Stage/Stage.dat", "rb") != 0)return false;

	for (int yy = 0; yy < MAP_GROUND_NUM_Y; yy++)
	{
		fread(loadBuff, sizeof(int), MAP_GROUND_NUM_X, fp);
		memcpy(&groundMapDat[yy], loadBuff, sizeof(int) * MAP_GROUND_NUM_X);
	}

	fclose(fp);

	return true;
}


/*
*--------------------------------------------------- 
* マップの上方向に移動(画面は下にスクロール)
* Input;
*    int mov マップスクロールの移動量(チップ数)
* Output;
*    無し
*----------------------------------------------------
*/
void Stage::MoveMapToUpper(int mov)
{
	mapDispStPos.y -= mov;
	if (mapDispStPos.y < 0)
	{
		mapDispStPos.y = 0;
	}
}
/*
*---------------------------------------------------
* マップの下方向に移動(画面は上にスクロール)
* Input;
*    int mov マップスクロールの移動量(チップ数)
* Output;
*    無し
*----------------------------------------------------
*/
void Stage::MoveMapToDown(int mov)
{
	mapDispStPos.y += mov;
	if (mapDispStPos.y + DSP_CHIP_NUM_Y >= MAP_GROUND_NUM_Y)
	{
		mapDispStPos.y = MAP_GROUND_NUM_Y - DSP_CHIP_NUM_Y;
	}
}
/*
*---------------------------------------------------
* マップの左方向に移動(画面は右にスクロール)
* Input;
*    int mov マップスクロールの移動量(チップ数)
* Output;
*    無し
*----------------------------------------------------
*/
void Stage::MoveMapToLeft(int mov)
{
	mapDispStPos.x -= mov;
	if (mapDispStPos.x < 0)
	{
		mapDispStPos.x = 0;
	}
}
/*
*---------------------------------------------------
* マップの右方向に移動(画面は左にスクロール)
* Input;
*    int mov マップスクロールの移動量(チップ数)
* Output;
*    無し
*----------------------------------------------------
*/
void Stage::MoveMapToRight(int mov)
{
	mapDispStPos.x += mov;
	if (mapDispStPos.x + DSP_CHIP_NUM_X >= MAP_GROUND_NUM_X)
	{
		mapDispStPos.x = MAP_GROUND_NUM_X - DSP_CHIP_NUM_X;
	}
}

/*
*---------------------------------------------------
* マップを変更する
* Input;
*    MAP_TYPE mtype : 切り替えるマップの種別
* Output;
*    無し
*----------------------------------------------------
*/
void Stage::ChangeMap(MAP_TYPE mtype)
{
	ClearDispMap();        // マップのクリア

	mapType = mtype;

	switch (mapType)
	{
	case MAP_TYPE::E_MTYPE_GROUND:
		// マップサイズを設定
		dispMapSize.x = MAP_GROUND_NUM_X;
		dispMapSize.y = MAP_GROUND_NUM_Y;

		// マップデータを設定する
		for (int yy = 0; yy < dispMapSize.y; yy++)
		{
			for (int xx = 0; xx < dispMapSize.x; xx++)
			{
				dispMapDat[yy][xx] = groundMapDat[yy][xx];
			}
		}
		break;
	case MAP_TYPE::E_MTYPE_UNDER_GROUND:
		// マップサイズを設定
		dispMapSize.x = MAP_UNDER_GROUND_NUM_X;
		dispMapSize.y = MAP_UNDER_GROUND_NUM_Y;

		// マップデータを設定する
		for (int yy = 0; yy < dispMapSize.y; yy++)
		{
			for (int xx = 0; xx < dispMapSize.x; xx++)
			{
				dispMapDat[yy][xx] = underGroundMapDat[yy][xx];
			}
		}
		break;
	}
}

//表示しているマップ情報の初期化
void Stage::ClearDispMap(void)
{
	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		for (int xx = 0; xx < MAP_MAX_NUM_X; xx++)
		{
			dispMapDat[yy][xx] = -1;
		}
	}
}

/*
 *----------------------------------------------------
 * 指定のマップ座標が階段かどうかを調べる
 * Input:
 * POSITION mapPos : マップ座標(0～)
 * Output:
 * bool : true = 階段 / false = 階段ではない
 *----------------------------------------------------
 */
bool Stage::IsStair(POSITION mapPos)
{
	int chipNo = GetMapChipNo(mapPos);
	if (chipNo >= MAP_CHIP_STAIR1_NO && chipNo <= MAP_CHIP_STAIR5_NO)return true;
	
	return false;
}