#include "Engine/Include/ComManager.h"
#include "Engine/Utilities/Include/Exception.h"
#include "Engine/Audio/Include/AudioManager.h"
#include "Engine/Graphics/Include/DirectX.h"

rave::ComManager::ComManager()
{
	HRESULT hr;
	rave_check_hr(CoInitializeEx(NULL, 0u));
	rave_check_hr(MFStartup(MF_VERSION));
}

rave::ComManager::~ComManager()
{
	MFShutdown();
	CoUninitialize();
}