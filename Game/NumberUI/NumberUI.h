#pragma once

/** ゲーム中に使用される数字のUI */
class NumberUI : public IGameObject
{
public:
	/** 各表示の桁数（配列サイズにも使うため公開） */
	static const int CREDIT_DIGIT_NUM = 2;
	static const int COUNT_DIGIT_NUM = 3;
	static const int PAYOUT_DIGIT_NUM = 2;

	NumberUI();
	~NumberUI();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	///<summary>
	///現在のクレジット数（目標値）を設定します。
	///<summary>
	void SetCredit(int credit);

	///<summary>
	///現在のカウント数（目標値）を設定します。
	///<summary>
	void SetCount(int count);

	/// <summary>
	/// 現在の払い出し枚数（目標値）を設定します。
	/// <summary>
	void SetPayout(int payout);

	///<summary>
	///現在のクレジット数（目標値）を取得します。
	///</summary>
	int GetCredit() const { return m_creditTarget; }

	///<summary>
	///現在のカウント数（目標値）を取得します。
	///</summary>
	int GetCount() const { return m_countTarget; }

	///<summary>
	///現在の払い出し枚数（目標値）を取得します。
	///</summary>
	int GetPayout() const { return m_payoutTarget; }

	///<summary>
	///カウント数を相対的に増減させます。
	///</summary>
	void AddCount(int delta) { SetCount(m_countTarget + delta); }

	///<summary>
    ///役が成立してメダルを獲得した際の処理です。
    ///獲得枚数をそのままPayOutに表示しつつ、クレジットにも加算します（上限50でクランプ）。
    ///</summary>
    /// <param name="amount">獲得したメダル枚数（例：ブドウなら8）。</param>
	void OnMedalWon(int amount);

	///<summary>
    ///クレジットを相対的に増減させます（ベット時の減算などに使用）。
    ///</summary>
    /// <param name="delta">増減量。マイナスを渡せば減算になります。</param>
	void AddCredit(int delta) { SetCredit(m_creditTarget + delta); }

private:
	int ClampValue(int value, int min, int max);
	///<summary>
	///表示値（display）を目標値（target）に、1フレームずつ近づけるカウンターアニメーション処理。
	///</summary>
	/// <param name="display">現在の表示値。1ずつtargetに近づきます。</param>
	/// <param name="target">最終的に表示したい目標値。</param>
	/// <param name="frameCounter">アニメーション速度を管理するための内部カウンター。</param>
	/// <param name="increaseInterval">増加時、何フレームに1回1ずつ増やすか。</param>
	/// <param name="decreaseInterval">減少時、何フレームに1回1ずつ減らすか。</param>
	void UpdateCounterAnimation(int& display, int target, int& frameCounter, int increaseInterval, int decreaseInterval);

	///<summary>
	///指定した「桁×10種類」のスプライト配列を使って、数値を描画する共通処理。
	///</summary>
	/// <param name="digitSlotArray">[桁数 × 10]で確保されたスプライト配列の先頭ポインタ。</param>
	/// <param name="digitNum">桁数。</param>
	/// <param name="value">描画したい数値。</param>
	void RenderNumber(RenderContext& rc, SpriteRender* digitSlotArray, int digitNum, int value);

	///<summary>
	///各桁の初期化（テクスチャ読み込みと位置の固定）を行う共通処理。
	///</summary>
	void InitDigitSlots(SpriteRender* digitSlotArray, int digitNum, const Vector3& basePosition, float digitWidth, const char* filepathBase, const char* extension);

	/** クレジット用：[桁(2)][絵柄0～9] */
	SpriteRender m_creditNumberSpriteRenders[CREDIT_DIGIT_NUM][10];

	/** カウント用：[桁(3)][絵柄0～9] */
	SpriteRender m_countNumberSpriteRenders[COUNT_DIGIT_NUM][10];

	/** 払い出し用：[桁(2)][絵柄0～9] */
	SpriteRender m_payoutNumberSpriteRenders[PAYOUT_DIGIT_NUM][10];

	int m_creditTarget = 0;
	int m_creditDisplay = 0;
	int m_creditAnimFrameCounter = 0;

	int m_countTarget = 0;
	int m_countDisplay = 0;
	int m_countAnimFrameCounter = 0;

	int m_payoutTarget = 0;
	int m_payoutDisplay = 0;
	int m_payoutAnimFrameCounter = 0;
};