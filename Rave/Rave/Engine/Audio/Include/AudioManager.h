#pragma once
#include <vector>

#include "Engine/Graphics/Include/DirectX.h"
#include <xaudio2.h>

// Windows Media Foundation
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

namespace rave
{
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		AudioManager(const AudioManager&) = delete;
		AudioManager& operator=(const AudioManager&) = delete;

	private:
		void LoadFile(const wchar_t* filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveLength);

		ComPtr<IXAudio2> pEngine;
		IXAudio2MasteringVoice* pMasteringVoice = nullptr;

		ComPtr<IMFAttributes> pSourceReaderConfiguration;

		friend class Sound;
		friend class SoundMixer;
	};
}