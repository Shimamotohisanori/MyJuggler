#pragma once
#include "RoleProbabilityDefine/RoleProbabilityDefine.h"

/** GOGOランプの色（設定示唆） */
enum class GogoLampType
{
	Normal,  /** 通常色（一番出やすい） */
	Green,   /** 緑（やや低確率） */
	Rainbow, /** 虹色（かなり低確率） */
};

/** ゲーム画面クラス */
class MainScene : public IGameObject
{
public:
	MainScene();
	~MainScene();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

	///<summary>
	///現在の抽選結果を設定します。BIGが確定した場合、内部でGOGOランプの色も同時に抽選されます。
	///</summary>
	void SetCurrentRole(Role role);

private:
	///<summary>
	///GOGOランプの色を抽選します（BIG確定時に1回だけ呼ばれる想定）。
	///</summary>
	GogoLampType DecideGogoLampType();

	/** メイン画面の画像 */
	SpriteRender m_mainSpriteRender;

	/** プッシュボタンの画像 */
	SpriteRender m_pushSpriteRender[8];

	/** GOGOランプ（通常色）の画像 */
	SpriteRender m_gogoSpriteRender;

	/** GOGOランプ（緑）の画像 */
	SpriteRender m_greenGogoSpriteRender;

	/** GOGOランプ（虹色）の画像 */
	SpriteRender m_rainbowGogoSpriteRender;

	/** 現在の抽選結果 */
	Role m_currentRole = enRole_Hazure;

	/** 現在表示すべきGOGOランプの色 */
	GogoLampType m_currentGogoLampType = GogoLampType::Normal;
};