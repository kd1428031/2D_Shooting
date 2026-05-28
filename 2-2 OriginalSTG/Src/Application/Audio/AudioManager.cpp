#include "AudioManager.h"

AudioManager::AudioManager()
{
}

void AudioManager::LoadSound(const std::string& name, const std::string& path)
{
	// まだロードされていない場合のみロード
	if (m_soundMap.find(name) == m_soundMap.end())
	{
		auto sound = std::make_shared<KdSoundEffect>();
		if (sound->Load(path))
		{
			m_soundMap[name] = sound;
		}
	}
}

void AudioManager::Init()
{
	LoadSound(SoundName::kTitle,"Sound/PerituneMaterial_Entangle.wav");
	LoadSound(SoundName::kGame,"Sound/Traume.wav");
	LoadSound(SoundName::kLastboss,"Sound/Battle02.wav");
	LoadSound(SoundName::kResult,"Sound/淀み.wav");
	LoadSound(SoundName::kNShot,"Sound/ショット1.wav");
	LoadSound(SoundName::kCrowShot,"Sound/ショット1_B_minor__bpm_100.wav");
	LoadSound(SoundName::kEnemyShot,"Sound/ショット.wav");
	LoadSound(SoundName::kWayShot,"Sound/ショット.wav");
	LoadSound(SoundName::kLighting,"Sound/雷魔法4.wav");
	LoadSound(SoundName::kHit,"Sound/軽いパンチ1.wav");
	LoadSound(SoundName::kEnemyDestroy,"Sound/386862__profmudkip__8-bit-explosion.wav");
	LoadSound(SoundName::kEnemyHit,"Sound/hit.wav");
	LoadSound(SoundName::kMenuPush,"Sound/decide3.wav");
	LoadSound(SoundName::kResultPush,"Sound/decide9.wav");
	LoadSound(SoundName::kHeartbeat,"Sound/maou_se_sound_heartbeat01.wav");
	LoadSound(SoundName::kChain,"Sound/チェーン・鎖03.wav");
	LoadSound(SoundName::kRing,"Sound/715784__dustywind__magic-whoosh.wav");
	LoadSound(SoundName::kFlapWings,"Sound/389634__stubb__wing-flap-1.wav");
	LoadSound(SoundName::kRavenTakeoff,"Sound/389634__stubb__wing-flap-1_hard.wav");
	LoadSound(SoundName::kError,"Sound/ビープ音4.wav");
	LoadSound(SoundName::kMpMax,"Sound/回復魔法1.wav");
}	

void AudioManager::Update()
{
	m_seFrameCount.clear();
	m_seList.remove_if([](PlayingSe& se) {
		return se.instance->IsPlay() == false;
		});
}

void AudioManager::UpdateFade()
{
	// フェード中か確認
	if (m_bgmFade.active)
	{
		if (m_bgmFade.fadeIn)
		{
			// フェードイン処理
			m_bgmFade.currentVol += m_bgmFade.speed;

			// フェードイン終了判定
			if (m_bgmFade.currentVol >= m_bgmFade.targetVol)
			{
				m_bgmFade.currentVol = m_bgmFade.targetVol;
				m_bgmFade.active = false;
				m_bgmFade.end = true;
			}
		}
		else
		{
			// フェードアウト処理
			m_bgmFade.currentVol -= m_bgmFade.speed;

			// フェードアウト終了判定
			if (m_bgmFade.currentVol <= m_bgmFade.targetVol)
			{
				m_bgmFade.currentVol = m_bgmFade.targetVol;
				m_bgmFade.active = false;
				m_bgmFade.end = true;

				// 完了したら停止
				StopBgm();
			}
		}

		if (m_bgmInst)
		{
			// 実際の音量に反映
			m_bgmInst->SetVolume(m_bgmFade.currentVol);
		}
	}

	if (m_bgmFade.end)
	{
		if (m_requestNextBgm)
		{
			FadeInBgm(m_nextBgm, m_fadeInTime, m_nextBgmLoop);
			m_requestNextBgm = false;
		}
		m_bgmFade.end = false;
	}
}

void AudioManager::PlayBgm(const std::string& resName, bool loop)
{
	// 既に何か再生中なら止める
	StopBgm();

	// マップからデータを探す
	if (m_soundMap.find(resName) != m_soundMap.end())
	{
		// 再生用インスタンス生成
		m_bgmInst = m_soundMap[resName]->CreateInstance(false);
		if (m_bgmInst) {
			m_bgmInst->SetVolume(m_bgmVol);
			m_bgmInst->Play(loop);
		}
	}
}

void AudioManager::StopBgm()
{
	if (m_bgmInst)
	{
		m_bgmInst->Stop();
		m_bgmInst = nullptr;
	}
}

void AudioManager::PlaySe(const std::string& resName, bool loop)
{
	if (m_soundMap.find(resName) != m_soundMap.end())
	{
		auto instance = m_soundMap[resName]->CreateInstance(false);
		if (instance)
		{
			instance->SetVolume(m_seVol);
			instance->Play(loop);

			m_seList.push_back({ resName, instance, 1.0f });
		}
	}
}

void AudioManager::StopSe(const std::string& name)
{
	for (auto& se : m_seList)
	{
		if (se.name == name && se.instance)
		{
			se.instance->Stop();
		}
	}
}

void AudioManager::PlaySeNumLimit(const std::string& resName, bool loop)
{
	if (m_soundMap.find(resName) == m_soundMap.end()) return;

	if (m_seFrameCount[resName] >= 1) return;
	m_seFrameCount[resName]++;

	// 同じSEだけカウント
	int playingCount = 0;
	for (auto& se : m_seList)
	{
		if (se.name == resName && se.instance->IsPlay())
		{
			playingCount++;
		}
	}

	// 音量減衰
	float mixRate = 1.0f / (1.0f + playingCount * 0.15f);

	// 下限
	const float minRate = 0.4f;
	if (mixRate < minRate)
	{
		mixRate = minRate;
	}

	float finalVolume = m_seVol * mixRate;

	auto instance = m_soundMap[resName]->CreateInstance(false);
	if (instance)
	{
		instance->SetVolume(finalVolume);
		instance->Play(loop);

		m_seList.push_back({ resName, instance, mixRate });
	}
}

void AudioManager::FadeInBgm(const std::string& resName, float fadeTime, bool loop)
{
	m_bgmFade = {};

	StopBgm();

	if (m_soundMap.find(resName) == m_soundMap.end()) return;

	// ★ m_bgmInst に代入する
	m_bgmInst = m_soundMap[resName]->CreateInstance(false);
	if (!m_bgmInst) return;

	m_bgmInst->SetVolume(0.0f);
	m_bgmInst->Play(loop);

	m_bgmFade.active = true;
	m_bgmFade.fadeIn = true;
	m_bgmFade.end = false;

	m_bgmFade.currentVol = 0.0f;
	m_bgmFade.targetVol = m_bgmVol;

	if (fadeTime <= 0.0f)
	{
		m_bgmFade.speed = m_bgmVol;
	}
	else
	{
		m_bgmFade.speed = m_bgmVol / (fadeTime * 60.0f);
	}
}

void AudioManager::FadeOutBgm(float fadeTime)
{
	m_bgmFade = {};

	// フェード状態をON
	m_bgmFade.active = true;
	m_bgmFade.fadeIn = false;
	m_bgmFade.end = false;

	// フェード開始音量
	m_bgmFade.currentVol = GetBgmVolume();

	// フェード終了音量
	m_bgmFade.targetVol = 0.0f;

	// 1フレームあたりの減少量を設定
	if (fadeTime <= 0.0f)
	{
		m_bgmFade.speed = m_bgmFade.currentVol;
	}
	else
	{
		// fadeTime秒で、現在の音量から0へフェードアウトする
		m_bgmFade.speed = m_bgmFade.currentVol / (fadeTime * 60.0f);
	}
}

void AudioManager::FadeOutAndPlayNext(const std::string& nextBgm, float fadeOutTime, float fadeInTime, bool loop)
{
	m_nextBgm = nextBgm;
	m_requestNextBgm = true;
	m_fadeInTime = fadeInTime;
	m_nextBgmLoop = loop;
	FadeOutBgm(fadeOutTime);
}

void AudioManager::PauseBGM() 
{
	if (m_bgmInst && !m_bgmInst->IsPause()) 
	{
		m_bgmInst->Pause();
	}
}

void AudioManager::ResumeBGM() 
{
	if (m_bgmInst && m_bgmInst->IsPause()) 
	{
		m_bgmInst->Resume();
	}
}

void AudioManager::Release()
{
	StopBgm();
	m_seList.clear();
	m_soundMap.clear();
}

void AudioManager::SetBgmVolume(float vol)
{
	if (vol < 0.0f) vol = 0.0f;
	if (vol > 1.0f) vol = 1.0f;

	m_bgmVol = vol;

	// フェード中なら目標値だけ変更
	if (m_bgmFade.active)
	{
		m_bgmFade.targetVol = m_bgmVol;
	}
	else if (m_bgmInst)
	{
		m_bgmInst->SetVolume(m_bgmVol);
	}
}

void AudioManager::SetSeVolume(float vol)
{
	if (vol < 0.0f) vol = 0.0f;
	if (vol > 1.0f) vol = 1.0f;

	m_seVol = vol;

	for (auto& se : m_seList)
	{
		if (se.instance)
		{
			se.instance->SetVolume(m_seVol * se.volumeRate);
		}
	}
}