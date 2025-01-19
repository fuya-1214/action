//--------------------------------------------------------------------------
// チャプター４
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// Fader class
#include <DxLib.h>
#include "Fader.h"
#include "Application.h"

// コンストラクタ
Fader::Fader(void)
{
}

// デストラクタ
Fader::~Fader(void)
{
}

/**
* -----------------------------------------------
* 初期化処理(最初の１回のみ実行)
* Input:
*     無し
* Output:
*     bool true = 正常終了 / false = エラー
* -----------------------------------------------
*/
bool Fader::SystemInit(void)
{
	GameInit();

	return true;
}

/**
*------------------------------------------
* ゲーム起動時・再開時にする処理
* Input:
*    無し
*  Output:
*    無し
* -----------------------------------------
*/
void Fader::GameInit(void)
{
	stat = E_STAT_FADE_NON;
	alpha = 0.0f;
	endFlg = true;
}

/**
*------------------------------------------
* 更新処理
* Input:
*    無し
*  Output:
*    無し
* -----------------------------------------
*/
void Fader::Update(void)
{
	if (endFlg)return;

	switch(stat)
	{
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
		alpha += FADE_SPEED_ALPHA;
		if (alpha > 255.0f)
		{
			// フェードアウト終了
			alpha = 255.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	case E_STAT_FADE_IN:
		alpha -= FADE_SPEED_ALPHA;
		if (alpha < 0)
		{
			// フェードイン終了
			alpha = 0.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	default:
		return;
	}

}

/**
*------------------------------------------
* 描画処理
* Input:
*    無し
*  Output:
*    無し
* -----------------------------------------
*/
void Fader::Draw(void)
{
	switch (stat)
	{
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
	case E_STAT_FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);    // α値をブレンドするモードに設定
		DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           // ブレンドモードを解除
		break;
	default:
		return;
	}
}

/**
*------------------------------------------
* 解放処理(最後の１回のみ実行)
* Input
*    無し
* Output
*    true = 正常終了　/ false =  エラー終了
*-----------------------------------------
*/
bool Fader::Release(void)
{
	return true;
}

// フェードアウト・フェードイン開始時に呼び出す処理
void Fader::SetFade(eFaderStateID id)
{
	stat = id;
	if (stat != E_STAT_FADE_NON)
	{
		endFlg = false;
	}
}
