#include "stdafx.h"
#include "MainScene.h"
namespace
{
	/** MainSceneの画像のファイルパス */
	const char* MAIN_SCENE_IMAGE_FILE_PATH = "Assets/sprites/MainScene.dds";

	/** MainSceneの画像の横幅 */
	constexpr float MAIN_SCENE_IMAGE_WIDTH = 1720.0f;

	/** MainSceneの画像の縦幅 */
	constexpr float MAIN_SCENE_IMAGE_HEIGHT = 880.0f;

	/** MainSceneの画像位置 */
	const Vector3 MAIN_SCENE_IMAGE_POSITION = Vector3(0.0f, 120.0f, 0.0f);

}

MainScene::MainScene()
{}

MainScene::~MainScene()
{}

bool MainScene::Start()
{
	m_mainSpriteRender.Init(MAIN_SCENE_IMAGE_FILE_PATH, MAIN_SCENE_IMAGE_WIDTH, MAIN_SCENE_IMAGE_HEIGHT);
	m_mainSpriteRender.SetPosition(MAIN_SCENE_IMAGE_POSITION);

	

	return true;
}

void MainScene::Update()
{
	m_mainSpriteRender.Update();
}

void MainScene::Render(RenderContext & rc)
{
	m_mainSpriteRender.Draw(rc);

}
