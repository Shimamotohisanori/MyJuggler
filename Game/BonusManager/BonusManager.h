#pragma once

/** 現在のボーナス状態 */
enum BonusType
{
	enBonusType_None, /** ボーナス中ではない（通常時） */
	enBonusType_BIG,  /** BIG中 */
	enBonusType_REG,  /** REG中 */
};

///<summary>
///BIG・REG中の状態（ボーナス中かどうか、獲得カウントの管理）を扱うクラス。
///</summary>
class BonusManager : public IGameObject
{
public:
	///<summary>
	///ボーナスを開始します。通常抽選でBIG/REGが確定したタイミングで呼び出してください。
	///</summary>
	/// <param name="bonusType">開始するボーナスの種類（BIG or REG）。</param>
	static void StartBonus(BonusType bonusType);

	///<summary>
	///現在ボーナス中かどうかを取得します。
	///</summary>
	static bool IsInBonus();

	///<summary>
	///現在のボーナス種別を取得します。ボーナス中でない場合はenBonusType_Noneが返ります。
	///</summary>
	static BonusType GetCurrentBonusType();

	///<summary>
	///ボーナス中の獲得カウントを加算します。
	///規定数に到達した場合、自動的にボーナスを終了し、通常時に戻ります。
	///</summary>
	/// <param name="count">加算する獲得枚数（カウント）。</param>
	static void AddCount(int count);

	///<summary>
	///現在のボーナス中の獲得カウントを取得します（NumberUIのカウント表示に使用）。
	///</summary>
	static int GetCurrentCount();

private:
	/** 現在のボーナス種別 */
	static BonusType m_currentBonusType;

	/** ボーナス中の獲得カウント */
	static int m_currentCount;

	///<summary>
	///指定したボーナス種別の、終了に必要なカウント数を取得します。
	///</summary>
	static int GetCountTarget(BonusType bonusType);
};