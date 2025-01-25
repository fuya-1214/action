//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// Player class
#include <DxLib.h>
#include <string>
#include "Player.h"
#include "Application.h"
#include "CommonUtility.h"
#include "Stage.h"

Player::Player(Stage* std)
{
	stage = std;
}

Player::~Player(void)
{
}

bool Player::SystemInit(void)
{
	if (!LoadPlayerImage())return false;

	return true;
}

void Player::GameInit(void)
{
	// モーションタイプ
	motionType = MOTION_TYPE::E_MOTION_IDLE;
	// アニメーションカウンタ
	fAnimCounter = 0.0f;
	// プレイヤーの初期位置
	pos = { 100.0f,100.0f };
	// プレイヤーの向き
	dir = DIRECTION::E_DIR_RIGHT;
	// ジャンプ力
	jumpPower = 0.0f;
	jumpFlg = true;
	// ジャンプキー押下判定
	putJumpKeyFlg = false;

	// ジャンプキーの入力カウンター
	// スタート直後は、1回着地しないとジャンプさせない
	inputJumpKeyCounter = INPUT_JUMPWKEY_FRAME;

	prevJumpKey = nowJumpKey = 0;
	plFlg = true;
}

void Player::Update(void)
{
	if (plFlg == false)
	{
		// 再表示する
		pos = { 100.0f,100.0f };

		plFlg = true;
	}
	// モーションの初期設定
	motionType = MOTION_TYPE::E_MOTION_IDLE;

	// 移動時の処理
	// 左向き
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		dir = DIRECTION::E_DIR_LEFT;
		// モーションの変更
		motionType = MOTION_TYPE::E_MOTION_RUN;
		// 移動速度
		pos.x -= MOVE_SPEED;
	}

	// 右向き
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		dir = DIRECTION::E_DIR_RIGHT;
		// モーションの変更
		motionType = MOTION_TYPE::E_MOTION_RUN;
		// 移動速度
		pos.x += MOVE_SPEED;
	}

	// 画面外に飛び出さないようにする
	// 左側
	if (pos.x < 0)pos.x = 0;

	//右側
	if (pos.x >= Application::SCREEN_SIZE_WID)
	{
//		pos.x = Application::SCREEN_SIZE_WID - CHARA_BODY_SIZE_WID - 1;
	}

	// 左右の衝突判定
	CollisionSide();

	// プレイヤーのジャンプ操作
	ProcessJump();
	// 重力を常にかける(ジャンプ中で無くても落下する)
	AddGravitation();
	// ジャンプ
	Jump();
	// 足元の衝突判定
	CollisionFoot();
	// 頭の衝突判定
	CollisionHead();
}

// 重力をかける
void Player::AddGravitation(void)
{
	// 現在のジャンプ力に重力を加える
	float power = jumpPower + GRAVITATION;
	SetJumpPower(power);
}

// プレイヤージャンプ操作
void Player::ProcessJump(void)
{
	prevJumpKey = nowJumpKey;
	nowJumpKey = CheckHitKey(KEY_INPUT_W);

	// 着地していないとジャンプを開始できないようにする
	if (nowJumpKey == 1 && !jumpFlg)
	{
		jumpFlg = true;
		putJumpKeyFlg = true;
	}

	// 入力時間に応じてジャンプ力を変更する
	if (nowJumpKey == 1 && inputJumpKeyCounter < INPUT_JUMPWKEY_FRAME && putJumpKeyFlg)
	{
		// ジャンプキー入力カウンターを増やす
		inputJumpKeyCounter++;

		// ジャンプ力を分配加算する
		float power = jumpPower - (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPWKEY_FRAME));
		SetJumpPower(power);

		jumpFlg = true;

		if (prevJumpKey == 1 && nowJumpKey == 0)
		{
			// ジャンプキーを離したら、ジャンプキーを入力判定を終了
			inputJumpKeyCounter = INPUT_JUMPWKEY_FRAME;
		}
	}
}

// ジャンプ
void Player::Jump(void)
{
	pos.y += jumpPower;
}

// ジャンプ力の設定
void Player::SetJumpPower(float power)
{
	// ジャンプ力を設定
	jumpPower = power;

	// 重力がかかりすぎるのを防ぐ
	if (jumpPower > MAX_JUMP_POWER)
	{
		jumpPower = MAX_JUMP_POWER;
	}
}

void Player::Draw(void)
{
	if (plFlg)
	{

		if (nowJumpKey == 1)
		{
			motionType = MOTION_TYPE::E_MOTION_JUMP;
		}

		// 現在のモーション
		int nowMotion = static_cast<int>(motionType);

		switch (motionType)
		{
		case MOTION_TYPE::E_MOTION_IDLE:
			DrawPlayer(img[nowMotion][0]);
			break;

		case MOTION_TYPE::E_MOTION_ATTACK:
		case MOTION_TYPE::E_MOTION_DAMAGE:
		case MOTION_TYPE::E_MOTION_RUN:
		{
			fAnimCounter += ANIM_SPEED;
			int idx = (CommonUtility::Round(fAnimCounter)) % 4;
			DrawPlayer(img[nowMotion][idx]);
		}
		break;
		case MOTION_TYPE::E_MOTION_DEATH:
		case MOTION_TYPE::E_MOTION_JUMP:
		{
			fAnimCounter += ANIM_SPEED;
			int idz = (CommonUtility::Round(fAnimCounter)) % MAX_ANIM_NUM;
			DrawPlayer(img[nowMotion][idz]);
		}
		break;
		}
	}
}

bool Player::Release(void)
{
	int motion_max = static_cast<int>(MOTION_TYPE::E_MOTION_MAX);

	for (int ii = 0; ii < motion_max; ii++)
	{
		for (int jj = 0; jj < MAX_ANIM_NUM; jj++)
		{
			if (img[ii][jj] != -1)
			{
				if (DeleteGraph(img[ii][jj]) == -1)return false;
			}
		}
	}

	return true;
}

// プレイヤー画像の読み込み処理
bool Player::LoadPlayerImage(void)
{
	std::string basePath = Application::PATH_PLAYER;

	int motion = 0;
	int motion_max = static_cast<int>(MOTION_TYPE::E_MOTION_MAX);

	// 画像ハンドル番号テーブルの初期化
	for (int ii = 0; ii < motion_max; ii++)
	{
		for (int jj = 0; jj < MAX_ANIM_NUM; jj++)
		{
			img[ii][jj] = -1;
		}
	}

	//----------------------------------------------
	// １つしかない画像を個別に読込む
	//----------------------------------------------
	// 待機モーション
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_IDLE);
	img[motion][0] = LoadGraph((Application::PATH_PLAYER + "Stop.png").c_str());
	if (img[motion][0] == -1)return false;

	// 走るモーション
	int run;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_RUN);
	run = LoadDivGraph((Application::PATH_PLAYER + "Run.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (run == -1)return false;

	// ジャンプモーション	
	int jump;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_JUMP);
	jump = LoadDivGraph((Application::PATH_PLAYER + "Jump.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (jump == -1)return false;

	// アタックモーション
	int attack;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_ATTACK);
	attack = LoadDivGraph((Application::PATH_PLAYER + "Attack.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (attack == -1)return false;

	// ダメージモーション
	int damage;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_DAMAGE);
	damage = LoadDivGraph((Application::PATH_PLAYER + "Damage.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (damage == -1)return false;

	// 消滅モーション
	int death;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_DEATH);
	death = LoadDivGraph((Application::PATH_PLAYER + "Death.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (death == -1)return false;

	return true;
}

// プレイヤーの描画
void Player::DrawPlayer(int handleId)
{
	POSITION pPos = CommonUtility::Round(pos);
	POSITION stPos = stage->GetMapDispStPos();
	pPos.x -= (stPos.x * Stage::MAP_CHIP_WID);

	// プレイヤーの描画
	bool leftFlg = true;
	if (dir == DIRECTION::E_DIR_RIGHT)
	{
		leftFlg = false;
	}

	DrawRotaGraph(pPos.x, pPos.y, 1.0, 0.0, handleId, true, leftFlg);
}

//-----------------------------------------------------
// 当たり判定処理関連関数
//-----------------------------------------------------
/**
 *----------------------------------------------------
 * ワールド座標の指す地形は衝突対象か調べる(衝突判定)
 * Input:
 * POSITION worldPos : ワールド座標
 * Output:
 * bool : true = 通行不可 / false = 通行可能
 *----------------------------------------------------
 */
bool Player::IsCollisionStage(POSITION worldPos)
{
	// ワールド座標をマップ座標へ変換
	POSITION mapPos = World2MapPos(worldPos);
	// マップ表示開始座標の取得
	POSITION stPos = stage->GetMapDispStPos();
	mapPos.x -= stPos.x;

	int chipNo = stage->GetMapChipNo(mapPos);

	if (chipNo >= 10)return true;
	return false;
}

/**
 *----------------------------------------------------
 * ワールド座標をマップ座標に変換する
 * Input:
 * POSITION worldPos : ワールド座標
 * Output:
 * POSITION : マップ座標
 *----------------------------------------------------
 */
POSITION Player::World2MapPos(POSITION worldPos)
{
	POSITION mapPos;

	mapPos.x = mapPos.y = 0;
	mapPos.x = worldPos.x / Stage::MAP_CHIP_WID;
	mapPos.y = worldPos.y / Stage::MAP_CHIP_HIG;

	return mapPos;
}

/**
 *----------------------------------------------------
 * 足元の衝突判定
 * Input:
 * 無し
 * Output:
 * 無し
 *----------------------------------------------------
*/
void Player::CollisionFoot(void)
{
	// 足元の座標(中心)
	POSITION footPosC = GetCollisionPos(COLLISION_LR::E_CENTER, COLLISION_TB::E_BOTTOM);

	// 足元の座標(左)
	POSITION footPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_BOTTOM);

	// 足元の座標(右)
	POSITION footPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_BOTTOM);

	if (IsCollisionStage(footPosC) || IsCollisionStage(footPosL) || IsCollisionStage(footPosR))
	{
		// プレイヤーのY座標を地面に接触した座標に設定する
		POSITION mPos = World2MapPos(footPosC);
		pos.y = static_cast<float>((mPos.y * Stage::MAP_CHIP_HIG) - 1 - (CHARA_SIZE_HIG / 2));

		// 地面についたのでジャンプをリセットする
		jumpFlg = false;
		SetJumpPower(0.0f);

		// 設置したらジャンプキー入力カウンターをクリアする
		inputJumpKeyCounter = 0;
		// ジャンプキー押下判定
		putJumpKeyFlg = false;
	}

	// 空中判定
	if (!jumpFlg)
	{
		footPosC.y++;
		footPosL.y++;
		footPosR.y++;
		if (!(IsCollisionStage(footPosC) || IsCollisionStage(footPosL) || IsCollisionStage(footPosR)))
		{
			// 着地していないのでジャンプ判定にする
			jumpFlg = true;
		}
	}
}

/**
 *----------------------------------------------------
 * 頭上の衝突判定
 * Input:
 * 無し
 * Output:
 * 無し
 *----------------------------------------------------
*/
void Player::CollisionHead(void)
{
	// 頭上の座標(中心)
	POSITION headPosC = GetCollisionPos(COLLISION_LR::E_CENTER, COLLISION_TB::E_TOP);

	// 頭上の座標(左)
	POSITION headPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_TOP);

	// 頭上の座標(右)
	POSITION headPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_TOP);

	if (IsCollisionStage(headPosC) || IsCollisionStage(headPosL) || IsCollisionStage(headPosR))
	{
		// プレイヤーのY座標を天井に設置した座標に設定する
		POSITION mPos = World2MapPos(headPosC);
		pos.y = static_cast<float>(((mPos.y + 1) * Stage::MAP_CHIP_HIG) + (CHARA_BODY_SIZE_HIG / 2));
		pos.y -= COLLISION_RECT_Y_OFFSET;

		// 頭がぶつかったので、ジャンプ力をリセット
		SetJumpPower(0.0f);
	}
}

/**
 *----------------------------------------------------
 * 左右の衝突判定
 * Input:
 * 無し
 * Output:
 * 無し
 *----------------------------------------------------
*/
void Player::CollisionSide(void)
{
	// 右側の衝突判定
	POSITION headPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_TOP);
	POSITION centerPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_CENTER);
	POSITION footPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_BOTTOM);

	if (IsCollisionStage(headPosR) || IsCollisionStage(centerPosR) || IsCollisionStage(footPosR))
	{
		POSITION mPos = World2MapPos(headPosR);
		if (IsCollisionStage(footPosR))
		{
			// 足元がぶつかっている時
			pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - COLLISION_FOOT_RECT_X);
		}
		else
		{
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// 右を向いているとき
				pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - ((COLLISION_RECT_L_SPACE + CHARA_BODY_SIZE_WID) - (CHARA_SIZE_WID / 2)));
			}
			else
			{
				// 左を向いているとき
				pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE));
			}
		}
	}

	// 左側の衝突判定
	POSITION headPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_TOP);
	POSITION centerPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_CENTER);
	POSITION footPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_BOTTOM);
	if (IsCollisionStage(headPosL) || IsCollisionStage(centerPosL) || IsCollisionStage(footPosL))
	{
		POSITION mPos = World2MapPos(headPosL);
		if (IsCollisionStage(footPosL))
		{
			// 足元がぶつかっている時
			pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + COLLISION_FOOT_RECT_X);
		}
		else
		{
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// 右を向いているとき
				pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE));
			}
			else
			{
				// 左を向いているとき
				pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + (CHARA_SIZE_WID / 2 - COLLISION_RECT_R_SPACE));
			}
		}
	}
}

/**
*----------------------------------------------------
* 衝突判定の座標を取得する
* Input:
* COLLISION_LR lr : 左右の位置
* COLLISION_TB tb : 上下の位置
* Output:
* 指定された位置の判定座標
*----------------------------------------------------
*/
POSITION Player::GetCollisionPos(COLLISION_LR lr, COLLISION_TB tb)
{
	POSITION pPos = CommonUtility::Round(pos);

	// 左右
	switch (lr)
	{
	case COLLISION_LR::E_LEFT:
		if (tb == COLLISION_TB::E_BOTTOM)
		{
			// 足元の右側
			pPos.x -= COLLISION_FOOT_RECT_X;
		}
		else
		{
			// 足元以外の左側
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// 右を向いているとき
				pPos.x -= (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE);
			}
			else
			{
				// 左を向いているとき
				pPos.x -= (CHARA_SIZE_WID / 2 - COLLISION_RECT_R_SPACE);
			}
		}
		break;
	case COLLISION_LR::E_RIGHT:
		if (tb == COLLISION_TB::E_BOTTOM)
		{
			// 足元の右側
			pPos.x += COLLISION_FOOT_RECT_X;
		}
		else
		{
			// 足元以外の右側
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// 右を向いているとき
				pPos.x += ((COLLISION_RECT_L_SPACE + CHARA_BODY_SIZE_WID) - (CHARA_SIZE_WID / 2));
			}
			if (dir == DIRECTION::E_DIR_LEFT)
			{
				// 左を向いているとき
				pPos.x += (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE);
			}
		}
		break;
	}

	// 上下
	switch (tb)
	{
	case COLLISION_TB::E_TOP:
		pPos.y -= (CHARA_BODY_SIZE_HIG / 2);
		break;
	case COLLISION_TB::E_BOTTOM:
		pPos.y += (CHARA_BODY_SIZE_HIG / 2);
		break;
	}

	return pPos;
}