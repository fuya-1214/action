#pragma once

#include "StDefine.h"

class TitleScene;
class GameScene;
class GameOverScene;
class Fader;

class SceneManager
{
public:
	SceneManager(void);             // コンストラクタ
	~SceneManager(void);            // デストラクタ

	bool SystemInit(void);         // 初期化処理(最初の１回のみ実行)
	void GameInit(void);           // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);             // 更新処理
	void Draw(void);               // 描画処理
	bool Release(void);            // 解放処理(最後の１回のみ実行)

private:
	TitleScene* titleInst;         // タイトルシーンのインスタンスのポインタ
	GameScene* gameInst;           // ゲームシーンクラスのインスタンスのポインタ
	GameOverScene* gameOver;            // ゲームオーバーシーンのインスタンスのポインタ
	Fader* fader;                  // フェードクラスのインスタンスのポインタ

	eScene_ID scene_ID;            // 現在のシーンID
	eScene_ID waitScene;           // シーンチェンジで次に遷移するシーンのID
	bool sceneChangeFlg;           // シーンチェンジ実行中フラグ

	// シーン切り替え処理
	bool ChangeScene(eScene_ID id);

	void ReleaseScene(eScene_ID id);
};
