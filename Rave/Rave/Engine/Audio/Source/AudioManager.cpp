#include "Engine/Audio/Include/AudioManager.h"
#include "Engine/Utilities/Include/Exception.h"

rave::AudioManager::AudioManager()
{
	HRESULT hr;
	rave_check_hr(MFCreateAttributes(&pSourceReaderConfiguration, 1u));
	rave_check_hr(pSourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true));

	rave_check_hr(XAudio2Create(&pEngine, 0, XAUDIO2_DEFAULT_PROCESSOR));
	rave_check_hr(pEngine->CreateMasteringVoice(&pMasteringVoice));
}

rave::AudioManager::~AudioManager()
{
	pMasteringVoice->DestroyVoice();
	pEngine->StopEngine();
}

void rave::AudioManager::LoadFile(const wchar_t* filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveFormatLength)
{
	HRESULT hr;

	rave_check_file(filename);

	// stream index
	DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;

	// create the source reader
	ComPtr<IMFSourceReader> pSourceReader;
	rave_check_hr(MFCreateSourceReaderFromURL(filename, pSourceReaderConfiguration.Get(), &pSourceReader));

	// select the first audio stream, and deselect all other streams
	rave_check_hr(pSourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false));
	rave_check_hr(pSourceReader->SetStreamSelection(streamIndex, true));

	// query information about the media file
	ComPtr<IMFMediaType> pNativeMediaType;
	rave_check_hr(pSourceReader->GetNativeMediaType(streamIndex, 0, &pNativeMediaType));

	// make sure that this is really an audio file
	GUID majorType{};
	rave_check_hr(pNativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType));

	// check whether the audio file is compressed or uncompressed
	GUID subType{};
	rave_check_hr(pNativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType));
	if (subType != MFAudioFormat_Float && subType != MFAudioFormat_PCM)
	{
		// the audio file is compressed; we have to decompress it first
		// to do so, we inform the SourceReader that we want uncompressed data
		// this causes the SourceReader to look for decoders to perform our request
		Microsoft::WRL::ComPtr<IMFMediaType> pPartialType = nullptr;
		rave_check_hr(MFCreateMediaType(pPartialType.GetAddressOf()));

		// set the media type to "audio"
		rave_check_hr(pPartialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio));

		// request uncompressed data
		rave_check_hr(pPartialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM));

		rave_check_hr(pSourceReader->SetCurrentMediaType(streamIndex, NULL, pPartialType.Get()));
	}

	// uncompress the data and load it into an XAudio2 Buffer
	ComPtr<IMFMediaType> pUncompressedAudioType = nullptr;
	rave_check_hr(pSourceReader->GetCurrentMediaType(streamIndex, &pUncompressedAudioType));

	rave_check_hr(MFCreateWaveFormatExFromMFMediaType(pUncompressedAudioType.Get(), waveFormatEx, &waveFormatLength));

	// ensure the stream is selected
	rave_check_hr(pSourceReader->SetStreamSelection(streamIndex, true));

	// copy data into byte vector
	ComPtr<IMFSample> pSample = nullptr;
	ComPtr<IMFMediaBuffer> pBuffer = nullptr;
	BYTE* localAudioData = NULL;
	DWORD localAudioDataLength = 0;

	while (true)
	{
		DWORD flags = 0;
		rave_check_hr(pSourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, &pSample));

		// check whether the data is still valid
		if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
			break;

		// check for eof
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
			break;

		if (pSample == nullptr)
			continue;

		// convert data to contiguous buffer
		rave_check_hr(pSample->ConvertToContiguousBuffer(&pBuffer));

		// lock buffer and copy data to local memory
		rave_check_hr(pBuffer->Lock(&localAudioData, nullptr, &localAudioDataLength));

		const size_t i = audioData.size();
		audioData.resize(i + localAudioDataLength);
		memcpy(&audioData[i], localAudioData, localAudioDataLength);

		// unlock the buffer
		rave_check_hr(pBuffer->Unlock());
		localAudioData = nullptr;
	}
}
