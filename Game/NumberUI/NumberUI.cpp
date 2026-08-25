#include "stdafx.h"
#include "NumberUI.h"

namespace
{
	const char* NUMBER_IMAGE_FILEPATH = "Assets/sprites/Numbers/";
	const char* NUMBER_IMAGE_EXTENSION = ".dds";

	const float NUMBER_IMAGE_WIDTH = 32.0f;
	const float NUMBER_IMAGE_HEIGHT = 48.0f;

	/** 各表示の基準座標（デザインに合わせて調整してください） */
	const Vector3 CREDIT_BASE_POSITION = Vector3(-235.0f, -200.0f, 0.0f);
	const Vector3 COUNT_BASE_POSITION = Vector3(-40.0f, -200.0f, 0.0f);
	const Vector3 PAYOUT_BASE_POSITION = Vector3(200.0f, -200.0f, 0.0f);

	const int CREDIT_MAX = 50;
	const int COUNT_MAX = 280;
	const int PAYOUT_MAX = 99;

	/** カウンターアニメーションの速さ（何フレームに1回、表示値を1動かすか） */
	const int COUNT_ANIMATION_INCREASE_FRAME_INTERVAL = 7; /** 増加時（ゆっくり） */
	const int COUNT_ANIMATION_DECREASE_FRAME_INTERVAL = 2; /** 減少時（速い） */
}

NumberUI::NumberUI()
{}

NumberUI::~NumberUI()
{}

bool NumberUI::Start()
{
	InitDigitSlots(&m_creditNumberSpriteRenders[0][0], CREDIT_DIGIT_NUM, CREDIT_BASE_POSITION, NUMBER_IMAGE_WIDTH, NUMBER_IMAGE_FILEPATH, NUMBER_IMAGE_EXTENSION);
	InitDigitSlots(&m_countNumberSpriteRenders[0][0], COUNT_DIGIT_NUM, COUNT_BASE_POSITION, NUMBER_IMAGE_WIDTH, NUMBER_IMAGE_FILEPATH, NUMBER_IMAGE_EXTENSION);
	InitDigitSlots(&m_payoutNumberSpriteRenders[0][0], PAYOUT_DIGIT_NUM, PAYOUT_BASE_POSITION, NUMBER_IMAGE_WIDTH, NUMBER_IMAGE_FILEPATH, NUMBER_IMAGE_EXTENSION);

	return true;
}

void NumberUI::InitDigitSlots(SpriteRender* digitSlotArray, int digitNum, const Vector3& basePosition, float digitWidth, const char* filepathBase, const char* extension)
{
	for (int slot = 0; slot < digitNum; slot++)
	{
		/** この桁の位置は固定なので、Startで一度だけ計算してSetPositionしておく */
		Vector3 position = basePosition;
		position.x += digitWidth * slot;

		for (int d = 0; d < 10; d++)
		{
			std::string file = std::string(filepathBase) + std::to_string(d) + extension;
			const char* filepath = file.c_str();

			SpriteRender& sprite = digitSlotArray[slot * 10 + d];
			sprite.Init(filepath, NUMBER_IMAGE_WIDTH, NUMBER_IMAGE_HEIGHT);
			sprite.SetPosition(position); /** 桁の位置は変わらないのでここで固定してしまう */
		}
	}
}

void NumberUI::Update()
{
	UpdateCounterAnimation(m_creditDisplay, m_creditTarget, m_creditAnimFrameCounter,
		COUNT_ANIMATION_INCREASE_FRAME_INTERVAL, COUNT_ANIMATION_DECREASE_FRAME_INTERVAL);
	UpdateCounterAnimation(m_countDisplay, m_countTarget, m_countAnimFrameCounter,
		COUNT_ANIMATION_INCREASE_FRAME_INTERVAL, COUNT_ANIMATION_DECREASE_FRAME_INTERVAL);
	UpdateCounterAnimation(m_payoutDisplay, m_payoutTarget, m_payoutAnimFrameCounter,
		COUNT_ANIMATION_INCREASE_FRAME_INTERVAL, COUNT_ANIMATION_DECREASE_FRAME_INTERVAL);

	/** 各スプライトの内部アニメーション更新のみ行う（位置は変えない） */
	for (int slot = 0; slot < CREDIT_DIGIT_NUM; slot++)
		for (int d = 0; d < 10; d++)
			m_creditNumberSpriteRenders[slot][d].Update();

	for (int slot = 0; slot < COUNT_DIGIT_NUM; slot++)
		for (int d = 0; d < 10; d++)
			m_countNumberSpriteRenders[slot][d].Update();

	for (int slot = 0; slot < PAYOUT_DIGIT_NUM; slot++)
		for (int d = 0; d < 10; d++)
			m_payoutNumberSpriteRenders[slot][d].Update();
}

void NumberUI::Render(RenderContext& rc)
{
	RenderNumber(rc, &m_creditNumberSpriteRenders[0][0], CREDIT_DIGIT_NUM, m_creditDisplay);
	RenderNumber(rc, &m_countNumberSpriteRenders[0][0], COUNT_DIGIT_NUM, m_countDisplay);
	RenderNumber(rc, &m_payoutNumberSpriteRenders[0][0], PAYOUT_DIGIT_NUM, m_payoutDisplay);
}

void NumberUI::SetCredit(int credit)
{
	m_creditTarget = ClampValue(credit, 0, CREDIT_MAX);
}

void NumberUI::SetCount(int count)
{
	m_countTarget = ClampValue(count, 0, COUNT_MAX);
}

void NumberUI::SetPayout(int payout)
{
	m_payoutTarget = ClampValue(payout, 0, PAYOUT_MAX);
}

int NumberUI::ClampValue(int value, int min, int max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

void NumberUI::UpdateCounterAnimation(int& display, int target, int& frameCounter, int increaseInterval, int decreaseInterval)
{
	if (display == target) return;

	frameCounter++;

	/** 増加か減少かで待つフレーム数を切り替える */
	bool isIncreasing = (display < target);
	int interval = isIncreasing ? increaseInterval : decreaseInterval;

	if (frameCounter >= interval)
	{
		frameCounter = 0;

		if (isIncreasing) display++;
		else display--;
	}
}

void NumberUI::RenderNumber(RenderContext& rc, SpriteRender* digitSlotArray, int digitNum, int value)
{
	for (int slot = 0; slot < digitNum; slot++)
	{
		int placeValue = 1;
		for (int j = 0; j < (digitNum - 1 - slot); j++)
		{
			placeValue *= 10;
		}

		int digit = (value / placeValue) % 10;

		/** この桁専用のオブジェクトを使うので、他の桁と取り合うことがない */
		SpriteRender& sprite = digitSlotArray[slot * 10 + digit];
		sprite.Draw(rc);
	}
}