#include "stdafx.h"
#include "MainScene.h"
#include <random>

namespace
{
	const char* MAIN_SCENE_IMAGE_FILE_PATH = "Assets/sprites/MainScene.dds";
	constexpr float MAIN_SCENE_IMAGE_WIDTH = 1720.0f;
	constexpr float MAIN_SCENE_IMAGE_HEIGHT = 880.0f;
	const Vector3 MAIN_SCENE_IMAGE_POSITION = Vector3(0.0f, 120.0f, 0.0f);

	const char* PUSU_SPRITE_FILE_PATH[8] =
	{
		"Assets/sprites/Lever/Allpush.dds",
		"Assets/sprites/Lever/Centernotpush.dds",
		"Assets/sprites/Lever/Centerpush.dds",
		"Assets/sprites/Lever/Leftnotpush.dds",
		"Assets/sprites/Lever/Leftpush.dds",
		"Assets/sprites/Lever/Notpush.dds",
		"Assets/sprites/Lever/Rightnotpush.dds",
		"Assets/sprites/Lever/Rightpush.dds",
	};

	const char* GOGO_SPRITE_FILE_PATH = "Assets/sprites/Pekari/GOGO.dds";
	const char* GREEN_GOGO_SPRITE_FILE_PATH = "Assets/sprites/Pekari/GOGO_Green.dds";
	const char* RAINBOW_GOGO_SPRITE_FILE_PATH = "Assets/sprites/Pekari/GOGO_Rainbow.dds";

	const Vector3 GOGO_SPRITE_POS = Vector3(-640.0f, -210.0f, 0.0f);
	constexpr float GOGO_SPRITE_WIDTH = 220.0f;
	constexpr float GOGO_SPRITE_HEIGHT = 170.0f;

	constexpr float PUSH_SPRITE_HEIGHT = 230.0f;
	constexpr float PUSH_SPRITE_WIDTH = 1720.0f;
	const Vector3 PUSH_SPRITE_POS = Vector3(0.0f, -430.0f, 0.0f);

	/** ==== GOGOランプの色の抽選確率（%） ====
	 * 上から順に判定するので、合計が100を超えないように注意すること。 */
	constexpr int RAINBOW_LAMP_RATE_PERCENT = 3;  /** 虹色：3% */
	constexpr int GREEN_LAMP_RATE_PERCENT = 10;   /** 緑　：10%（虹色の3%とは別枠） */
	/** 残り87%は通常色 */

	/** ランプ色抽選専用の乱数エンジン */
	std::mt19937 g_gogoLampMt(std::random_device{}());
}

MainScene::MainScene()
{}

MainScene::~MainScene()
{}

bool MainScene::Start()
{
	m_mainSpriteRender.Init(MAIN_SCENE_IMAGE_FILE_PATH, MAIN_SCENE_IMAGE_WIDTH, MAIN_SCENE_IMAGE_HEIGHT);
	m_mainSpriteRender.SetPosition(MAIN_SCENE_IMAGE_POSITION);

	m_pushSpriteRender[0].Init(PUSU_SPRITE_FILE_PATH[0], PUSH_SPRITE_WIDTH, PUSH_SPRITE_HEIGHT);
	m_pushSpriteRender[0].SetPosition(PUSH_SPRITE_POS);

	m_gogoSpriteRender.Init(GOGO_SPRITE_FILE_PATH, GOGO_SPRITE_WIDTH, GOGO_SPRITE_HEIGHT);
	m_gogoSpriteRender.SetPosition(GOGO_SPRITE_POS);

	m_greenGogoSpriteRender.Init(GREEN_GOGO_SPRITE_FILE_PATH, GOGO_SPRITE_WIDTH, GOGO_SPRITE_HEIGHT);
	m_greenGogoSpriteRender.SetPosition(GOGO_SPRITE_POS);

	m_rainbowGogoSpriteRender.Init(RAINBOW_GOGO_SPRITE_FILE_PATH, GOGO_SPRITE_WIDTH, GOGO_SPRITE_HEIGHT);
	m_rainbowGogoSpriteRender.SetPosition(GOGO_SPRITE_POS);

	return true;
}

void MainScene::Update()
{
	m_mainSpriteRender.Update();
	m_pushSpriteRender[0].Update();
	m_gogoSpriteRender.Update();
	m_greenGogoSpriteRender.Update();
	m_rainbowGogoSpriteRender.Update();
}

void MainScene::Render(RenderContext& rc)
{
	m_mainSpriteRender.Draw(rc);
	m_pushSpriteRender[0].Draw(rc);

	if (m_currentRole == enRole_BIG)
	{
		/** BIGの場合のみ、抽選済みの色でランプを描画する */
		switch (m_currentGogoLampType)
		{
		case GogoLampType::Rainbow:
			m_rainbowGogoSpriteRender.Draw(rc);
			break;
		case GogoLampType::Green:
			m_greenGogoSpriteRender.Draw(rc);
			break;
		case GogoLampType::Normal:
		default:
			m_gogoSpriteRender.Draw(rc);
			break;
		}
	}
	else if (m_currentRole == enRole_REG)
	{
		/** REGは色の抽選をせず、常に通常色で表示する */
		m_gogoSpriteRender.Draw(rc);
	}
}

void MainScene::SetCurrentRole(Role role)
{
	m_currentRole = role;

	if (role == enRole_BIG)
	{
		/** BIGが確定した瞬間に1回だけ、ランプの色を抽選する */
		m_currentGogoLampType = DecideGogoLampType();
	}
	else
	{
		/** BIG以外の場合は通常色に戻しておく（次回BIGが来るまで使われないが、念のため初期化） */
		m_currentGogoLampType = GogoLampType::Normal;
	}
}

GogoLampType MainScene::DecideGogoLampType()
{
	std::uniform_int_distribution<int> dist(0, 99);
	int random = dist(g_gogoLampMt);

	if (random < RAINBOW_LAMP_RATE_PERCENT)
	{
		return GogoLampType::Rainbow; /** 0～2 → 3%の確率で虹色 */
	}

	if (random < RAINBOW_LAMP_RATE_PERCENT + GREEN_LAMP_RATE_PERCENT)
	{
		return GogoLampType::Green; /** 3～12 → 10%の確率で緑 */
	}

	return GogoLampType::Normal; /** 13～99 → 残り87%は通常色 */
}