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
	static constexpr int MAP_CHIP_ALL_NUM = (MAP_CHIP_NUMS_X * MAP_CHIP_NUMS_Y);      // �}�b�v�`�b�v�摜���̑f�ނ̑���

	static constexpr int MAP_MAX_NUM_X = 70;           // �}�b�v�̍ő�T�C�Y
	static constexpr int MAP_MAX_NUM_Y = 70;

	static constexpr int MAP_GROUND_NUM_X = 50;        // �n��}�b�v�T�C�Y�̉�
	static constexpr int MAP_GROUND_NUM_Y = 50;        // �n��}�b�v�T�C�Y�̏c

	static constexpr int MAP_UNDER_GROUND_NUM_X = 50;  // �n���̃}�b�v�T�C�Y��
	static constexpr int MAP_UNDER_GROUND_NUM_Y = 50;  // �n���̃}�b�v�T�C�Y�c
	
	static constexpr int DSP_CHIP_NUM_X = Application::SCREEN_SIZE_WID / MAP_CHIP_WID;
	static constexpr int DSP_CHIP_NUM_Y = Application::SCREEN_SIZE_HIG / MAP_CHIP_HIG + 1;

	static constexpr int MAP_SIZE_WID = MAP_CHIP_WID * MAP_GROUND_NUM_X;  // �}�b�v�̉��T�C�Y
	static constexpr int MAP_SIZE_HIG = MAP_CHIP_HIG * MAP_GROUND_NUM_Y;  // �}�b�v�̏c�T�C�Y

	static constexpr int MAP_CHIP_STAIR1_NO = 20;     // �K�i�̒n�`�ԍ�
	static constexpr int MAP_CHIP_STAIR2_NO = 21;     // �K�i�̒n�`�ԍ�
	static constexpr int MAP_CHIP_STAIR3_NO = 22;     // �K�i�̒n�`�ԍ�
	static constexpr int MAP_CHIP_STAIR4_NO = 23;     // �K�i�̒n�`�ԍ�
	static constexpr int MAP_CHIP_STAIR5_NO = 24;     // �K�i�̒n�`�ԍ�

	enum class MAP_TYPE
	{
		E_MTYPE_NON,
		E_MTYPE_GROUND,        // �n��}�b�v
		E_MTYPE_UNDER_GROUND,  // �n���}�b�v

		E_MTYPE_MAX,
	};

	Stage(void);    // �R���X�g���N�^
	~Stage(void);   // �f�X�g���N�^

	bool SystemInit(void);          // ����������(�ŏ��̂P��̂ݎ��s) 
	void GameInit(void);            // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);              // �X�V����
	void Draw(void);                // �`�揈��
	bool Release(void);             // �������(�Ō�̂P��̂ݎ��s)

	bool LoadGroundData(void);      // �O���t�@�C������}�b�v�f�[�^��ǂݍ���
	bool LoadUnderGroundData(void); // �O���t�@�C������n���}�b�v�f�[�^��ǂݍ���

	// �Q�b�^�[�E�Z�b�^�[�֐�
	void MoveMapToUpper(int mov);     // �}�b�v�̏�����Ɉړ�(��ʂ͉��ɃX�N���[��)
	void MoveMapToDown(int mov);      // �}�b�v�̉������Ɉړ�(��ʂ͏�ɃX�N���[��)
	void MoveMapToLeft(int mov);      // �}�b�v�̍������Ɉړ�(��ʂ͉E�ɃX�N���[��)
	void MoveMapToRight(int mov);     // �}�b�v�̉E�����Ɉړ�(��ʂ͍��ɃX�N���[��)

	POSITION GetMapDispStPos(void) { return mapDispStPos; }
	int GetMapChipNo(POSITION mPos) { return dispMapDat[mPos.y][mPos.x]; }  // �}�b�v���W�̃`�b�v�ԍ����擾����
	POSITION GetDispMapSize(void) { return dispMapSize; }    // �\�����Ă���}�b�v�̃T�C�Y���擾����
	MAP_TYPE GetMapType(void) { return mapType; } // �\�����Ă���}�b�v�̎�ʂ��擾����
	bool IsStair(POSITION mapPos);    // �w��̃}�b�v���W���K�i���ǂ����𒲂ׂ�

	// �}�b�v��ύX����
	void ChangeMap(MAP_TYPE mtype);

private:
	int imgMapChipArray[MAP_CHIP_ALL_NUM];       // �}�b�v�`�b�v�摜�̃n���h���ԍ��e�[�u��

	// �\�����Ă���}�b�v�f�[�^
	int dispMapDat[MAP_MAX_NUM_Y][MAP_MAX_NUM_X];
	// �\�����Ă���}�b�v�̃T�C�Y
	POSITION dispMapSize;
	// �\�����Ă���}�b�v�̎��
	MAP_TYPE mapType;

	// �n��}�b�v�f�[�^
	int groundMapDat[MAP_GROUND_NUM_Y][MAP_GROUND_NUM_X];
	// �n���}�b�v�f�[�^
	int underGroundMapDat[MAP_UNDER_GROUND_NUM_Y][MAP_UNDER_GROUND_NUM_X];

	POSITION mapDispStPos;                       // �}�b�v�\���J�n���W

	// �\�����Ă���}�b�v�̏�������������
	void ClearDispMap(void);
};
