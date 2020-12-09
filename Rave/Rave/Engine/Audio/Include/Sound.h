#pragma once

#include <vector>
#include "Engine/Audio/Include/AudioManager.h"

namespace rave
{
	class Sound
	{
	public:
		Sound(AudioManager& audio, SoundMixer& mixer, const wchar_t* filename);

		Sound(const Sound&) = delete;
		Sound& operator=(const Sound&) = delete;

		void Play();
		void Stop();
		const bool IsPlaying();

		void SetVolume(const float volume);
		const float GetVolume();

		~Sound();

	private:
		bool playing = false;
		IXAudio2SourceVoice* pSourceVoice = nullptr;	// the XAudio2 source voice
		std::vector<BYTE> audioData;					// the audio data
		XAUDIO2_BUFFER audioBuffer;						// the actual buffer with the audio data
	};

	class SoundMixer
	{
	public:
		SoundMixer(AudioManager& audioManager);

		SoundMixer(const SoundMixer&) = delete;
		SoundMixer& operator=(const SoundMixer&) = delete;

		void SetVolume(const float volume);
		const float GetVolume();

		~SoundMixer();

	private:
		IXAudio2SubmixVoice* pSubmixVoice = nullptr;

		XAUDIO2_SEND_DESCRIPTOR sendDesc;
		XAUDIO2_VOICE_SENDS		sendList;

		friend class Sound;
	};
}