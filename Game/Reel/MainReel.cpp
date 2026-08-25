#include "stdafx.h"
#include "MainReel.h"

namespace
{
	/** リールのファイルパス */
	const char* REEL_SPRITE_FILE_PATH[3] =
	{
		"Assets/sprites/Spritereel/Mr.LeftReel.dds",
		"Assets/sprites/Spritereel/Mr.CenterReel.dds",
		"Assets/sprites/Spritereel/Mr.RightReel.dds",
	};

	/** それぞれ三つのリールのX座標 */
	constexpr float REEL_POS_X[3] = { -380.0f,0.0f,380.0f };
	constexpr float REEL_POS_Z = 0.0f;


	/** リールの大きさ */
	constexpr float REEL_WIDTH = 370.0f;
	constexpr float REEL_HEIGHT = 3000.0f;

	static constexpr float REEL_SPEED = 55.0f;

	/** MAXBET設定するBET数 */
	static constexpr int MAX_BET = 3;
}

bool MainReel::Start()
{
	/** 各リールに同じ画像を二枚並べて初期化する */
	for (int i = 0; i < m_reelNum; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			m_mainReel[i][j].Init(REEL_SPRITE_FILE_PATH[i], REEL_WIDTH, REEL_HEIGHT);
		}

		/** 一枚目は基準位置、二枚目はその真上に配置しておく */
		m_mainReel[i][0].SetPosition({ REEL_POS_X[i],1.0f,REEL_POS_Z });
		m_mainReel[i][1].SetPosition({ REEL_POS_X[i], 1.0f + REEL_HEIGHT, REEL_POS_Z });

	}

	return true;
}

void MainReel::Update()
{
	// ボタン入力の判定
	UpdateInput();

	for (int i = 0; i < m_reelNum; i++)
	{
		// 回転中のリールだけスクロールさせる
		if (m_reelState[i] == ReelState::Spinning)
		{
			// スクロール量を進める(上から下へ移動させたいのでYを減算)
			m_scrollY[i] -= REEL_SPEED;

			// 1枚分の高さを超えてループしたら、スクロール量をリセット
			if (m_scrollY[i] <= -REEL_HEIGHT)
			{
				m_scrollY[i] += REEL_HEIGHT;
			}
		}

		// 2枚のスプライトに同じスクロール量を反映(片方は+REEL_HEIGHTした位置)
		m_mainReel[i][0].SetPosition({ REEL_POS_X[i], 1.0f + m_scrollY[i], REEL_POS_Z });
		m_mainReel[i][1].SetPosition({ REEL_POS_X[i], 1.0f + m_scrollY[i] + REEL_HEIGHT, REEL_POS_Z });

		m_mainReel[i][0].Update();
		m_mainReel[i][1].Update();
	}
}

void MainReel::UpdateInput()
{
	auto& pad = g_pad[0];

	/** 回転開始(全リール停止中のみ) */
	if (pad->IsTrigger(nsK2EngineLow::enButtonSelect))
	{
		StartSpin();
	}

	/** 左リールを止める */
	if (pad->IsTrigger(nsK2EngineLow::enButtonA))
	{
		StopReel(0);
	}

	/** 中リールで止める */
	if (pad->IsTrigger(nsK2EngineLow::enButtonB))
	{
		StopReel(1);
	}

	// Bボタン: 右リールを止める
	if (pad->IsTrigger(nsK2EngineLow::enButtonX))
	{
		StopReel(2);
	}

	// Startボタン: MAXBET
	if (pad->IsTrigger(nsK2EngineLow::enButtonStart))
	{
		// 全リールが停止している時だけBETできるようにする(回転中のBET変更を防ぐ)
		if (IsAllStopped())
		{
			
		}
	}
}

void MainReel::StartSpin()
{
	// 既にリールが回っている間は再スタートできないようにする
	if (!IsAllStopped()) return;

	for (int i = 0; i < m_reelNum; i++)
	{
		m_reelState[i] = ReelState::Spinning;
	}
}

void MainReel::StopReel(int index)
{
	if (index < 0 || index >= m_reelNum) return;

	// 回転中のリールしか止められない(既に止まっているリールへの誤操作を防ぐ)
	if (m_reelState[index] == ReelState::Spinning)
	{
		m_reelState[index] = ReelState::Stop;
	}
}

bool MainReel::IsAllStopped() const
{
	for (int i = 0; i < m_reelNum; i++)
	{
		if (m_reelState[i] == ReelState::Spinning) return false;
	}
	return true;
}

void MainReel::Render(RenderContext& rc)
{
	for (int i = 0; i < m_reelNum; i++)
	{
		
		m_mainReel[i][0].Draw(rc);
		m_mainReel[i][1].Draw(rc);
	}
}