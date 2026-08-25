#pragma once

/** 抽選の分母 */
constexpr int LOTTERY_TOTAL = 65536;

/** 成立する役の種類（最終的にDraw()が返す値） */
enum Role
{
	enRole_Hazure,  /** ハズレ */
	enRole_Bell,    /** ベル */
	enRole_Pierrot, /** ピエロ */
	enRole_Replay,  /** リプレイ */
	enRole_Budou,   /** ブドウ */
	enRole_Cherry,  /** チェリー */
	enRole_Chance,  /** チャンス目 */
	enRole_BIG,     /** BIG */
	enRole_REG,     /** REG */
	enRole_Num      /** 役の種類の総数 */
};

namespace
{
	/** ==== 1段階目：メイン抽選（65536分の数値） ====
	 * ベル・ピエロ・リプレイ・ブドウ・チェリーの5つだけを直接抽選する。
	 * 残り（ハズレ分）は、この5つの合計をLOTTERY_TOTALから引いた値になる。 */
	const int g_bellProbability = 60;
	const int g_pierrotProbability = 60;
	const int g_replayProbability = 8978;
	const int g_budouProbability = 11497;
	const int g_cherryProbability = 1867;

	/** ハズレ枠の抽選値（チャンス目・BIG・REGの分も含んだ拡張ハズレ）
	 * = LOTTERY_TOTAL - (ベル+ピエロ+リプレイ+ブドウ+チェリー) */
	const int g_hazureExtendedProbability =
		LOTTERY_TOTAL - (g_bellProbability + g_pierrotProbability + g_replayProbability + g_budouProbability + g_cherryProbability);

	/** ==== 2段階目-A：ハズレの中でのさらなる抽選（g_hazureExtendedProbability分の数値） ====
	 * ここでチャンス目・BIG・REG・純粋なハズレのどれかが決まる。 */
	const int g_chanceProbabilityInHazure = 218;
	const int g_bigProbabilityInHazure = 175;
	const int g_regProbabilityInHazure = 384;
	/** 残りは純粋なハズレとして扱う（コード側で自動計算） */

	/** ==== 2段階目-B：チェリーを引いた後の重複判定 ====
	 * チェリーを引いたうちの何%で、さらにBIG/REGの重複判定を行うか */
	const int g_cherryBonusCheckRatePercent = 10;
	/** 重複判定に当選した場合、そのうち何%をBIGにするか（残りはREG） */
	const int g_cherryBonusBigRatePercent = 70;

	/** ==== 2段階目-C：ピエロを引いた後の重複判定 ==== */
	const int g_pierrotBonusCheckRatePercent = 20;
	const int g_pierrotBonusBigRatePercent = 50;
}