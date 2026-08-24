#pragma once

#include "Level3DRender/LevelRender.h"
class MainScene;
class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/** 静的アクセス用 */
	static Game* GetInstance() { return m_instance; }

	/** 他クラスからMainSceneを取得するためのgetter */
	MainScene* GetMainScene() const { return m_mainScene; }

private:
	/** メインシーン */
	MainScene* m_mainScene = nullptr;

	/** 自分自身への静的ポインタ */
	static Game* m_instance;
};

