#pragma once

class SceneManager;

class Application
{
public:
	static constexpr int SCREEN_SIZE_WID = 800;
	static constexpr int SCREEN_SIZE_HIG = 576;

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

