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
	int err = LoadDivGraph("image/Stage/TileMap.png", MAP_CHIP_ALL_NUM, MAP_CHIP_NUMS_X, MAP_CHIP_NUMS_Y, MAP_CHIP_WID, MAP_CHIP_HIG, imgMapChipArray);
	if (err == -1)return false;

	return true;
}

// �Q�[���N�����E�ĊJ���ɂ��鏈��
void Stage::GameInit(void)
{
	LoadGroundData();          // �n��}�b�v�f�[�^��ǂݍ���

	ChangeMap(MAP_TYPE::E_MTYPE_GROUND);

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
	for (int yy = 0; yy < dispMapSize.y; yy++)
	{
		if (yy >= DSP_CHIP_NUM_Y)break;
		for (int xx = 0; xx < dispMapSize.x; xx++)
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
	for (int ii = MAP_CHIP_ALL_NUM - 1; ii >= 0; ii--)
	{
		if (DeleteGraph(imgMapChipArray[ii]) == -1)return false;
	}

	return true;
}

// �O���t�@�C������}�b�v�f�[�^��ǂݍ���
bool Stage::LoadGroundData(void)
{
	int loadBuff[MAP_GROUND_NUM_X + 1];

	// �}�b�v�f�[�^�t�@�C�����I�[�v��
	FILE* fp;
	if (fopen_s(&fp, "Stage/Stage.dat", "rb") != 0)return false;

	for (int yy = 0; yy < MAP_GROUND_NUM_Y; yy++)
	{
		fread(loadBuff, sizeof(int), MAP_GROUND_NUM_X, fp);
		memcpy(&groundMapDat[yy], loadBuff, sizeof(int) * MAP_GROUND_NUM_X);
	}

	fclose(fp);

	return true;
}


/*
*--------------------------------------------------- 
* �}�b�v�̏�����Ɉړ�(��ʂ͉��ɃX�N���[��)
* Input;
*    int mov �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output;
*    ����
*----------------------------------------------------
*/
void Stage::MoveMapToUpper(int mov)
{
	mapDispStPos.y -= mov;
	if (mapDispStPos.y < 0)
	{
		mapDispStPos.y = 0;
	}
}
/*
*---------------------------------------------------
* �}�b�v�̉������Ɉړ�(��ʂ͏�ɃX�N���[��)
* Input;
*    int mov �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output;
*    ����
*----------------------------------------------------
*/
void Stage::MoveMapToDown(int mov)
{
	mapDispStPos.y += mov;
	if (mapDispStPos.y + DSP_CHIP_NUM_Y >= MAP_GROUND_NUM_Y)
	{
		mapDispStPos.y = MAP_GROUND_NUM_Y - DSP_CHIP_NUM_Y;
	}
}
/*
*---------------------------------------------------
* �}�b�v�̍������Ɉړ�(��ʂ͉E�ɃX�N���[��)
* Input;
*    int mov �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output;
*    ����
*----------------------------------------------------
*/
void Stage::MoveMapToLeft(int mov)
{
	mapDispStPos.x -= mov;
	if (mapDispStPos.x < 0)
	{
		mapDispStPos.x = 0;
	}
}
/*
*---------------------------------------------------
* �}�b�v�̉E�����Ɉړ�(��ʂ͍��ɃX�N���[��)
* Input;
*    int mov �}�b�v�X�N���[���̈ړ���(�`�b�v��)
* Output;
*    ����
*----------------------------------------------------
*/
void Stage::MoveMapToRight(int mov)
{
	mapDispStPos.x += mov;
	if (mapDispStPos.x + DSP_CHIP_NUM_X >= MAP_GROUND_NUM_X)
	{
		mapDispStPos.x = MAP_GROUND_NUM_X - DSP_CHIP_NUM_X;
	}
}

/*
*---------------------------------------------------
* �}�b�v��ύX����
* Input;
*    MAP_TYPE mtype : �؂�ւ���}�b�v�̎��
* Output;
*    ����
*----------------------------------------------------
*/
void Stage::ChangeMap(MAP_TYPE mtype)
{
	ClearDispMap();        // �}�b�v�̃N���A

	mapType = mtype;

	switch (mapType)
	{
	case MAP_TYPE::E_MTYPE_GROUND:
		// �}�b�v�T�C�Y��ݒ�
		dispMapSize.x = MAP_GROUND_NUM_X;
		dispMapSize.y = MAP_GROUND_NUM_Y;

		// �}�b�v�f�[�^��ݒ肷��
		for (int yy = 0; yy < dispMapSize.y; yy++)
		{
			for (int xx = 0; xx < dispMapSize.x; xx++)
			{
				dispMapDat[yy][xx] = groundMapDat[yy][xx];
			}
		}
		break;
	case MAP_TYPE::E_MTYPE_UNDER_GROUND:
		// �}�b�v�T�C�Y��ݒ�
		dispMapSize.x = MAP_UNDER_GROUND_NUM_X;
		dispMapSize.y = MAP_UNDER_GROUND_NUM_Y;

		// �}�b�v�f�[�^��ݒ肷��
		for (int yy = 0; yy < dispMapSize.y; yy++)
		{
			for (int xx = 0; xx < dispMapSize.x; xx++)
			{
				dispMapDat[yy][xx] = underGroundMapDat[yy][xx];
			}
		}
		break;
	}
}

//�\�����Ă���}�b�v���̏�����
void Stage::ClearDispMap(void)
{
	for (int yy = 0; yy < MAP_MAX_NUM_Y; yy++)
	{
		for (int xx = 0; xx < MAP_MAX_NUM_X; xx++)
		{
			dispMapDat[yy][xx] = -1;
		}
	}
}

/*
 *----------------------------------------------------
 * �w��̃}�b�v���W���K�i���ǂ����𒲂ׂ�
 * Input:
 * POSITION mapPos : �}�b�v���W(0�`)
 * Output:
 * bool : true = �K�i / false = �K�i�ł͂Ȃ�
 *----------------------------------------------------
 */
bool Stage::IsStair(POSITION mapPos)
{
	int chipNo = GetMapChipNo(mapPos);
	if (chipNo >= MAP_CHIP_STAIR1_NO && chipNo <= MAP_CHIP_STAIR5_NO)return true;
	
	return false;
}