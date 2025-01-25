#pragma once

#include "StDefine.h"
#include "Application.h"

class Stage
{
public:
	static constexpr int MAP_CHIP_WID = 32;            // マップチップの横サイズ
	static constexpr int MAP_CHIP_HIG = 32;            // マップチップの縦サイズ

	static constexpr int MAP_CHIP_NUMS_X = 11;         // マップチップ画像内の素材の横数
	static constexpr int MAP_CHIP_NUMS_Y = 3;          // マップチップ画像内の素材の縦数
	static constexpr int MAP_CHIP_ALL_NUMS = (MAP_CHIP_NUMS_X * MAP_CHIP_NUMS_Y);      // マップチップ画像内の素材の総数

	static constexpr int MAP_MAX_NUM_X = 50;           // マップの最大サイズ
	static constexpr int MAP_MAX_NUM_Y = 20;

	static constexpr int DSP_CHIP_NUM_X = Application::SCREEN_SIZE_WID / MAP_CHIP_WID;
	static constexpr int DSP_CHIP_NUM_Y = Application::SCREEN_SIZE_HIG / MAP_CHIP_HIG + 1;

	Stage(void);    // コンストラクタ
	~Stage(void);   // デストラクタ

	bool SystemInit(void);          // 初期化処理(最初の１回のみ実行) 
	void GameInit(void);            // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);              // 更新処理
	void Draw(void);                // 描画処理
	bool Release(void);             // 解放処理(最後の１回のみ実行)

	bool LoadGroundData(void);      // 外部ファイルからマップデータを読み込む

	POSITION GetMapDispStPos(void) { return mapDispStPos; }                	// マップ表示開始座標の取得
	int GetMapChipNo(POSITION mPos) { return dispMapDat[mPos.y][mPos.x]; }  // マップ座標のチップ番号を取得する

	void MoveMapToLeft(int mov);
	void MoveMapToRight(int mov);

private:
	int imgMapChipArray[MAP_CHIP_ALL_NUMS];       // マップチップ画像のハンドル番号テーブル

	// 表示しているマップデータ
	int dispMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];
	// 表示しているマップのサイズ
	POSITION dispMapSize;

	// 地上マップデータ
	int groundMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];

	POSITION mapDispStPos;                       // マップ表示開始座標

};
