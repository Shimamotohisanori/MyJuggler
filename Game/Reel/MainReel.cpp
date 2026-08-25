#include "stdafx.h"
#include "MainReel.h"

namespace
{
	const char* REEL_SPRITE_FILE_PATH[3] =
	{
		"Assets/sprites/Spritereel/Mr.LeftReel.dds",
		"Assets/sprites/Spritereel/Mr.CenterReel.dds",
		"Assets/sprites/Spritereel/Mr.RightReel.dds",
	};

	const Vector3 LEFT_REEL_POS   = { -380.0f, 1.0f,0.0f };
	const Vector3 CENTER_REEL_POS = {    0.0f, 1.0f,0.0f };
	const Vector3 RIGHT_REEL_POS  = {  380.0f, 1.0f,0.0f };

	constexpr float REEL_WIDTH = 370.0f;
	constexpr float REEL_HEIGHT = 3000.0f;
}

bool MainReel::Start()
{
	for (int i = 0; i < m_reelNum; i++)
	{
		m_mainReel[i].Init(REEL_SPRITE_FILE_PATH[i], REEL_WIDTH, REEL_HEIGHT);
	}
	m_mainReel[0].SetPosition(LEFT_REEL_POS);
	m_mainReel[1].SetPosition(CENTER_REEL_POS);
	m_mainReel[2].SetPosition(RIGHT_REEL_POS);

	return true;
}

void MainReel::Update()
{
	for (int i = 0; i < m_reelNum; i++)
	{
		m_mainReel[i].Update();
	}
}

void MainReel::Render(RenderContext& rc)
{
	for (int i = 0; i < m_reelNum; i++)
	{
		m_mainReel[i].Draw(rc);
	}
}