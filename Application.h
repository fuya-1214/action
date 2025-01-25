#pragma once

#include <string>

class SceneManager;

class Application
{
public:
	static constexpr int SCREEN_SIZE_WID = 800;
	static constexpr int SCREEN_SIZE_HIG = 576;

	static const std::string PATH_PLAYER;
	static const std::string PATH_IMAGE;

	Application();
	~Application();

	bool SystemInit(void);
	void Run(void);
	bool Release(void);

private:
	void Update(void);
	void Draw(void);

	SceneManager* sceneMana;    // シーンマネージャークラスのインスタンスのポインタ

};

