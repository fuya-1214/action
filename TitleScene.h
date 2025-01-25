#pragma once

#include "StDefine.h"

class TitleScene
{
public:
	
	static constexpr int TITLE_BACK_WID = 768;  // タイトル画像の横サイズ
	static constexpr int TITLE_BACK_HIG = 480;  // タイトル画面の縦サイズ
	
	TitleScene(void);     // コンストラクタ
	~TitleScene(void);    // デストラクタ

	bool SystemInit(void);        // 初期化処理(最初の１回のみ実行)
	void GameInit(void);          // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);            // 更新処理
	void Draw(void);            // 描画処理
	bool Release(void);           // 解放処理(最後の１回のみ実行)

	// 次に遷移するシーンのIDを取得する
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	int bgImage;            // 背景画像のハンドル番号

	eScene_ID nextSceneID;  // 次に遷移するシーンのID

	int prevSpaceKey, nowSpaceKey;  // キーの状態を格納する変数
};
