#pragma once
#include <map>
#include <list>
#include <string>
#include <memory>

// KdGameLibのクラス前方宣言
class KdSoundEffect;
class KdSoundInstance;

namespace SoundName
{
	constexpr char kTitle[] = "title";
	constexpr char kGame[] = "game";
	constexpr char kLastboss[] = "lastboss";
	constexpr char kResult[] = "result";
	constexpr char kNShot[] = "normalshot";
	constexpr char kCrowShot[] = "crowshot";
	constexpr char kEnemyShot[] = "enemyshot";
	constexpr char kWayShot[] = "Wayshot";
	constexpr char kLighting[] = "lighting";
	constexpr char kHit[] = "hit";
	constexpr char kEnemyDestroy[] = "enemyDestroy";
	constexpr char kEnemyHit[] = "enemyhit";
	constexpr char kMenuPush[] = "menuPush";
	constexpr char kResultPush[] = "resultPush";
	constexpr char kHeartbeat[] = "heartbeat";
	constexpr char kChain[] = "chain";
	constexpr char kRing[] = "ring";
	constexpr char kFlapWings[] = "flapwings";
	constexpr char kRavenTakeoff[] = "raventakeoff";
	constexpr char kError[] = "error";
	constexpr char kMpMax[] = "mpmax";
}

class AudioManager
{
public:
	// シングルトンパターン
	static AudioManager& Instance()
	{
		static AudioManager instance;
		return instance;
	}

	// 初期化
	void Init();

	// 更新
	void Update();

	void UpdateFade();

	// BGM再生
	void PlayBgm(const std::string& resName, bool loop = true);

	// BGM停止
	void StopBgm();

	// SE再生
	void PlaySe(const std::string& resName, bool loop = false);

	// SE停止
	void StopSe(const std::string& name);

	// 同時再生時減衰用Se再生
	void PlaySeNumLimit(const std::string& resName, bool loop = false);

	// Bgmのフェードイン
	void FadeInBgm(const std::string& resName, float fadeTime, bool loop = false);

	// Bgmのフェードアウト
	void FadeOutBgm(float fadeTime);

	void FadeOutAndPlayNext(const std::string& nextBgm, float fadeOutTime, float fadeInTime, bool loop);

	void PauseBGM();
	void ResumeBGM();

	// 解放
	void Release();

	void SetBgmVolume(float vol);
	void SetSeVolume(float vol);
	float GetBgmVolume() const { return m_bgmVol; }
	float GetSeVolume() const { return m_seVol; }

private:

	AudioManager();
	~AudioManager() { Release(); }

	// サウンドデータ管理
	std::map<std::string, std::shared_ptr<KdSoundEffect>> m_soundMap;

	// 現在再生中のBGM
	std::shared_ptr<KdSoundInstance> m_bgmInst;

	// 再生中のSEリスト 
	struct PlayingSe
	{
		std::string name;
		std::shared_ptr<KdSoundInstance> instance;
		float volumeRate = 1.0f;
	};

	std::list<PlayingSe> m_seList;

	std::unordered_map<std::string, int> m_seFrameCount; // 今フレームの再生回数

	// 音量設定
	float m_bgmVol = 0.3f;
	float m_seVol = 0.2f;

	struct FadeParam
	{
		bool active = false;
		bool fadeIn = false;
		std::string type;
		float currentVol = 0.0f;
		float targetVol = 0.0f;
		float speed = 0.0f;

		bool end = false;
	};

	FadeParam m_bgmFade = {};
	std::string m_nextBgm = {};
	bool m_requestNextBgm = false;
	float m_fadeInTime = 0.0f;
	bool m_nextBgmLoop = false;
	Math::Vector2 m_listenerPos{};

	void LoadSound(const std::string& name, const std::string& path);
};

#define AUDIOM AudioManager::Instance()