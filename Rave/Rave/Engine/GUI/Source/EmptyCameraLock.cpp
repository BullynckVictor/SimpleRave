#include "Engine/GUI/Include/EmptyCameraLock.h"

rave::EmptyCameraLock::EmptyCameraLock()
	:
	empty(),
	pPrev(Transform::pCamera)
{
	Transform::pCamera = &empty;
}

rave::EmptyCameraLock::~EmptyCameraLock()
{
	Transform::pCamera = pPrev;
}
