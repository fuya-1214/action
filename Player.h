#pragma once

#include "StDefine.h"
#include <string>

class Stage;

class Player
{
public:
	static constexpr int CHARA_SIZE_WID = 32;          // �v���C���[�摜�̉��T�C�Y
	static constexpr int CHARA_SIZE_HIG = 32;          // �v���C���[�摜�̏c�T�C�Y
	static constexpr int CHARA_BODY_SIZE_WID = 21;     // �v���C���[�L�����{�̂̉��T�C�Y
	static constexpr int CHARA_BODY_SIZE_HIG = 26;     // �v���C���[�L�����{�̂̏c�T�C�Y
	static constexpr int COLLISION_RECT_L_SPACE = 3;  // �v���C���[�摜�̍����̋󂫃T�C�Y
	static constexpr int COLLISION_RECT_R_SPACE = (CHARA_SIZE_WID - COLLISION_RECT_L_SPACE - CHARA_BODY_SIZE_WID);  // �v���C���[�摜�̉E���̋󂫃T�C�Y

	static constexpr int COLLISION_RECT_Y_OFFSET = 3;   // �Փˋ�`�̃I�t�Z�b�g
	static constexpr int COLLISION_FOOT_RECT_X = -1;     // �Փˋ�`�̃I�t�Z�b�g

	// �ő�A�j���[�V�����p�^�[����
	static constexpr int MAX_ANIM_NUM = 8;
	// �A�j���[�V�����X�s�[�h
	static constexpr float ANIM_SPEED = 0.1f;
	// �v���C���[�̈ړ����x
	static constexpr float MOVE_SPEED = 3.0f;

	// �ő�W�����v��
	static constexpr float MAX_JUMP_POWER = 8.5f;
	// �d��
	static constexpr float GRAVITATION = 0.25f;
	// �W�����v�L�[�̓��͂��󂯕t����v���[����
	static constexpr int INPUT_JUMPWKEY_FRAME = 8;
	// ���[�V�����^�C�v
	enum class MOTION_TYPE
	{
		E_MOTION_IDLE,      // �ҋ@���[�V����
		E_MOTION_RUN,       // ���郂�[�V����
		E_MOTION_JUMP,      // �W�����v���[�V����
		E_MOTION_ATTACK,    // �A�^�b�N���[�V����
		E_MOTION_DAMAGE,    // �_���[�W���[�V����
		E_MOTION_DEATH,     // ���Ń��[�V����

		E_MOTION_MAX,
	};

	// �Փˍ��W(���E)
	enum class COLLISION_LR
	{
		E_CENTER,
		E_LEFT,
		E_RIGHT
	};

	// �Փˍ��W(�㉺)
	enum class COLLISION_TB
	{
		E_CENTER,
		E_TOP,
		E_BOTTOM,
	};

	Player(Stage* stg);
	~Player(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	// �Q�b�^�[�E�Z�b�^�[�֐�
	POSITION_F GetPlayerPos(void) { return pos; }
	void SetPlayerFlgOff(void) { plFlg = false; }


private:
	Stage* stage;    // �X�e�[�W�N���X�̃C���X�^���X�̃|�C���^

	// �v���C���[�摜�̃n���h���ԍ��e�[�u��
	int img[static_cast<int>(MOTION_TYPE::E_MOTION_MAX)][MAX_ANIM_NUM];

	// �v���C���[�̉摜�t�@�C����
	std::string imgFName;

	// �v���C���[�̍��W
	POSITION_F pos;

	// �v���C���[�̃��[�V�����^�C�v
	MOTION_TYPE motionType;

	// �A�j���[�V�����J�E���^
	float fAnimCounter;
	// �W�����v�L�[�̓��̓J�E���^�[
	int inputJumpKeyCounter;

	// �v���C���[�̌���
	DIRECTION dir;

	// �W�����v��
	float jumpPower;
	// �W�����v������
	bool jumpFlg;
	// �W�����v�L�[�̉�������
	bool putJumpKeyFlg;

	int prevJumpKey, nowJumpKey;

	// �v���C���[�摜�̓ǂݍ��ݏ���
	bool LoadPlayerImage(void);
	// �v���C���[�̕`��
	void DrawPlayer(int handleId);
	// �d�͂�������
	void AddGravitation(void);
	// �v���C���[�W�����v����
	void ProcessJump(void);
	// �W�����v
	void Jump(void);
	// �W�����v�͂̐ݒ�
	void SetJumpPower(float power);
	// �v���C���[�̕\���t���O(true=�\��/false=��\��)
	bool plFlg;

	//-----------------------------------------------------
	// �����蔻�菈���֘A�֐�
	//-----------------------------------------------------
	bool IsCollisionStage(POSITION worldPos);
	POSITION World2MapPos(POSITION worldPos);
	// �����̏Փ˔���
	void CollisionFoot(void);
	// ���̏Փ˔���
	void CollisionHead(void);
	// ���E�̏Փ˔���
	void CollisionSide(void);
	POSITION GetCollisionPos(COLLISION_LR lr, COLLISION_TB tb);
	//------------------------------------------------------
};
