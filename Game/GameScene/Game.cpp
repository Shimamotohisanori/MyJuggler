#include "stdafx.h"
#include "Game.h"
#include "MainScene.h"
#include "Reel/MainReel.h"
#include "NumberUI/NumberUI.h"

bool Game::Start()
{	
	
	m_mainReel = NewGO<MainReel>(0, "mainreel");
	m_mainScene = NewGO<MainScene>(0, "mainscene");
	m_numberUI = NewGO<NumberUI>(0, "numberUI");
	m_numberUI->SetCredit(46);
	m_numberUI->SetCount(0);
	m_numberUI->SetPayout(0);
	return true;
}

void Game::Update()
{
	/////////////////////////////////////////
	// 実験的なコード。数字UIのクレジット数を増減させる。
	/////////////////////////////////////////
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		m_numberUI->AddCredit(1);
	}

	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		m_numberUI->AddCredit(-3);
	}

	/////////////////////////////////////////
}

void Game::Render(RenderContext& rc)
{
	
}