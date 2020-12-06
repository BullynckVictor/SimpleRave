#include "Engine/Graphics/Include/InfoManager.h"
#include "Engine/Utilities/Include/Exception.h"

#pragma comment(lib, "dxguid.lib")

rave::DXInfoManager::DXInfoManager()
{
	HRESULT hr;
	// define function signature of DXGIGetDebugInterface
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	// load the dll that contains the function DXGIGetDebugInterface
	const auto hModDxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (hModDxgiDebug == nullptr)
		rave_throw_last();

	// get address of DXGIGetDebugInterface in dll
	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
	);
	if (DxgiGetDebugInterface == nullptr)
		rave_throw_last();

	rave_check_hr(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), &pInfoQueue));
}

void rave::DXInfoManager::ClearQueue() noexcept
{
	index = pInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

const std::vector<std::string> rave::DXInfoManager::GetNewMessages()
{
	HRESULT hr;

	std::vector<std::string> ret;
	const unsigned long long qlen = pInfoQueue->GetNumStoredMessagesAllowedByRetrievalFilters(DXGI_DEBUG_ALL);
	for (unsigned long long i = index; i < qlen; i++)
	{
		SIZE_T length = 0;
		rave_check_hr(pInfoQueue->GetMessageW(DXGI_DEBUG_ALL, index, NULL, &length));
		std::unique_ptr<BYTE[]> pBytes = std::make_unique<BYTE[]>(length);
		DXGI_INFO_QUEUE_MESSAGE* pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(pBytes.get());
		rave_check_hr(pInfoQueue->GetMessageW(DXGI_DEBUG_ALL, index, pMessage, &length));
		ret.push_back(pMessage->pDescription);
	}
	return ret;
}
