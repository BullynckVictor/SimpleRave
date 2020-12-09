#include "Engine/Audio/Include/Sound.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Sound::Sound(AudioManager& audio, SoundMixer& mixer, const wchar_t* filename)
{
	HRESULT hr;

	unsigned int waveLength;
	WAVEFORMATEX* waveFormatEx;
	audio.LoadFile(filename, audioData, &waveFormatEx, waveLength);

	rave_check_hr(audio.pEngine->CreateSourceVoice(&pSourceVoice, waveFormatEx, 0, XAUDIO2_DEFAULT_FREQ_RATIO, nullptr, &mixer.sendList, nullptr));

	ZeroMemory(&audioBuffer, sizeof(XAUDIO2_BUFFER));
	audioBuffer.AudioBytes = (UINT32)audioData.size();
	audioBuffer.pAudioData = (BYTE* const)audioData.data();
	audioBuffer.pContext = nullptr;
}

void rave::Sound::Play()
{
	HRESULT hr;
	if (!IsPlaying())
		rave_check_hr(pSourceVoice->SubmitSourceBuffer(&audioBuffer));
	rave_check_hr(pSourceVoice->Start());
	playing = true;
}

void rave::Sound::Stop()
{
	HRESULT hr;
	rave_check_hr(pSourceVoice->Stop());
	playing = false;
}

const bool rave::Sound::IsPlaying()
{
	return playing;
}

void rave::Sound::SetVolume(const float volume)
{
	pSourceVoice->SetVolume(volume);
}

const float rave::Sound::GetVolume()
{
	float ret;
	pSourceVoice->GetVolume(&ret);
	return ret;
}

rave::Sound::~Sound()
{
	if (pSourceVoice)
		pSourceVoice->DestroyVoice();
}

rave::SoundMixer::SoundMixer(AudioManager& audioManager)
{
	audioManager.pEngine->CreateSubmixVoice(&pSubmixVoice, 1, 44100, 0, 0, 0, 0);
	sendDesc = { 0, pSubmixVoice };
	sendList = { 1, &sendDesc };
}

void rave::SoundMixer::SetVolume(const float volume)
{
	pSubmixVoice->SetVolume(volume);
}

const float rave::SoundMixer::GetVolume()
{
	float ret;
	pSubmixVoice->GetVolume(&ret);
	return ret;
}

rave::SoundMixer::~SoundMixer()
{
	if (pSubmixVoice)
		pSubmixVoice->DestroyVoice();
}
