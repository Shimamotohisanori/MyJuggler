#include "stdafx.h"
#include "Game.h"
#include "MainScene.h"

/** 静的メンバの実体を定義 */
Game* Game::m_instance = nullptr;

bool Game::Start()
{
	m_instance = this;

	m_mainScene = NewGO<MainScene>(0,"mainScene");
	
	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
}