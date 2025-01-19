//--------------------------------------------------------------------------
// action
// ���@���F����@����
//--------------------------------------------------------------------------
// main class
#include <DxLib.h>
#include "Application.h"

#if 0
#define WINDOW_WIDTH (1600)
#define WINDOW_HEGHT (900)

// �p�b�h�̏���񋓑̂Œ�`
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

// �p�b�g�̃r�b�g���
int Pad_Inp;

// �p�b�g�̉������J�E���g��
int Pad_Cou[e_But::But_Total];

// �p�b�h�̓��͏����擾����֐�
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

// �Q�[���J�n���̏������s���֐�
void Game_Init()
{

}

// �Q�[���I�����̏������s���֐�
void Game_End()
{
}

// �Q�[���v�Z�������s���֐�
void Game_Cal()
{
}

// �Q�[���`�揈�����s���֐�
void Game_Draw()
{
}
#endif

//-----------------
// WinMain�֐�
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanced, LPSTR llpCmdLine, int nCmdShow)
{
#if 0	
	ChangeWindowMode(TRUE);
	DxLib_Init();

	// �E�B���h�E�̏�����
	SetMainWindowText("����");
	SetWindowInitPosition(0, 0);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEGHT, 32);  // �w�i�摜�̏�����
	SetDrawScreen(DX_SCREEN_BACK);

	Game_Init();

	// 1�b�Ԃ�60��(FPS��)�������[�v
	while (ScreenFlip() == 0 && ClearDrawScreen() == 0 && ProcessMessage() == 0 && Pad_Read() == FALSE)
	{
		Game_Cal();
		Game_Draw();
		
	}

	DxLib_End();

#endif

	// �A�v���P�[�V�����N���X�̎��̉������I�u�W�F�N�g�̍쐬
	Application apl;

	// ����������
	apl.SystemInit();

	// �Q�[���̋N��
	apl.Run();

	// �������
	apl.Release();

	return 0;
}