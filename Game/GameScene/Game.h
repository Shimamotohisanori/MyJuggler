#pragma once

#include "Level3DRender/LevelRender.h"
class MainScene;
class MainReel;
class NumberUI;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/** メインシーン */
	MainScene* m_mainScene = nullptr;

	/** メインリール */
	MainReel* m_mainReel = nullptr;
	
	/** 数字UI */
	NumberUI* m_numberUI = nullptr;

};

