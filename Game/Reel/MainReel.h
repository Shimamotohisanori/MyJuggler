#pragma once
class MainReel : public IGameObject
{
public:
	enum class ReelState
	{
		Stop,    //停止中
		Spinning,//回転中
	};

	MainReel(){}
	~MainReel(){}

	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/** ボタン入力の処理をまとめる */
	void UpdateInput();

	/** 全リールの回転を開始する */
	void StartSpin();

	/** 指定したリールを止める(既に停止済みなら何もしない) */
	void StopReel(int index);

	/** 全リールが停止しているか */
	bool IsAllStopped() const;

	/** 現在の状態から表示すべきボタンの画像のインデックスを求める */
	int GetPushSpriteIndex() const;
private:
	/** リール配列の数 */
	uint8_t m_reelNum = 3;

	uint8_t m_ButtonPushNum = 0;

	/** 左のリールが停止しているかどうか */
	bool m_isLeftStop = false;

	/** 中リールが停止しているかどうか */
	bool m_isCenterStop = false;

	/** 右リールが停止しているかどうか */
	bool m_isRightStop = false;

private:
	/**
	 * リールの画像。
	 * 1つのリールにつき「同じ画像を2枚」用意する。
	 * [i][0] = 基準となる1枚目
	 * [i][1] = 1枚目の真上(REEL_HEIGHT分)に配置する2枚目
	 * この2枚を常にセットで動かし続けることで、
	 * 「1枚が画面下に消え切る瞬間には、もう1枚がちょうど上から入ってくる」
	 * という玉突き状態を作り、リールが途切れず流れ続けているように見せる。
	 */
	SpriteRender m_mainReel[3][2];

	/** ボタンを押す画像 */
	SpriteRender m_pushSpriteRender[8];

	/** 各リールのY座標のオフセット(スクロール量) */
	float m_scrollY[3] = { 0.0f, 0.0f, 0.0f };

	/** 各リールが回転中かどうか */
	ReelState m_reelState[3] = { ReelState::Stop, ReelState::Stop, ReelState::Stop };

};

