#pragma once
class MainReel : public IGameObject
{
public:
	MainReel(){}
	~MainReel(){}

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/** リール配列の数 */
	uint8_t m_reelNum = 3;

private:
	SpriteRender m_mainReel[3];

};

