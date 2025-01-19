#pragma once

#include "StDefine.h"

class Stage;
class Player;

class GameScene
{
public:
	GameScene(void);
	~GameScene(void);

	bool SystemInit(void);        // 初期化処理(最初の１回のみ実行)
	void GameInit(void);          // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);            // 更新処理
	void Draw(void);              // 描画処理
	bool Release(void);           // 解放処理(最後の１回のみ実行)

	// 次に遷移するシーンのIDを取得する
	eScene_ID GetNextSceneID(void) { return nextSceneID; }

private:
	Stage* stage;         // ステージクラスのインスタンスのポインタ

	eScene_ID nextSceneID;     // 次に遷移するシーンのID

	int prevEndKey, nowEndKey;

};
