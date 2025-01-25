//--------------------------------------------------------------------------
// �`���v�^�[�S
// ���@���F����@����
//--------------------------------------------------------------------------
// Stage class
#include <DxLib.h>
#include "Stage.h"
#include "Application.h"

// �R���X�g���N�^
Stage::Stage(void)
{
}

// �f�X�g���N�^
Stage::~Stage(void)
{
}

// ����������(�ŏ��̂P��̂ݎ��s)
bool Stage::SystemInit(void)
{
	// �}�b�v�`�b�v�f�[�^��ǂݍ���
	int err = LoadDivGraph("image/Stage/TileMap.png", MAP_CHIP_ALL_NUMS, MAP_CHIP_NUMS_X, MAP_CHIP_NUMS_Y, MAP_CHIP_WID, MAP_CHIP_HIG, imgMapChipArray);
	if (err == -1)return false;

	return true;
}

// �Q�[���N�����E�ĊJ���ɂ��鏈��
void Stage::GameInit(void)
{
	LoadStageData();          // �X�e�[�W�f�[�^��ǂݍ���

	mapDispStPos.x = mapDispStPos.y = 0;
}

// �X�V����
void Stage::Update(void)
{
}

// �`�揈��
void Stage::Draw(void)
{
	// �܂��w�i�����œh��Ԃ�
	DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0, 0, 0), true);
	// �}�b�v�`�b�v�摜��\������
	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		if (yy >= DSP_CHIP_NUM_Y)break;
		for (int xx = 0; xx < MAP_MAX_NUM_X; xx++)
		{
			if (xx >= DSP_CHIP_NUM_X)break;
			int chip = dispMapDat[mapDispStPos.y+yy][mapDispStPos.x+xx];
			int dx = MAP_CHIP_WID * xx;
			int dy = MAP_CHIP_HIG * yy;
			DrawGraph(dx, dy, imgMapChipArray[chip], true);
		}
	}
}

// �������(�Ō�̂P��̂ݎ��s)
bool Stage::Release(void)
{
	for (int ii = MAP_CHIP_ALL_NUMS - 1; ii >= 0; ii--)
	{
		if (DeleteGraph(imgMapChipArray[ii]) == -1)return false;
	}

	return true;
}

// �O���t�@�C������}�b�v�f�[�^��ǂݍ���
bool Stage::LoadStageData(void)
{
	int loadBuff[MAP_MAX_NUM_X + 1];

	// �}�b�v�f�[�^�t�@�C�����I�[�v��
	FILE* fp;
	if (fopen_s(&fp, "Stage/Sample.dat", "rb") != 0)return false;

	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		fread(loadBuff, sizeof(int), MAP_MAX_NUM_X, fp);
		memcpy(&dispMapDat[yy], loadBuff, sizeof(int) * MAP_MAX_NUM_X);
	}

	fclose(fp);

	return true;
}

/*
*-------------------------------------------
* �}�b�v�̍������Ɉړ�(��ʂ͉E�ɃX�N���[��)
* INPUT:
*    int mov : �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output:
*    ����
*-------------------------------------------
*/
void Stage::MoveMapToLeft(int mov)
{
	mapDispStPos.x -= mov;
	if (mapDispStPos.x < 0)mapDispStPos.x = 0;
}

/*
*-------------------------------------------
* �}�b�v�̉E�����Ɉړ�(��ʂ͍��ɃX�N���[��)
* INPUT:
*    int mov : �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output:
*    ����
*-------------------------------------------
*/
void Stage::MoveMapToRight(int mov)
{
	mapDispStPos.x += mov;
	if (mapDispStPos.x + DSP_CHIP_NUM_X >= MAP_MAX_NUM_X)
	{
		mapDispStPos.x = MAP_MAX_NUM_X - DSP_CHIP_NUM_X;
	}
}
