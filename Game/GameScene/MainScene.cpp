#include "stdafx.h"
#include "MainScene.h"
namespace
{
	/** MainSceneの画像のファイルパス */
	const char* MAIN_SCENE_IMAGE_FILE_PATH = "Assets/sprites/MainScene.dds";

	/** MainSceneの画像の横幅 */
	const float MAIN_SCENE_IMAGE_WIDTH = 1720.0f;

	/** MainSceneの画像の縦幅 */
	const float MAIN_SCENE_IMAGE_HEIGHT = 880.0f;

	/** MainSceneの画像位置 */
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

	const float PUSH_SPRITE_HEIGHT = 230.0f;

	const float PUSH_SPRITE_WIDTH = 1720.0f;

	const Vector3 PUSH_SPRITE_POS = Vector3(0.0f, -430.0f, 0.0f);

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

	return true;
}

void MainScene::Update()
{
	m_mainSpriteRender.Update();
	m_pushSpriteRender[0].Update();
}

void MainScene::Render(RenderContext & rc)
{
	m_mainSpriteRender.Draw(rc);

	m_pushSpriteRender[0].Draw(rc);
}
