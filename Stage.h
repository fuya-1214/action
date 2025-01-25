#pragma once

#include "StDefine.h"
#include "Application.h"

class Stage
{
public:
	static constexpr int MAP_CHIP_WID = 32;            // �}�b�v�`�b�v�̉��T�C�Y
	static constexpr int MAP_CHIP_HIG = 32;            // �}�b�v�`�b�v�̏c�T�C�Y

	static constexpr int MAP_CHIP_NUMS_X = 11;         // �}�b�v�`�b�v�摜���̑f�ނ̉���
	static constexpr int MAP_CHIP_NUMS_Y = 3;          // �}�b�v�`�b�v�摜���̑f�ނ̏c��
	static constexpr int MAP_CHIP_ALL_NUMS = (MAP_CHIP_NUMS_X * MAP_CHIP_NUMS_Y);      // �}�b�v�`�b�v�摜���̑f�ނ̑���

	static constexpr int MAP_MAX_NUM_X = 50;           // �}�b�v�̍ő�T�C�Y
	static constexpr int MAP_MAX_NUM_Y = 20;

	static constexpr int DSP_CHIP_NUM_X = Application::SCREEN_SIZE_WID / MAP_CHIP_WID;
	static constexpr int DSP_CHIP_NUM_Y = Application::SCREEN_SIZE_HIG / MAP_CHIP_HIG + 1;

	Stage(void);    // �R���X�g���N�^
	~Stage(void);   // �f�X�g���N�^

	bool SystemInit(void);          // ����������(�ŏ��̂P��̂ݎ��s) 
	void GameInit(void);            // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);              // �X�V����
	void Draw(void);                // �`�揈��
	bool Release(void);             // �������(�Ō�̂P��̂ݎ��s)

	bool LoadGroundData(void);      // �O���t�@�C������}�b�v�f�[�^��ǂݍ���

	POSITION GetMapDispStPos(void) { return mapDispStPos; }                	// �}�b�v�\���J�n���W�̎擾
	int GetMapChipNo(POSITION mPos) { return dispMapDat[mPos.y][mPos.x]; }  // �}�b�v���W�̃`�b�v�ԍ����擾����

	void MoveMapToLeft(int mov);
	void MoveMapToRight(int mov);

private:
	int imgMapChipArray[MAP_CHIP_ALL_NUMS];       // �}�b�v�`�b�v�摜�̃n���h���ԍ��e�[�u��

	// �\�����Ă���}�b�v�f�[�^
	int dispMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];
	// �\�����Ă���}�b�v�̃T�C�Y
	POSITION dispMapSize;

	// �n��}�b�v�f�[�^
	int groundMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];

	POSITION mapDispStPos;                       // �}�b�v�\���J�n���W

};
