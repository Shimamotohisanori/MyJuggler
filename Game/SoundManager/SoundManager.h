#pragma once
#include "sound/SoundSource.h"

/** ファイルパスを追加する際は、
 * cppのnamespaceと下記のenumを使用してください */
enum OperationSound {
	enOperationSound_ButtonStop, /** ボタン押下音 */
	enOperationSound_LeverOn, /** レバーオン音 */
	enOperationSound_MaxBet, /** 最大ベット音 */
	enOperationSound_Num  /** このステータスは、サウンドの総数を表しているため、この下には追加しないでください */
};

enum RoleSound
{
	enRoleSound_Pekari, /** ペカリ音 */
	enRoleSound_Budou, /** ブドウ成立音 */
	enRoleSound_Budou_2Bet, /** ブドウ成立音（2BET時） */
	enRoleSound_Cherry, /** チェリー成立音 */
	enRoleSound_Replay, /** リプレイ成立音 */
	enRoleSound_Num  /** このステータスは、サウンドの総数を表しているため、この下には追加しないでください */
};

enum BonusSound
{
	enBonusSound_Bonus_Start, /** ボーナス開始音 */
	enBonusSound_Bonus_Main, /** ボーナスメイン音 */
	enBonusSound_Bonus_End, /** ボーナス終了音 */
	enBonusSound_Num  /** このステータスは、サウンドの総数を表しているため、この下には追加しないでください */
};

class SoundManager : public IGameObject
{
public:
	SoundManager();
	~SoundManager() {};

	///<summary>
	///指定した操作サウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	SoundSource* PlayingOperationSound(OperationSound number, bool isLoop = true, float volume = 1.0f);

	///<summary>
	///指定した操作サウンドを停止します。
	/// </summary>
	void StopOperationSound(OperationSound number);

	///<summary>
	///指定した子役成立サウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	SoundSource* PlayingRoleSound(RoleSound number, bool isLoop = true, float volume = 1.0f);

	///<summary>
	///指定した子役成立サウンドを停止します。
	/// </summary>
	void StopRoleSound(RoleSound number);

	///<summary>
	///指定したボーナスサウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	SoundSource* PlayingBonusSound(BonusSound number, bool isLoop = true, float volume = 1.0f);

	///<summary>
	///指定したボーナスサウンドを停止します。
	/// </summary>
	void StopBonusSound(BonusSound number);

private:
	/** 現在再生中のSoundSourceを、OperationSound種別ごとに保持する */
	SoundSource* m_playingOperationSounds[enOperationSound_Num] = { nullptr };

	/** 現在再生中のSoundSourceを、RoleSound種別ごとに保持する */
	SoundSource* m_playingRoleSounds[enRoleSound_Num] = { nullptr };

	/** 現在再生中のSoundSourceを、BonusSound種別ごとに保持する */
	SoundSource* m_playingBonusSounds[enBonusSound_Num] = { nullptr };
};