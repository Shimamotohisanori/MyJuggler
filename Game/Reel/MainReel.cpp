#include "stdafx.h"
#include "MainReel.h"
#include "NumberUI/NumberUI.h"
#include "SoundManager/SoundManager.h"

namespace
{
	/** リールのファイルパス */
	const char* REEL_SPRITE_FILE_PATH[3] =
	{
		"Assets/sprites/Spritereel/Mr.LeftReel.dds",
		"Assets/sprites/Spritereel/Mr.CenterReel.dds",
		"Assets/sprites/Spritereel/Mr.RightReel.dds",
	};

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

	/** それぞれ三つのリールのX座標 */
	constexpr float REEL_POS_X[3] = { -380.0f,0.0f,380.0f };
	constexpr float REEL_POS_Z = 0.0f;

	/** ボタンを押す画像の大きさ */
	constexpr float PUSH_SPRITE_HEIGHT = 230.0f;
	constexpr float PUSH_SPRITE_WIDTH = 1720.0f;

	/** リールの大きさ */
	constexpr float REEL_WIDTH = 370.0f;
	constexpr float REEL_HEIGHT = 3000.0f;

	/** リールが動く速度 */
	static constexpr float REEL_SPEED = 55.0f;

	/** MAXBET設定するBET数 */
	static constexpr int MAX_BET = 3;

	constexpr uint8_t PUSH_NUM = 8;

	/** ボタンを押す画像の座標 */
	const Vector3 PUSH_SPRITE_POS = Vector3(0.0f, -430.0f, 0.0f);
}

bool MainReel::Start()
{
	m_soundManager = FindGO<SoundManager>("soundManager");

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

	for (int i = 0; i < PUSH_NUM; i++)
	{
		m_pushSpriteRender[i].Init(PUSU_SPRITE_FILE_PATH[i], PUSH_SPRITE_WIDTH, PUSH_SPRITE_HEIGHT);
		m_pushSpriteRender[i].SetPosition(PUSH_SPRITE_POS);
	}

	return true;
}

void MainReel::Update()
{
	if (m_numberUI == nullptr)
	{
		m_numberUI = FindGO<NumberUI>("numberUI");
	}

	// ボタン入力の判定
	UpdateInput();

	for (int i = 0; i < PUSH_NUM; i++)
	{
		m_pushSpriteRender[i].Update();
	}

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
		m_isLeftStop   = false;
		m_isCenterStop = false;
		m_isRightStop  = false;

		m_leverOnSound = m_soundManager->PlayingOperationSound(enOperationSound_LeverOn, false);
		StartSpin();
	}

	/** 左リールを止める */
	if (pad->IsTrigger(nsK2EngineLow::enButtonA))
	{
		m_isLeftStop = true;
		m_buttonStopSound = m_soundManager->PlayingOperationSound(enOperationSound_ButtonStop, false);
		StopReel(0);
	}

	/** 中リールで止める */
	if (pad->IsTrigger(nsK2EngineLow::enButtonB))
	{
		m_isCenterStop = true;
		m_buttonStopSound = m_soundManager->PlayingOperationSound(enOperationSound_ButtonStop, false);
		StopReel(1);
	}

	// Bボタン: 右リールを止める
	if (pad->IsTrigger(nsK2EngineLow::enButtonX))
	{
		m_isRightStop = true;
		m_buttonStopSound = m_soundManager->PlayingOperationSound(enOperationSound_ButtonStop, false);
		StopReel(2);
	}

	// Startボタン: MAXBET
	if (pad->IsTrigger(nsK2EngineLow::enButtonStart))
	{
		// 全リールが停止している時だけBETできるようにする(回転中のBET変更を防ぐ)
		if (IsAllStopped())
		{
			/** MAXBET時は3枚使う */
			m_numberUI->AddCredit(-3);

			/** MAXBET時の音を再生 */
			m_maxBetSound = m_soundManager->PlayingOperationSound(enOperationSound_MaxBet, false);
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

int MainReel::GetPushSpriteIndex() const
{
	/*
	 * ボタンを押された数
	 * bool型から押された数を数えている
	 */
	uint8_t stoppedCount = static_cast<uint8_t>(m_isLeftStop) + static_cast<uint8_t>(m_isCenterStop) + static_cast<uint8_t>(m_isRightStop);

	/** 何も押されていない状態 */
	if (stoppedCount == 0)
	{
		return 5;
	}

	/** 全て押されている状態 */
	if (stoppedCount == 3)
	{
		return 0;
	}

	/** 三つのボタンのうち一つのボタンを押した場合 */
	if (stoppedCount == 1)
	{
		/** 左のボタンを押した */
		if (m_isLeftStop) return 4;

		/** 中のボタンを押した */
		if (m_isCenterStop) return 2;
		
		/** 右のボタンを押した */
		return 7;
	}

	if (stoppedCount == 2)
	{
		if (!m_isLeftStop) return 3;
		if (!m_isCenterStop) return 1;
		return 6;
	}

}

void MainReel::Render(RenderContext& rc)
{
	for (int i = 0; i < m_reelNum; i++)
	{
		m_mainReel[i][0].Draw(rc);
		m_mainReel[i][1].Draw(rc);
	}

	/** int型の関数で返された値を描画する */
	m_pushSpriteRender[GetPushSpriteIndex()].Draw(rc);
}