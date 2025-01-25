#pragma once

#include "StDefine.h"
#include <string>

class Stage;

class Player
{
public:
	static constexpr int CHARA_SIZE_WID = 32;          // プレイヤー画像の横サイズ
	static constexpr int CHARA_SIZE_HIG = 32;          // プレイヤー画像の縦サイズ
	static constexpr int CHARA_BODY_SIZE_WID = 21;     // プレイヤーキャラ本体の横サイズ
	static constexpr int CHARA_BODY_SIZE_HIG = 26;     // プレイヤーキャラ本体の縦サイズ
	static constexpr int COLLISION_RECT_L_SPACE = 3;  // プレイヤー画像の左側の空きサイズ
	static constexpr int COLLISION_RECT_R_SPACE = (CHARA_SIZE_WID - COLLISION_RECT_L_SPACE - CHARA_BODY_SIZE_WID);  // プレイヤー画像の右側の空きサイズ

	static constexpr int COLLISION_RECT_Y_OFFSET = 3;   // 衝突矩形のオフセット
	static constexpr int COLLISION_FOOT_RECT_X = -1;     // 衝突矩形のオフセット

	// 最大アニメーションパターン数
	static constexpr int MAX_ANIM_NUM = 8;
	// アニメーションスピード
	static constexpr float ANIM_SPEED = 0.1f;
	// プレイヤーの移動速度
	static constexpr float MOVE_SPEED = 3.0f;

	// 最大ジャンプ力
	static constexpr float MAX_JUMP_POWER = 8.5f;
	// 重力
	static constexpr float GRAVITATION = 0.25f;
	// ジャンプキーの入力を受け付けるプレーム数
	static constexpr int INPUT_JUMPWKEY_FRAME = 8;
	// モーションタイプ
	enum class MOTION_TYPE
	{
		E_MOTION_IDLE,      // 待機モーション
		E_MOTION_RUN,       // 走るモーション
		E_MOTION_JUMP,      // ジャンプモーション
		E_MOTION_ATTACK,    // アタックモーション
		E_MOTION_DAMAGE,    // ダメージモーション
		E_MOTION_DEATH,     // 消滅モーション

		E_MOTION_MAX,
	};

	// 衝突座標(左右)
	enum class COLLISION_LR
	{
		E_CENTER,
		E_LEFT,
		E_RIGHT
	};

	// 衝突座標(上下)
	enum class COLLISION_TB
	{
		E_CENTER,
		E_TOP,
		E_BOTTOM,
	};

	Player(Stage* stg);
	~Player(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	// ゲッター・セッター関数
	POSITION_F GetPlayerPos(void) { return pos; }
	void SetPlayerFlgOff(void) { plFlg = false; }


private:
	Stage* stage;    // ステージクラスのインスタンスのポインタ

	// プレイヤー画像のハンドル番号テーブル
	int img[static_cast<int>(MOTION_TYPE::E_MOTION_MAX)][MAX_ANIM_NUM];

	// プレイヤーの画像ファイル名
	std::string imgFName;

	// プレイヤーの座標
	POSITION_F pos;

	// プレイヤーのモーションタイプ
	MOTION_TYPE motionType;

	// アニメーションカウンタ
	float fAnimCounter;
	// ジャンプキーの入力カウンター
	int inputJumpKeyCounter;

	// プレイヤーの向き
	DIRECTION dir;

	// ジャンプ力
	float jumpPower;
	// ジャンプ中判定
	bool jumpFlg;
	// ジャンプキーの押下判定
	bool putJumpKeyFlg;

	int prevJumpKey, nowJumpKey;

	// プレイヤー画像の読み込み処理
	bool LoadPlayerImage(void);
	// プレイヤーの描画
	void DrawPlayer(int handleId);
	// 重力をかける
	void AddGravitation(void);
	// プレイヤージャンプ操作
	void ProcessJump(void);
	// ジャンプ
	void Jump(void);
	// ジャンプ力の設定
	void SetJumpPower(float power);
	// プレイヤーの表示フラグ(true=表示/false=非表示)
	bool plFlg;

	//-----------------------------------------------------
	// 当たり判定処理関連関数
	//-----------------------------------------------------
	bool IsCollisionStage(POSITION worldPos);
	POSITION World2MapPos(POSITION worldPos);
	// 足元の衝突判定
	void CollisionFoot(void);
	// 頭の衝突判定
	void CollisionHead(void);
	// 左右の衝突判定
	void CollisionSide(void);
	POSITION GetCollisionPos(COLLISION_LR lr, COLLISION_TB tb);
	//------------------------------------------------------
};
