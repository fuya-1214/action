//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// Application class
#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "SceneManager.h"

Application::Application()
{
	sceneMana = nullptr;
}

Application::~Application()
{
}

bool Application::SystemInit(void)
{
	// システム設定処理
	SetWindowText("最終作品");                    //ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);     // ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);					      // ゲームウィンドウの表示方法(false：フルスクリーン)
	
	if (DxLib_Init() == -1)return false;          // DXライブラリの初期化処理

	// インスタンスの作成
	sceneMana = new SceneManager;
	if (sceneMana == nullptr)return false;

	sceneMana->SystemInit();

	return true;
}					

void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		Update();
		Draw();
	}
}

void Application::Update(void)
{
	sceneMana->Update();
}

void Application::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);    // 描画する画面を裏の画面に設定する 
	ClearDrawScreen();			      // 描画する画面の内容を消去(クリア)する

	sceneMana->Draw();

	ScreenFlip();                     // 裏画面と表画面を入れ替える
}
bool Application::Release(void)
{
	sceneMana->Release();
	delete sceneMana;
	sceneMana = nullptr;

	if (DxLib_End() == -1)return false;

	return true;
}
