#include "Engine/Include/Window.h"
#include "Engine/Include/Transform.h"
#include "resource.h"

rave::Window::Window(Graphics& gfx, const wchar_t* windowName, const int width, const int height, const bool useMouseEvents, const bool useMouseRawDeltas, const wchar_t* className)
	:
    mouse(useMouseEvents, useMouseRawDeltas),
    hInstance(GetModuleHandle(nullptr)),
	hwnd(CreateHWND(hInstance, windowName, width, height, className, this)),
	name(windowName),
    className(className),
	width(width),
	height(height),
	gfx(gfx)
{
    swap.Load(gfx, hwnd, width, height);
    target.Load(gfx, swap);
    blender.Load(gfx, true);

    size = target.GetTargetSize();

    ShowWindow(hwnd, SW_SHOWDEFAULT);

    //register raw input device
    RAWINPUTDEVICE rid[1];
    rid[0].usUsagePage = 0x01;
    rid[0].usUsage = 0x02;
    rid[0].dwFlags = 0;
    rid[0].hwndTarget = nullptr;

    if (!RegisterRawInputDevices(rid, 1u, sizeof(RAWINPUTDEVICE)))
        rave_throw_last();

    Bind();
    blender.Bind(gfx);
}

HWND rave::Window::CreateHWND(const HINSTANCE hInst, const wchar_t* windowName, const int width, const int height, const wchar_t* className, const Window* _this)
{
    HWND hwnd;

    WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = StaticWindowProcSetup;
    wc.hInstance = hInst;
    wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), 0));
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0));
    wc.hCursor = NULL;
    wc.lpszClassName = className;

    RegisterClassEx(&wc);

    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
    if (AdjustWindowRect(&wr, style, FALSE) == 0)
        rave_throw_last();

    hwnd = CreateWindow(
        className, windowName, style,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, hInst, (void*)_this
    );

    if (hwnd == nullptr)
        rave_throw_last();

    return hwnd;
}


rave::Window::~Window()
{
    if(!open)
        DestroyWindow(hwnd);
    UnregisterClassW(className.c_str(), hInstance);
}

void rave::Window::Clear() noexcept
{
    target.Clear(gfx, background);
}

void rave::Window::Present()
{
    target.EndDraw();
    swap.Present();
}

void rave::Window::Bind()
{
    target.Bind(gfx);
}

void rave::Window::SetAlphaBlending(const bool blendAlpha)
{
    blender.SetAlpha(gfx, blendAlpha);
    blender.Bind(gfx);
}

bool rave::Window::HandleMessages() noexcept
{
    MSG msg = { };
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (!open)
            return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

const wchar_t* rave::Window::GetTitle() const noexcept
{
    return name.c_str();
}

void rave::Window::SetTitle(const wchar_t* name_) noexcept
{
    name = name_;
    SetWindowText(hwnd, name_);
}

int rave::Window::GetWidth() const noexcept
{
    return width;
}

int rave::Window::GetHeight() const noexcept
{
    return height;
}

void rave::Window::SetVSync(const bool vsync) noexcept
{
    swap.SetVSync(vsync);
}

bool rave::Window::GetVSync() const noexcept
{
    return swap.GetVSync();
}

void rave::Window::EnableCursor() noexcept
{
    cursorEnabled = true;
    ShowCursor();
    FreeCursor();
}

void rave::Window::DisableCursor() noexcept
{
    cursorEnabled = false;
    HideCursor();
    ConfineCursor();
}

void rave::Window::ConfineCursor() noexcept
{
    RECT rect;
    GetClientRect(hwnd, &rect);
    MapWindowPoints(hwnd, nullptr, reinterpret_cast<POINT*>(&rect), 2);
    ClipCursor(&rect);
}

void rave::Window::FreeCursor() noexcept
{
    ClipCursor(nullptr);
}

void rave::Window::ShowCursor() noexcept
{
    while (::ShowCursor(TRUE) < 0);
}

void rave::Window::HideCursor() noexcept
{
    while (::ShowCursor(FALSE) >= 0);
}

void rave::Window::Close() const noexcept
{
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

bool rave::Window::IsOpen() const noexcept
{
    return open;
}

rave::RenderTarget& rave::Window::GetRenderTarget() noexcept
{
    return target;
}

const rave::TargetSize rave::Window::GetSize() const noexcept
{
    return size;
}

rave::Vector2 rave::Window::MousePos() const noexcept
{
    TargetSize ts = GetSize();
    Vector2 pos = { (float)mouse.GetPosX(), (float)mouse.GetPosY() };
    pos /= { (float)ts.pixel.view.x, (float)ts.pixel.view.y };
    pos.view.x = pos.view.x * 2 - 1;
    pos.view.y = -pos.view.y * 2 + 1;
    pos *= ts.relative;

    return pos;
}

bool rave::Window::CursorEnabled() const noexcept
{
    return cursorEnabled;
}

LRESULT CALLBACK rave::Window::WindowProc(HWND, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        open = false;
        return 0;
    }
    break;
    //keyboard
    case WM_KEYDOWN:
    {
        unsigned char key = (unsigned char)wParam;
        kbd.pressedKeys[(size_t)key] = true;
        kbd.keyEventQueue.push(Keyboard::Event{ key, true });
    }
    break;
    case WM_KEYUP:
    {
        unsigned char key = (unsigned char)wParam;
        kbd.pressedKeys[(size_t)key] = false;
        kbd.keyEventQueue.push(Keyboard::Event{ key, false });
    }
    break;
    case WM_CHAR:
    {
        kbd.charQueue.push((wchar_t)wParam);
    }
    break;

    //mouse messages
    case WM_MOUSEMOVE:
    {
        POINTS point = MAKEPOINTS(lParam);
        mouse.x = (int)point.x;
        mouse.y = (int)point.y;
        mouse.inWindow = true;
        if(mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::Move, point, wParam);
    }
    break;

    case WM_LBUTTONDOWN:
    {
        mouse.left = true;
        if (!captured)
        {
            captured = true;
            SetCapture(hwnd);
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::LeftPressed, MAKEPOINTS(lParam), wParam);
    }
    break;
    case WM_LBUTTONUP:
    {
        mouse.left = false;
        if (captured)
        {
            captured = false;
            ReleaseCapture();
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::LeftReleased, MAKEPOINTS(lParam), wParam);
    }
    break;

    case WM_MBUTTONDOWN:
    {
        mouse.middle = true;
        if (!captured)
        {
            captured = true;
            SetCapture(hwnd);
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::MiddlePressed, MAKEPOINTS(lParam), wParam);
    }
    break;
    case WM_MBUTTONUP:
    {
        mouse.middle = false;
        if (captured)
        {
            captured = false;
            ReleaseCapture();
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::MiddleReleased, MAKEPOINTS(lParam), wParam);
    }
    break;

    case WM_RBUTTONDOWN:
    {
        mouse.right = true;
        if (!captured)
        {
            captured = true;
            SetCapture(hwnd);
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::RightPressed, MAKEPOINTS(lParam), wParam);
    }
    break;
    case WM_RBUTTONUP:
    {
        mouse.right = false;
        if (captured)
        {
            captured = false;
            ReleaseCapture();
        }
        if (mouse.useEvents)
            mouse.AddEvent(Mouse::Event::Type::RightReleased, MAKEPOINTS(lParam), wParam);
    }
    break;

    case WM_MOUSEHWHEEL:
    {
        int delta = GET_WHEEL_DELTA_WPARAM(wParam);
        mouse.delta += delta;

        if (mouse.useEvents)
            if (delta > 0)
                mouse.AddEvent(Mouse::Event::Type::WheelUp, MAKEPOINTS(lParam), wParam);
            else if (delta < 0)
                mouse.AddEvent(Mouse::Event::Type::WheelDown, MAKEPOINTS(lParam), wParam);
    }
    break;

    //raw input
    case WM_INPUT:
    {
        std::vector<char> riData;
        UINT size = 0;
        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &size, sizeof RAWINPUTHEADER) == -1)
            break;
        riData.resize(size);
        if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, riData.data(), &size, sizeof RAWINPUTHEADER) != size)
            break;
        auto* pRi = (RAWINPUT*)riData.data();
        if (pRi->header.dwType == RIM_TYPEMOUSE)
        {
            if (mouse.useRawDeltas && (pRi->data.mouse.lLastX != 0 || pRi->data.mouse.lLastY != 0))
                mouse.rawDeltas.push({ pRi->data.mouse.lLastX, pRi->data.mouse.lLastY });
            if (pRi->data.mouse.usButtonFlags == RI_MOUSE_WHEEL)
            {
                SHORT delta = (SHORT)pRi->data.mouse.usButtonData;
                mouse.delta += (int)delta;
                if (delta > 0)
                    mouse.AddEvent(Mouse::Event::Type::WheelUp, POINTS{ std::numeric_limits<SHORT>::min(),std::numeric_limits<SHORT>::min() }, 0);
                else if (delta < 0)
                    mouse.AddEvent(Mouse::Event::Type::WheelDown, POINTS{ std::numeric_limits<SHORT>::min(),std::numeric_limits<SHORT>::min() }, 0);
            }
        }
    }
    break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT rave::Window::StaticWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    return pWnd->WindowProc(hwnd, msg, wParam, lParam);
}

LRESULT rave::Window::StaticWindowProcSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_CREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&rave::Window::StaticWindowProc));
        return pWnd->WindowProc(hwnd, msg, wParam, lParam);
    }
    else
    {
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}