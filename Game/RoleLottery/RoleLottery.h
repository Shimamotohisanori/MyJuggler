#pragma once
#include "RoleProbabilityDefine/RoleProbabilityDefine.h"

class RoleLottery
{
public:
	///<summary>
	///役の抽選を行います
	///</summary>
	/// <returns>抽選された役</returns>
	static Role Draw();

private:
	///<summary>
	///0~(maxExclusive - 1)の乱数を一つ生成します。
	///</summary>
	static int GetRandomValue(int maxExclusive);

	///<summary>
	///0～99の乱数を一つ生成します（%判定用）。
	///</summary>
	static int GetRandomPercent();

	///<summary>
	///ハズレを引いた場合の追加抽選（チャンス目/BIG/REG/純粋なハズレを決める）。
	///</summary>
	static Role DrawFromHazure();

	///<summary>
	///チェリー・ピエロを引いた場合の重複判定抽選を行う共通処理。
	///</summary>
	/// <param name="bonusCheckRatePercent">重複判定を行う確率（%）。</param>
	/// <param name="bigRatePercent">重複当選時、BIGになる確率（%）。残りはREG。</param>
	/// <param name="baseRole">重複しなかった場合に返す役（Cherry or Pierrot）。</param>
	static Role DrawBonusOverlap(int bonusCheckRatePercent, int bigRatePercent, Role baseRole);
};