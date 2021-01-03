#include "Engine/GUI/Include/EmptyCameraLock.h"

rave::EmptyCameraLock::EmptyCameraLock()
	:
	empty(),
	pPrev(Transform2::pCamera)
{
	Transform2::pCamera = &empty;
}

rave::EmptyCameraLock::~EmptyCameraLock()
{
	Transform2::pCamera = pPrev;
}
