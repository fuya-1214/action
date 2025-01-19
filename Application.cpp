//--------------------------------------------------------------------------
// action
// ���@���F����@����
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
	// �V�X�e���ݒ菈��
	SetWindowText("�ŏI��i");                    //�Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);     // �Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);					      // �Q�[���E�B���h�E�̕\�����@(false�F�t���X�N���[��)
	
	if (DxLib_Init() == -1)return false;          // DX���C�u�����̏���������

	// �C���X�^���X�̍쐬
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
	SetDrawScreen(DX_SCREEN_BACK);    // �`�悷���ʂ𗠂̉�ʂɐݒ肷�� 
	ClearDrawScreen();			      // �`�悷���ʂ̓��e������(�N���A)����

	sceneMana->Draw();

	ScreenFlip();                     // ����ʂƕ\��ʂ����ւ���
}
bool Application::Release(void)
{
	sceneMana->Release();
	delete sceneMana;
	sceneMana = nullptr;

	if (DxLib_End() == -1)return false;

	return true;
}
