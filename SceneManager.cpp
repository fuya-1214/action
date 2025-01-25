//--------------------------------------------------------------------------
// �`���v�^�[5
// ���@���F����@����
//--------------------------------------------------------------------------
// SceneManager class
#include <DxLib.h>
#include "SceneManager.h"
#include "Fader.h"
#include "titleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

// �R���X�g���N�^
SceneManager::SceneManager(void)
{
	fader = nullptr;
	titleInst = nullptr;
	gameInst = nullptr;
	gameOver = nullptr;

	scene_ID = waitScene = E_SCENE_NON;
}

// �f�X�g���N�^
SceneManager::~SceneManager(void)
{
}

bool SceneManager::SystemInit(void)
{
	// �C���X�^���X�̍쐬
	fader = new Fader();
	if (fader == nullptr)return false;

	fader->SystemInit();

	sceneChangeFlg = false;

	ChangeScene(E_SCENE_TITLE);

	return true;
}

void SceneManager::GameInit(void)
{
}

void SceneManager::Update(void)
{
	fader->Update();

	if (sceneChangeFlg)
	{
		if (fader->IsEnd() && waitScene != E_SCENE_NON)
		{
			// �t�F�[�h�A�E�g�I��
			ChangeScene(waitScene);
			waitScene = E_SCENE_NON;
			fader->SetFade(E_STAT_FADE_IN);
		}
		else if (fader->IsEnd() && waitScene == E_SCENE_NON)
		{
			// �t�F�[�h�C���I��
			sceneChangeFlg = false;
		}
	}
	else
	{
		eScene_ID nextSceneID = scene_ID;

		switch (scene_ID)
		{
		case E_SCENE_TITLE:
			titleInst->Update();
			nextSceneID = titleInst->GetNextSceneID();
			break;
		case E_SCENE_GAME:
			gameInst->Update();
			nextSceneID = gameInst->GetNextSceneID();
			break;
		case E_SCENE_GAMEOVER:
			gameOver->Update();
			nextSceneID = gameOver->GetNextSceneID();
			break;
		}

		// �V�[���J�ڔ���
		if (scene_ID != nextSceneID)	
		{
			sceneChangeFlg = true;     // �V�[���J�ڏ����J�n
			waitScene = nextSceneID;
			fader->SetFade(E_STAT_FADE_OUT);
		}
	}
}

void SceneManager::Draw(void)
{
	switch (scene_ID)
	{
	case E_SCENE_TITLE:
		titleInst->Draw();
		break;
	case E_SCENE_GAME:
		gameInst->Draw();
		break;
	case E_SCENE_GAMEOVER:
		gameOver->Draw();
		break;
	}

	fader->Draw();
}

bool SceneManager::Release(void)
{
	// �C���X�^���X�̉��
	ReleaseScene(E_SCENE_TITLE);
	ReleaseScene(E_SCENE_GAME);
	ReleaseScene(E_SCENE_GAMEOVER);

	if (fader->Release() == false)return false;
	delete fader;
	fader = nullptr;

	return true;
}

bool SceneManager::ChangeScene(eScene_ID id)
{
	// ���݂̃V�[�����J��
	ReleaseScene(scene_ID);

	// �V�[��ID��ύX
	scene_ID = id;

	switch (scene_ID)
	{
	case E_SCENE_TITLE:
		if (titleInst == nullptr)
		{
			titleInst = new TitleScene();
			if (titleInst == nullptr)return false;
			titleInst->SystemInit();
			titleInst->GameInit();
		}
		break;
	case E_SCENE_GAME:
		if (gameInst == nullptr)
		{
			gameInst = new GameScene();
			if (gameInst == nullptr)return false;
			gameInst->SystemInit();
			gameInst->GameInit();
		}
		break;
	case E_SCENE_GAMEOVER:
		if (gameOver == nullptr)
		{
			gameOver = new GameOverScene();
			if (gameOver == nullptr)return false;
			gameOver->SystemInit();
			gameOver->GameInit();
		}
		break;
	}

	return true;
}

void SceneManager::ReleaseScene(eScene_ID id)
{
	switch (id)
	{
	case E_SCENE_TITLE:
		if (titleInst != nullptr)
		{
			titleInst->Release();
			delete titleInst;
			titleInst = nullptr;
		}
		break;
	case E_SCENE_GAME:
		if (gameInst != nullptr)
		{
			gameInst->Release();
			delete gameInst;
			gameInst = nullptr;
		}
		break;
	case E_SCENE_GAMEOVER:
		if (gameOver != nullptr)
		{
			gameOver->Release();
			delete gameOver;
			gameOver = nullptr;
		}
		break;
	}
}