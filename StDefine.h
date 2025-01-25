#pragma once

//--------------------
// 列挙型定義
//--------------------
// シーン定義
enum eScene_ID
{
	E_SCENE_NON = -1,

	E_SCENE_TITLE,     // タイトル画面
	E_SCENE_GAME,      // ゲームシーン画面
	E_SCENE_GAMEOVER,  // ゲームオーバー画面


	E_SCENE_ID_MAX,
};

// フェードの状態
enum eFaderStateID
{
	E_STAT_FADE_NON = -1,
	E_STAT_FADE_OUT,        // フェードアウト(徐々に暗転する)
	E_STAT_FADE_IN,         // フェードイン(徐々に明転する)


	E_STAT_FADE_MAX,

};

// 方向
enum class DIRECTION
{
	E_DIR_DOWN,        // 下	
	E_DIR_UP,          // 上
	E_DIR_LEFT,        // 左
	E_DIR_RIGHT,       // 右

	E_DIR_MAX,
};

//--------------------
// 構造体定義
//--------------------
struct POSITION
{
	int x;
	int y;
};

struct POSITION_F
{
	float x;
	float y;
};
