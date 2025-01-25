#pragma once
#include "StDefine.h"

class Fader
{
public:
	static constexpr float FADE_SPEED_ALPHA = 2.0f;     // フェードの速さ

	Fader(void);             // コンストラクタ
	~Fader(void);            // デストラクタ

	bool SystemInit(void);         // 初期化処理(最初の１回のみ実行)
	void GameInit(void);           // ゲームの起動・再開時に必ず呼び出す処理
	void Update(void);             // 更新処理
	void Draw(void);               // 描画処理
	bool Release(void);            // 解放処理(最後の１回のみ実行)

	// ゲッター・セッター関数
	eFaderStateID GetNowState(void) { return stat; }
	bool IsEnd(void) { return endFlg; }
	void SetFade(eFaderStateID id);  // フェードアウト・フェードイン開始時

private:
	eFaderStateID stat;             // 現在のフェードの状態(ステータス)
	float  alpha;                   // アルファ値用の変数
	bool endFlg;                    // フェード処理終了フラグ(true=未実装/false=実装中)

};
