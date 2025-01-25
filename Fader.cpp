//--------------------------------------------------------------------------
// �`���v�^�[�S
// ���@���F����@����
//--------------------------------------------------------------------------
// Fader class
#include <DxLib.h>
#include "Fader.h"
#include "Application.h"

// �R���X�g���N�^
Fader::Fader(void)
{
}

// �f�X�g���N�^
Fader::~Fader(void)
{
}

/**
* -----------------------------------------------
* ����������(�ŏ��̂P��̂ݎ��s)
* Input:
*     ����
* Output:
*     bool true = ����I�� / false = �G���[
* -----------------------------------------------
*/
bool Fader::SystemInit(void)
{
	GameInit();

	return true;
}

/**
*------------------------------------------
* �Q�[���N�����E�ĊJ���ɂ��鏈��
* Input:
*    ����
*  Output:
*    ����
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
* �X�V����
* Input:
*    ����
*  Output:
*    ����
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
			// �t�F�[�h�A�E�g�I��
			alpha = 255.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	case E_STAT_FADE_IN:
		alpha -= FADE_SPEED_ALPHA;
		if (alpha < 0)
		{
			// �t�F�[�h�C���I��
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
* �`�揈��
* Input:
*    ����
*  Output:
*    ����
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);    // ���l���u�����h���郂�[�h�ɐݒ�
		DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0, 0, 0), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);           // �u�����h���[�h������
		break;
	default:
		return;
	}
}

/**
*------------------------------------------
* �������(�Ō�̂P��̂ݎ��s)
* Input
*    ����
* Output
*    true = ����I���@/ false =  �G���[�I��
*-----------------------------------------
*/
bool Fader::Release(void)
{
	return true;
}

// �t�F�[�h�A�E�g�E�t�F�[�h�C���J�n���ɌĂяo������
void Fader::SetFade(eFaderStateID id)
{
	stat = id;
	if (stat != E_STAT_FADE_NON)
	{
		endFlg = false;
	}
}
