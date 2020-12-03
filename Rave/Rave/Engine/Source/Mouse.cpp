#include "Engine/Include/Mouse.h"
#include "Engine/Utilities/Include/Exception.h"

rave::Mouse::Mouse(const bool useEvents, const bool useRawDeltas)
    :
    useEvents(useEvents),
    useRawDeltas(useRawDeltas)
{
}

const bool rave::Mouse::LeftIsPressed() const noexcept
{
    return left;
}

const bool rave::Mouse::MiddleIsPressed() const noexcept
{
    return middle;
}

const bool rave::Mouse::RightIsPressed() const noexcept
{
    return right;
}

const int rave::Mouse::GetPosX() const noexcept
{
    return x;
}

const int rave::Mouse::GetPosY() const noexcept
{
    return y;
}

const int rave::Mouse::GetScrollDelta() noexcept
{
    int temp = delta / 120;
    delta -= temp * 120;
    return temp;
}

const bool rave::Mouse::InWindow() const noexcept
{
    return inWindow;
}

const rave::Mouse::Event rave::Mouse::GetEvent() noexcept
{
    if (!events.empty())
    {
        Event e = events.front();
        events.pop();
        return e;
    }
    return {};
}

const std::optional<rave::Mouse::RawDelta> rave::Mouse::GetRawDelta() noexcept
{
    if (!rawDeltas.empty())
    {
        RawDelta e = rawDeltas.front();
        rawDeltas.pop();
        return e;
    }
    return {};
}

void rave::Mouse::ClearEventQueue() noexcept
{
    while (!events.empty())
        events.pop();
}

void rave::Mouse::ClearDeltaQueue() noexcept
{
    while (!rawDeltas.empty())
        rawDeltas.pop();
}

void rave::Mouse::AddEvent(const Event::Type type, const POINTS p, const WPARAM wParam)
{
    rave_assert_info(useEvents, L"Mouse Events are disabled, change this value in the rave::Mouse constructor");

    Mouse::Event e;
    e.type = type;
    e.x = p.x;
    e.y = p.y;
    e.leftPressed = wParam & MK_LBUTTON;
    e.middlePressed = wParam & MK_MBUTTON;
    e.rightPressed = wParam & MK_RBUTTON;
    e.ctrlPressed = wParam & MK_CONTROL;
    e.shiftPressed = wParam & MK_SHIFT;

    events.push(e);
}

rave::Mouse::Event::Event()
    :
    type(Type::None)
{
}
