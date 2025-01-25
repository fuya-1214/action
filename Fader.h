#pragma once
#include "StDefine.h"

class Fader
{
public:
	static constexpr float FADE_SPEED_ALPHA = 2.0f;     // �t�F�[�h�̑���

	Fader(void);             // �R���X�g���N�^
	~Fader(void);            // �f�X�g���N�^

	bool SystemInit(void);         // ����������(�ŏ��̂P��̂ݎ��s)
	void GameInit(void);           // �Q�[���̋N���E�ĊJ���ɕK���Ăяo������
	void Update(void);             // �X�V����
	void Draw(void);               // �`�揈��
	bool Release(void);            // �������(�Ō�̂P��̂ݎ��s)

	// �Q�b�^�[�E�Z�b�^�[�֐�
	eFaderStateID GetNowState(void) { return stat; }
	bool IsEnd(void) { return endFlg; }
	void SetFade(eFaderStateID id);  // �t�F�[�h�A�E�g�E�t�F�[�h�C���J�n��

private:
	eFaderStateID stat;             // ���݂̃t�F�[�h�̏��(�X�e�[�^�X)
	float  alpha;                   // �A���t�@�l�p�̕ϐ�
	bool endFlg;                    // �t�F�[�h�����I���t���O(true=������/false=������)

};
