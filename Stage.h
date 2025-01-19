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
	static constexpr int MAP_CHIP_ALL_NUM = (MAP_CHIP_NUMS_X * MAP_CHIP_NUMS_Y);      // マップチップ画像内の素材の総数

	static constexpr int MAP_MAX_NUM_X = 70;           // マップの最大サイズ
	static constexpr int MAP_MAX_NUM_Y = 70;

	static constexpr int MAP_GROUND_NUM_X = 50;        // 地上マップサイズの横
	static constexpr int MAP_GROUND_NUM_Y = 50;        // 地上マップサイズの縦

	static constexpr int MAP_UNDER_GROUND_NUM_X = 50;  // 地下のマップサイズ横
	static constexpr int MAP_UNDER_GROUND_NUM_Y = 50;  // 地下のマップサイズ縦
	
	static constexpr int DSP_CHIP_NUM_X = Application::SCREEN_SIZE_WID / MAP_CHIP_WID;
	static constexpr int DSP_CHIP_NUM_Y = Application::SCREEN_SIZE_HIG / MAP_CHIP_HIG + 1;

	static constexpr int MAP_SIZE_WID = MAP_CHIP_WID * MAP_GROUND_NUM_X;  // マップの横サイズ
	static constexpr int MAP_SIZE_HIG = MAP_CHIP_HIG * MAP_GROUND_NUM_Y;  // マップの縦サイズ

	static constexpr int MAP_CHIP_STAIR1_NO = 20;     // 階段の地形番号
	static constexpr int MAP_CHIP_STAIR2_NO = 21;     // 階段の地形番号
	static constexpr int MAP_CHIP_STAIR3_NO = 22;     // 階段の地形番号
	static constexpr int MAP_CHIP_STAIR4_NO = 23;     // 階段の地形番号
	static constexpr int MAP_CHIP_STAIR5_NO = 24;     // 階段の地形番号

	enum class MAP_TYPE
	{
		E_MTYPE_NON,
		E_MTYPE_GROUND,        // 地上マップ
		E_MTYPE_UNDER_GROUND,  // 地下マップ

		E_MTYPE_MAX,
	};

	Stage(void);    // コンストラクタ
	~Stage(void);   // デストラクタ

	bool SystemInit(void);          // 初期化処理(最初の１回のみ実行) 
	void GameInit(void);            // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);              // 更新処理
	void Draw(void);                // 描画処理
	bool Release(void);             // 解放処理(最後の１回のみ実行)

	bool LoadGroundData(void);      // 外部ファイルからマップデータを読み込む
	bool LoadUnderGroundData(void); // 外部ファイルから地下マップデータを読み込む

	// ゲッター・セッター関数
	void MoveMapToUpper(int mov);     // マップの上方向に移動(画面は下にスクロール)
	void MoveMapToDown(int mov);      // マップの下方向に移動(画面は上にスクロール)
	void MoveMapToLeft(int mov);      // マップの左方向に移動(画面は右にスクロール)
	void MoveMapToRight(int mov);     // マップの右方向に移動(画面は左にスクロール)

	POSITION GetMapDispStPos(void) { return mapDispStPos; }
	int GetMapChipNo(POSITION mPos) { return dispMapDat[mPos.y][mPos.x]; }  // マップ座標のチップ番号を取得する
	POSITION GetDispMapSize(void) { return dispMapSize; }    // 表示しているマップのサイズを取得する
	MAP_TYPE GetMapType(void) { return mapType; } // 表示しているマップの種別を取得する
	bool IsStair(POSITION mapPos);    // 指定のマップ座標が階段かどうかを調べる

	// マップを変更する
	void ChangeMap(MAP_TYPE mtype);

private:
	int imgMapChipArray[MAP_CHIP_ALL_NUM];       // マップチップ画像のハンドル番号テーブル

	// 表示しているマップデータ
	int dispMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];
	// 表示しているマップのサイズ
	POSITION dispMapSize;
	// 表示しているマップの種別
	MAP_TYPE mapType;

	// 地上マップデータ
	int groundMapDat[MAP_GROUND_NUM_Y][MAP_GROUND_NUM_X];
	// 地下マップデータ
	int underGroundMapDat[MAP_UNDER_GROUND_NUM_Y][MAP_UNDER_GROUND_NUM_X];

	POSITION mapDispStPos;                       // マップ表示開始座標

	// 表示しているマップの情報を初期化する
	void ClearDispMap(void);
};
