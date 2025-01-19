//--------------------------------------------------------------------------
// action
// 氏　名：八代　風弥
//--------------------------------------------------------------------------
// main class
#include <DxLib.h>
#include "Application.h"

#if 0
#define WINDOW_WIDTH (1600)
#define WINDOW_HEGHT (900)

// パッドの情報を列挙体で定義
enum e_But
{
	But_Dow, // 1Bit
	But_Lef, // 2Bit
	But_Rig, // 3Bit
	But_Up,  // 4Bit
	But_A,   // 5Bit
	But_B,   // 6Bit
	But_X,   // 7Bit
	But_Y,   // 8Bit
	But_L,   // 9Bit
	But_R,   // 10Bit
	But_Sel, // 11Bit
	But_Sta, // 12Bit
	But_L3,  // 13Bit
	But_R3,  // 14Bit
	But_Total, 
};

// パットのビット情報
int Pad_Inp;

// パットの押したカウント数
int Pad_Cou[e_But::But_Total];

// パッドの入力情報を取得する関数
bool Pad_Read()
{
	Pad_Inp = GetJoypadInputState(DX_INPUT_PAD1);

	for (int b = 0; b < e_But::But_Total; b = b + 1)
	{
		if (Pad_Inp & (1 << b))
		{
			Pad_Cou[b] = Pad_Cou[b] + 1;
		}
	}
	return FALSE;
}

enum e_Type
{
	E_LAND_1,
	E_LAND_2,
	E_LAND_3,
	E_LAND_4,
	E_LAND_5,
	E_LAND_6,
	E_LAND_7,
	E_LAND_8,
	E_LAND_9,
	E_LAND_10,
	E_LAND_11,
	E_LAND_12,
	E_LAND_13,
	E_LAND_14,
	E_LAND_15,
	E_LAND_16,
	E_LAND_17,
	E_LAND_18,
	E_LAND_19,
	E_LAND_20,
	E_LAND_21,
	E_LAND_22,
	E_LAND_23,
	E_LAND_24,
	E_LAND_25,
	E_LAND_26,
	E_LAND_27,
	E_LAND_28,
	E_LAND_29,
	E_LAND_30,
	E_LAND_31,
	E_LAND_32,
	E_LAND_33,
};

// ゲーム開始時の処理を行う関数
void Game_Init()
{

}

// ゲーム終了時の処理を行う関数
void Game_End()
{
}

// ゲーム計算処理を行う関数
void Game_Cal()
{
}

// ゲーム描画処理を行う関数
void Game_Draw()
{
}
#endif

//-----------------
// WinMain関数
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanced, LPSTR llpCmdLine, int nCmdShow)
{
#if 0	
	ChangeWindowMode(TRUE);
	DxLib_Init();

	// ウィンドウの初期化
	SetMainWindowText("試作");
	SetWindowInitPosition(0, 0);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEGHT, 32);  // 背景画像の初期化
	SetDrawScreen(DX_SCREEN_BACK);

	Game_Init();

	// 1秒間に60回(FPS回)無限ループ
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && Pad_Read() == FALSE)
	{
		Game_Cal();
		Game_Draw();
		
	}

	DxLib_End();

#endif

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