//--------------------------------------------------------------------------
// action
// ���@���F����@����
//--------------------------------------------------------------------------
// Player class
#include <DxLib.h>
#include <string>
#include "Player.h"
#include "Application.h"
#include "CommonUtility.h"
#include "Stage.h"

Player::Player(Stage* std)
{
	stage = std;
}

Player::~Player(void)
{
}

bool Player::SystemInit(void)
{
	if (!LoadPlayerImage())return false;

	return true;
}

void Player::GameInit(void)
{
	// ���[�V�����^�C�v
	motionType = MOTION_TYPE::E_MOTION_IDLE;
	// �A�j���[�V�����J�E���^
	fAnimCounter = 0.0f;
	// �v���C���[�̏����ʒu
	pos = { 100.0f,100.0f };
	// �v���C���[�̌���
	dir = DIRECTION::E_DIR_RIGHT;
	// �W�����v��
	jumpPower = 0.0f;
	jumpFlg = true;
	// �W�����v�L�[��������
	putJumpKeyFlg = false;

	// �W�����v�L�[�̓��̓J�E���^�[
	// �X�^�[�g����́A1�񒅒n���Ȃ��ƃW�����v�����Ȃ�
	inputJumpKeyCounter = INPUT_JUMPWKEY_FRAME;

	prevJumpKey = nowJumpKey = 0;
	plFlg = true;
}

void Player::Update(void)
{
	if (plFlg == false)
	{
		// �ĕ\������
		pos = { 100.0f,100.0f };

		plFlg = true;
	}
	// ���[�V�����̏����ݒ�
	motionType = MOTION_TYPE::E_MOTION_IDLE;

	// �ړ����̏���
	// ������
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		dir = DIRECTION::E_DIR_LEFT;
		// ���[�V�����̕ύX
		motionType = MOTION_TYPE::E_MOTION_RUN;
		// �ړ����x
		pos.x -= MOVE_SPEED;
	}

	// �E����
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		dir = DIRECTION::E_DIR_RIGHT;
		// ���[�V�����̕ύX
		motionType = MOTION_TYPE::E_MOTION_RUN;
		// �ړ����x
		pos.x += MOVE_SPEED;
	}

	// ��ʊO�ɔ�яo���Ȃ��悤�ɂ���
	// ����
	if (pos.x < 0)pos.x = 0;

	//�E��
	if (pos.x >= Application::SCREEN_SIZE_WID)
	{
//		pos.x = Application::SCREEN_SIZE_WID - CHARA_BODY_SIZE_WID - 1;
	}

	// ���E�̏Փ˔���
	CollisionSide();

	// �v���C���[�̃W�����v����
	ProcessJump();
	// �d�͂���ɂ�����(�W�����v���Ŗ����Ă���������)
	AddGravitation();
	// �W�����v
	Jump();
	// �����̏Փ˔���
	CollisionFoot();
	// ���̏Փ˔���
	CollisionHead();
}

// �d�͂�������
void Player::AddGravitation(void)
{
	// ���݂̃W�����v�͂ɏd�͂�������
	float power = jumpPower + GRAVITATION;
	SetJumpPower(power);
}

// �v���C���[�W�����v����
void Player::ProcessJump(void)
{
	prevJumpKey = nowJumpKey;
	nowJumpKey = CheckHitKey(KEY_INPUT_W);

	// ���n���Ă��Ȃ��ƃW�����v���J�n�ł��Ȃ��悤�ɂ���
	if (nowJumpKey == 1 && !jumpFlg)
	{
		jumpFlg = true;
		putJumpKeyFlg = true;
	}

	// ���͎��Ԃɉ����ăW�����v�͂�ύX����
	if (nowJumpKey == 1 && inputJumpKeyCounter < INPUT_JUMPWKEY_FRAME && putJumpKeyFlg)
	{
		// �W�����v�L�[���̓J�E���^�[�𑝂₷
		inputJumpKeyCounter++;

		// �W�����v�͂𕪔z���Z����
		float power = jumpPower - (MAX_JUMP_POWER / static_cast<float>(INPUT_JUMPWKEY_FRAME));
		SetJumpPower(power);

		jumpFlg = true;

		if (prevJumpKey == 1 && nowJumpKey == 0)
		{
			// �W�����v�L�[�𗣂�����A�W�����v�L�[����͔�����I��
			inputJumpKeyCounter = INPUT_JUMPWKEY_FRAME;
		}
	}
}

// �W�����v
void Player::Jump(void)
{
	pos.y += jumpPower;
}

// �W�����v�͂̐ݒ�
void Player::SetJumpPower(float power)
{
	// �W�����v�͂�ݒ�
	jumpPower = power;

	// �d�͂������肷����̂�h��
	if (jumpPower > MAX_JUMP_POWER)
	{
		jumpPower = MAX_JUMP_POWER;
	}
}

void Player::Draw(void)
{
	if (plFlg)
	{

		if (nowJumpKey == 1)
		{
			motionType = MOTION_TYPE::E_MOTION_JUMP;
		}

		// ���݂̃��[�V����
		int nowMotion = static_cast<int>(motionType);

		switch (motionType)
		{
		case MOTION_TYPE::E_MOTION_IDLE:
			DrawPlayer(img[nowMotion][0]);
			break;

		case MOTION_TYPE::E_MOTION_ATTACK:
		case MOTION_TYPE::E_MOTION_DAMAGE:
		case MOTION_TYPE::E_MOTION_RUN:
		{
			fAnimCounter += ANIM_SPEED;
			int idx = (CommonUtility::Round(fAnimCounter)) % 4;
			DrawPlayer(img[nowMotion][idx]);
		}
		break;
		case MOTION_TYPE::E_MOTION_DEATH:
		case MOTION_TYPE::E_MOTION_JUMP:
		{
			fAnimCounter += ANIM_SPEED;
			int idz = (CommonUtility::Round(fAnimCounter)) % MAX_ANIM_NUM;
			DrawPlayer(img[nowMotion][idz]);
		}
		break;
		}
	}
}

bool Player::Release(void)
{
	int motion_max = static_cast<int>(MOTION_TYPE::E_MOTION_MAX);

	for (int ii = 0; ii < motion_max; ii++)
	{
		for (int jj = 0; jj < MAX_ANIM_NUM; jj++)
		{
			if (img[ii][jj] != -1)
			{
				if (DeleteGraph(img[ii][jj]) == -1)return false;
			}
		}
	}

	return true;
}

// �v���C���[�摜�̓ǂݍ��ݏ���
bool Player::LoadPlayerImage(void)
{
	std::string basePath = Application::PATH_PLAYER;

	int motion = 0;
	int motion_max = static_cast<int>(MOTION_TYPE::E_MOTION_MAX);

	// �摜�n���h���ԍ��e�[�u���̏�����
	for (int ii = 0; ii < motion_max; ii++)
	{
		for (int jj = 0; jj < MAX_ANIM_NUM; jj++)
		{
			img[ii][jj] = -1;
		}
	}

	//----------------------------------------------
	// �P�����Ȃ��摜���ʂɓǍ���
	//----------------------------------------------
	// �ҋ@���[�V����
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_IDLE);
	img[motion][0] = LoadGraph((Application::PATH_PLAYER + "Stop.png").c_str());
	if (img[motion][0] == -1)return false;

	// ���郂�[�V����
	int run;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_RUN);
	run = LoadDivGraph((Application::PATH_PLAYER + "Run.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (run == -1)return false;

	// �W�����v���[�V����	
	int jump;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_JUMP);
	jump = LoadDivGraph((Application::PATH_PLAYER + "Jump.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (jump == -1)return false;

	// �A�^�b�N���[�V����
	int attack;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_ATTACK);
	attack = LoadDivGraph((Application::PATH_PLAYER + "Attack.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (attack == -1)return false;

	// �_���[�W���[�V����
	int damage;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_DAMAGE);
	damage = LoadDivGraph((Application::PATH_PLAYER + "Damage.png").c_str(), MAX_ANIM_NUM / 2, MAX_ANIM_NUM / 2, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (damage == -1)return false;

	// ���Ń��[�V����
	int death;
	motion = static_cast<int>(MOTION_TYPE::E_MOTION_DEATH);
	death = LoadDivGraph((Application::PATH_PLAYER + "Death.png").c_str(), MAX_ANIM_NUM, MAX_ANIM_NUM, 1, CHARA_SIZE_WID, CHARA_SIZE_HIG, &img[motion][0]);
	if (death == -1)return false;

	return true;
}

// �v���C���[�̕`��
void Player::DrawPlayer(int handleId)
{
	POSITION pPos = CommonUtility::Round(pos);
	POSITION stPos = stage->GetMapDispStPos();
	pPos.x -= (stPos.x * Stage::MAP_CHIP_WID);

	// �v���C���[�̕`��
	bool leftFlg = true;
	if (dir == DIRECTION::E_DIR_RIGHT)
	{
		leftFlg = false;
	}

	DrawRotaGraph(pPos.x, pPos.y, 1.0, 0.0, handleId, true, leftFlg);
}

//-----------------------------------------------------
// �����蔻�菈���֘A�֐�
//-----------------------------------------------------
/**
 *----------------------------------------------------
 * ���[���h���W�̎w���n�`�͏ՓˑΏۂ����ׂ�(�Փ˔���)
 * Input:
 * POSITION worldPos : ���[���h���W
 * Output:
 * bool : true = �ʍs�s�� / false = �ʍs�\
 *----------------------------------------------------
 */
bool Player::IsCollisionStage(POSITION worldPos)
{
	// ���[���h���W���}�b�v���W�֕ϊ�
	POSITION mapPos = World2MapPos(worldPos);
	// �}�b�v�\���J�n���W�̎擾
	POSITION stPos = stage->GetMapDispStPos();
	mapPos.x -= stPos.x;

	int chipNo = stage->GetMapChipNo(mapPos);

	if (chipNo >= 10)return true;
	return false;
}

/**
 *----------------------------------------------------
 * ���[���h���W���}�b�v���W�ɕϊ�����
 * Input:
 * POSITION worldPos : ���[���h���W
 * Output:
 * POSITION : �}�b�v���W
 *----------------------------------------------------
 */
POSITION Player::World2MapPos(POSITION worldPos)
{
	POSITION mapPos;

	mapPos.x = mapPos.y = 0;
	mapPos.x = worldPos.x / Stage::MAP_CHIP_WID;
	mapPos.y = worldPos.y / Stage::MAP_CHIP_HIG;

	return mapPos;
}

/**
 *----------------------------------------------------
 * �����̏Փ˔���
 * Input:
 * ����
 * Output:
 * ����
 *----------------------------------------------------
*/
void Player::CollisionFoot(void)
{
	// �����̍��W(���S)
	POSITION footPosC = GetCollisionPos(COLLISION_LR::E_CENTER, COLLISION_TB::E_BOTTOM);

	// �����̍��W(��)
	POSITION footPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_BOTTOM);

	// �����̍��W(�E)
	POSITION footPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_BOTTOM);

	if (IsCollisionStage(footPosC) || IsCollisionStage(footPosL) || IsCollisionStage(footPosR))
	{
		// �v���C���[��Y���W��n�ʂɐڐG�������W�ɐݒ肷��
		POSITION mPos = World2MapPos(footPosC);
		pos.y = static_cast<float>((mPos.y * Stage::MAP_CHIP_HIG) - 1 - (CHARA_SIZE_HIG / 2));

		// �n�ʂɂ����̂ŃW�����v�����Z�b�g����
		jumpFlg = false;
		SetJumpPower(0.0f);

		// �ݒu������W�����v�L�[���̓J�E���^�[���N���A����
		inputJumpKeyCounter = 0;
		// �W�����v�L�[��������
		putJumpKeyFlg = false;
	}

	// �󒆔���
	if (!jumpFlg)
	{
		footPosC.y++;
		footPosL.y++;
		footPosR.y++;
		if (!(IsCollisionStage(footPosC) || IsCollisionStage(footPosL) || IsCollisionStage(footPosR)))
		{
			// ���n���Ă��Ȃ��̂ŃW�����v����ɂ���
			jumpFlg = true;
		}
	}
}

/**
 *----------------------------------------------------
 * ����̏Փ˔���
 * Input:
 * ����
 * Output:
 * ����
 *----------------------------------------------------
*/
void Player::CollisionHead(void)
{
	// ����̍��W(���S)
	POSITION headPosC = GetCollisionPos(COLLISION_LR::E_CENTER, COLLISION_TB::E_TOP);

	// ����̍��W(��)
	POSITION headPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_TOP);

	// ����̍��W(�E)
	POSITION headPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_TOP);

	if (IsCollisionStage(headPosC) || IsCollisionStage(headPosL) || IsCollisionStage(headPosR))
	{
		// �v���C���[��Y���W��V��ɐݒu�������W�ɐݒ肷��
		POSITION mPos = World2MapPos(headPosC);
		pos.y = static_cast<float>(((mPos.y + 1) * Stage::MAP_CHIP_HIG) + (CHARA_BODY_SIZE_HIG / 2));
		pos.y -= COLLISION_RECT_Y_OFFSET;

		// �����Ԃ������̂ŁA�W�����v�͂����Z�b�g
		SetJumpPower(0.0f);
	}
}

/**
 *----------------------------------------------------
 * ���E�̏Փ˔���
 * Input:
 * ����
 * Output:
 * ����
 *----------------------------------------------------
*/
void Player::CollisionSide(void)
{
	// �E���̏Փ˔���
	POSITION headPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_TOP);
	POSITION centerPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_CENTER);
	POSITION footPosR = GetCollisionPos(COLLISION_LR::E_RIGHT, COLLISION_TB::E_BOTTOM);

	if (IsCollisionStage(headPosR) || IsCollisionStage(centerPosR) || IsCollisionStage(footPosR))
	{
		POSITION mPos = World2MapPos(headPosR);
		if (IsCollisionStage(footPosR))
		{
			// �������Ԃ����Ă��鎞
			pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - COLLISION_FOOT_RECT_X);
		}
		else
		{
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// �E�������Ă���Ƃ�
				pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - ((COLLISION_RECT_L_SPACE + CHARA_BODY_SIZE_WID) - (CHARA_SIZE_WID / 2)));
			}
			else
			{
				// ���������Ă���Ƃ�
				pos.x = static_cast<float>((mPos.x * Stage::MAP_CHIP_WID) - 1 - (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE));
			}
		}
	}

	// �����̏Փ˔���
	POSITION headPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_TOP);
	POSITION centerPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_CENTER);
	POSITION footPosL = GetCollisionPos(COLLISION_LR::E_LEFT, COLLISION_TB::E_BOTTOM);
	if (IsCollisionStage(headPosL) || IsCollisionStage(centerPosL) || IsCollisionStage(footPosL))
	{
		POSITION mPos = World2MapPos(headPosL);
		if (IsCollisionStage(footPosL))
		{
			// �������Ԃ����Ă��鎞
			pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + COLLISION_FOOT_RECT_X);
		}
		else
		{
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// �E�������Ă���Ƃ�
				pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE));
			}
			else
			{
				// ���������Ă���Ƃ�
				pos.x = static_cast<float>((mPos.x + 1) * Stage::MAP_CHIP_WID + (CHARA_SIZE_WID / 2 - COLLISION_RECT_R_SPACE));
			}
		}
	}
}

/**
*----------------------------------------------------
* �Փ˔���̍��W���擾����
* Input:
* COLLISION_LR lr : ���E�̈ʒu
* COLLISION_TB tb : �㉺�̈ʒu
* Output:
* �w�肳�ꂽ�ʒu�̔�����W
*----------------------------------------------------
*/
POSITION Player::GetCollisionPos(COLLISION_LR lr, COLLISION_TB tb)
{
	POSITION pPos = CommonUtility::Round(pos);

	// ���E
	switch (lr)
	{
	case COLLISION_LR::E_LEFT:
		if (tb == COLLISION_TB::E_BOTTOM)
		{
			// �����̉E��
			pPos.x -= COLLISION_FOOT_RECT_X;
		}
		else
		{
			// �����ȊO�̍���
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// �E�������Ă���Ƃ�
				pPos.x -= (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE);
			}
			else
			{
				// ���������Ă���Ƃ�
				pPos.x -= (CHARA_SIZE_WID / 2 - COLLISION_RECT_R_SPACE);
			}
		}
		break;
	case COLLISION_LR::E_RIGHT:
		if (tb == COLLISION_TB::E_BOTTOM)
		{
			// �����̉E��
			pPos.x += COLLISION_FOOT_RECT_X;
		}
		else
		{
			// �����ȊO�̉E��
			if (dir == DIRECTION::E_DIR_RIGHT)
			{
				// �E�������Ă���Ƃ�
				pPos.x += ((COLLISION_RECT_L_SPACE + CHARA_BODY_SIZE_WID) - (CHARA_SIZE_WID / 2));
			}
			if (dir == DIRECTION::E_DIR_LEFT)
			{
				// ���������Ă���Ƃ�
				pPos.x += (CHARA_SIZE_WID / 2 - COLLISION_RECT_L_SPACE);
			}
		}
		break;
	}

	// �㉺
	switch (tb)
	{
	case COLLISION_TB::E_TOP:
		pPos.y -= (CHARA_BODY_SIZE_HIG / 2);
		break;
	case COLLISION_TB::E_BOTTOM:
		pPos.y += (CHARA_BODY_SIZE_HIG / 2);
		break;
	}

	return pPos;
}