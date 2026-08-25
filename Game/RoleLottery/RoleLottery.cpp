#include "stdafx.h"
#include "RoleLottery.h"
#include <random>

namespace
{
	/** 乱数エンジンは使いまわすので、静的に一つだけ保持する */
	std::mt19937 g_mt(std::random_device{}());
}

Role RoleLottery::Draw()
{
	/** ==== 1段階目：メイン抽選 ==== */
	int random = GetRandomValue(LOTTERY_TOTAL);

	int sum = 0;

	sum += g_bellProbability;
	if (random < sum) return enRole_Bell; /** ベルは追加抽選なし、確定 */

	sum += g_pierrotProbability;
	if (random < sum) return DrawBonusOverlap(g_pierrotBonusCheckRatePercent, g_pierrotBonusBigRatePercent, enRole_Pierrot);

	sum += g_replayProbability;
	if (random < sum) return enRole_Replay; /** リプレイは追加抽選なし、確定 */

	sum += g_budouProbability;
	if (random < sum) return enRole_Budou; /** ブドウは追加抽選なし、確定 */

	sum += g_cherryProbability;
	if (random < sum) return DrawBonusOverlap(g_cherryBonusCheckRatePercent, g_cherryBonusBigRatePercent, enRole_Cherry);

	/** ここまでのどれにも当たらなければハズレ。ハズレの中でさらに抽選する。 */
	return DrawFromHazure();
}

Role RoleLottery::DrawFromHazure()
{
	/** ハズレ枠(g_hazureExtendedProbability)の中で、チャンス目/BIG/REG/純粋なハズレを決める */
	int random = GetRandomValue(g_hazureExtendedProbability);

	int sum = 0;

	sum += g_chanceProbabilityInHazure;
	if (random < sum) return enRole_Chance;

	sum += g_bigProbabilityInHazure;
	if (random < sum) return enRole_BIG;

	sum += g_regProbabilityInHazure;
	if (random < sum) return enRole_REG;

	/** どれにも当たらなければ純粋なハズレ */
	return enRole_Hazure;
}

Role RoleLottery::DrawBonusOverlap(int bonusCheckRatePercent, int bigRatePercent, Role baseRole)
{
	/** 重複判定（例：チェリーの場合10%でここに入る） */
	int checkRandom = GetRandomPercent();
	if (checkRandom >= bonusCheckRatePercent)
	{
		/** 重複しなかった場合は、そのままの役として確定 */
		return baseRole;
	}

	/** 重複当選した場合、さらにBIGかREGかを判定する */
	int bigOrRegRandom = GetRandomPercent();
	if (bigOrRegRandom < bigRatePercent)
	{
		return enRole_BIG;
	}
	else
	{
		return enRole_REG;
	}
}

int RoleLottery::GetRandomValue(int maxExclusive)
{
	/** 0～(maxExclusive - 1)の乱数を生成する */
	std::uniform_int_distribution<int> dist(0, maxExclusive - 1);
	return dist(g_mt);
}

int RoleLottery::GetRandomPercent()
{
	/** 0～99の乱数を生成する */
	std::uniform_int_distribution<int> dist(0, 99);
	return dist(g_mt);
}