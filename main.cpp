//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// main class
#include <DxLib.h>
#include "Application.h"

//-----------------
// WinMain関数
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanced, LPSTR llpCmdLine, int nCmdShow)
{
	// アプリケーションクラスの実体化したオブジェクトの作成
	Application apl;

	// 初期化処理
	apl.SystemInit();

	// ゲームの起動
	apl.Run();

	// 解放処理
	apl.Release();

	return 0;
}