//--------------------------------------------------------------------------
// action
// ���@���F����@����
//--------------------------------------------------------------------------
// main class
#include <DxLib.h>
#include "Application.h"

//-----------------
// WinMain�֐�
//-----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanced, LPSTR llpCmdLine, int nCmdShow)
{
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