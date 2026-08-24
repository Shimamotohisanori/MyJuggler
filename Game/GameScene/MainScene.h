#pragma once

/** ゲーム画面クラス */
class MainScene : public IGameObject
{
public:
	MainScene();
	~MainScene();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:

	/** メイン画面の画像 */
	SpriteRender m_mainSpriteRender;

	SpriteRender m_pushSpriteRender[8];
};

