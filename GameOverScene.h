#pragma once

#include "StDefine.h"

class GameOverScene
{
public:
	static constexpr int TITLE_BACK_WID = 768;   // タイトル画像の横サイズ
	static constexpr int TITLE_BACK_HIG = 480;   // タイトル画像の縦サイズ
	static constexpr int GAME_OVER_WID = 768;   // ゲームオーバー画像の縦サイズ
	static constexpr int GAME_OVER_HIG = 147;    // ゲームオーバー画像の横サイズ

	GameOverScene(void);
	~GameOverScene(void);

	bool SystemInit(void);
	void GameInit(void) ;
	void Update(void);
	void Draw(void);
	bool Release(void);

	// 次に遷移するシーンのIDを取得する
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	int bgImage;                  // 背景画像のハンドル番号
	int gameOver;                // ゲームオーバー画像のハンドル番号

	eScene_ID nextSceneID;        // 次に遷移するシーンのID

	int prevEKey, nowEKey;
};