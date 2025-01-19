#pragma once

//--------------------
// �񋓌^��`
//--------------------
// �V�[����`
enum eScene_ID
{
	E_SCENE_NON = -1,

	E_SCENE_TITLE,     // �^�C�g�����
	E_SCENE_GAME,      // �Q�[���V�[�����
	E_SCENE_GAMEOVER,  // �Q�[���I�[�o�[���


	E_SCENE_ID_MAX,
};

// �t�F�[�h�̏��
enum eFaderStateID
{
	E_STAT_FADE_NON = -1,
	E_STAT_FADE_OUT,        // �t�F�[�h�A�E�g(���X�ɈÓ]����)
	E_STAT_FADE_IN,         // �t�F�[�h�C��(���X�ɖ��]����)


	E_STAT_FADE_MAX,

};

// ����
enum class DIRECTION
{
	E_DIR_DOWN,        // ��	
	E_DIR_UP,          // ��
	E_DIR_LEFT,        // ��
	E_DIR_RIGHT,       // �E

	E_DIR_MAX,
};

//--------------------
// �\���̒�`
//--------------------
struct POSITION
{
	int x;
	int y;
};

struct POSITION_F
{
	float x;
	float y;
};
