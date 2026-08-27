#include "stdafx.h"
#include "BonusManager.h"

namespace
{
	/** BIG終了に必要な獲得カウント（実機のBIG最大枚数を参考に設定） */
	const int BIG_COUNT_TARGET = 280;

	/** REG終了に必要な獲得カウント（実機のREG最大枚数を参考に設定） */
	const int REG_COUNT_TARGET = 96;
}

BonusType BonusManager::m_currentBonusType = enBonusType_None;
int BonusManager::m_currentCount = 0;

void BonusManager::StartBonus(BonusType bonusType)
{
	m_currentBonusType = bonusType;
	m_currentCount = 0;
}

bool BonusManager::IsInBonus()
{
	return m_currentBonusType != enBonusType_None;
}

BonusType BonusManager::GetCurrentBonusType()
{
	return m_currentBonusType;
}

void BonusManager::AddCount(int count)
{
	if (!IsInBonus())
	{
		/** ボーナス中でないのに呼ばれた場合は何もしない（呼び出しミス対策） */
		return;
	}

	m_currentCount += count;

	if (m_currentCount >= GetCountTarget(m_currentBonusType))
	{
		/** 規定カウントに到達したのでボーナス終了、通常時に戻る */
		m_currentBonusType = enBonusType_None;
		m_currentCount = 0;
	}
}

int BonusManager::GetCurrentCount()
{
	return m_currentCount;
}

int BonusManager::GetCountTarget(BonusType bonusType)
{
	switch (bonusType)
	{
	case enBonusType_BIG: return BIG_COUNT_TARGET;
	case enBonusType_REG: return REG_COUNT_TARGET;
	default: return 0;
	}
}