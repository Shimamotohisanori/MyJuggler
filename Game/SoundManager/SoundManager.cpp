#include "stdafx.h"
#include "SoundManager.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include <iostream>

namespace {
	const char* SOUND_FILEPATH = "Assets/sound/";
	const char* SOUND_EXTENSION = ".wav";

	/** 操作サウンドのファイル名リスト */
	const char* operationSoundFileNameList[enOperationSound_Num] =
	{
		"ButtonStop",
		"LeverOn",
		"MaxBet"
	};

	/** 子役成立サウンドのファイル名リスト */
	const char* roleSoundFileNameList[enRoleSound_Num] =
	{
		"Pekari",
		"Budou",
		"Budou_2Bet",
		"Cherry",
		"Replay"
	};

	/** ボーナスサウンドのファイル名リスト */
	const char* bonusSoundFileNameList[enBonusSound_Num] =
	{
		"Bonus_Start",
		"Bonus_Main",
		"Bonus_End"
	};
}

SoundManager::SoundManager()
{
	/** 操作サウンドの登録（バンク番号: 0 ~ enOperationSound_Num-1） */
	for (int i = 0; i < enOperationSound_Num; i++)
	{
		std::string file = std::string(SOUND_FILEPATH) + operationSoundFileNameList[i] + SOUND_EXTENSION;
		const char* filepath = file.c_str();
		g_soundEngine->ResistWaveFileBank(i, filepath);
	}

	/** 子役成立サウンドの登録（オフセット: enOperationSound_Num ~） */
	for (int i = 0; i < enRoleSound_Num; i++)
	{
		std::string file = std::string(SOUND_FILEPATH) + roleSoundFileNameList[i] + SOUND_EXTENSION;
		const char* filepath = file.c_str();
		g_soundEngine->ResistWaveFileBank(enOperationSound_Num + i, filepath);
	}

	/** ボーナスサウンドの登録（オフセット: enOperationSound_Num + enRoleSound_Num ~） */
	for (int i = 0; i < enBonusSound_Num; i++)
	{
		std::string file = std::string(SOUND_FILEPATH) + bonusSoundFileNameList[i] + SOUND_EXTENSION;
		const char* filepath = file.c_str();
		g_soundEngine->ResistWaveFileBank(enOperationSound_Num + enRoleSound_Num + i, filepath);
	}
}

SoundSource* SoundManager::PlayingOperationSound(OperationSound number, bool isLoop, float volume)
{
	SoundSource* sound = NewGO<SoundSource>(0);
	sound->Init(number);
	sound->SetVolume(volume);
	sound->Play(isLoop);

	m_playingOperationSounds[number] = sound;

	return sound;
}

void SoundManager::StopOperationSound(OperationSound number)
{
	SoundSource* sound = m_playingOperationSounds[number];
	if (sound == nullptr) return;

	sound->Stop();
	DeleteGO(sound);
	m_playingOperationSounds[number] = nullptr;
}

SoundSource* SoundManager::PlayingRoleSound(RoleSound number, bool isLoop, float volume)
{
	SoundSource* sound = NewGO<SoundSource>(0);
	/** バンク番号はオフセットをかけた番号に合わせる */
	sound->Init(enOperationSound_Num + number);
	sound->SetVolume(volume);
	sound->Play(isLoop);

	m_playingRoleSounds[number] = sound;

	return sound;
}

void SoundManager::StopRoleSound(RoleSound number)
{
	SoundSource* sound = m_playingRoleSounds[number];
	if (sound == nullptr) return;

	sound->Stop();
	DeleteGO(sound);
	m_playingRoleSounds[number] = nullptr;
}

SoundSource* SoundManager::PlayingBonusSound(BonusSound number, bool isLoop, float volume)
{
	SoundSource* sound = NewGO<SoundSource>(0);
	/** バンク番号はオフセットをかけた番号に合わせる */
	sound->Init(enOperationSound_Num + enRoleSound_Num + number);
	sound->SetVolume(volume);
	sound->Play(isLoop);

	m_playingBonusSounds[number] = sound;

	return sound;
}

void SoundManager::StopBonusSound(BonusSound number)
{
	SoundSource* sound = m_playingBonusSounds[number];
	if (sound == nullptr) return;

	sound->Stop();
	DeleteGO(sound);
	m_playingBonusSounds[number] = nullptr;
}