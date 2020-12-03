#include "Engine/Include/Keyboard.h"

bool rave::Keyboard::KeyIsPressed(const unsigned char key)
{
    return pressedKeys.test((size_t)key);
}

const std::optional<rave::Keyboard::Event> rave::Keyboard::GetKeyEvent()
{
    if (keyEventQueue.empty())
        return {};
    auto e = keyEventQueue.front();
    keyEventQueue.pop();
    return e;
}

const std::vector<rave::Keyboard::Event> rave::Keyboard::GetAllEvents()
{
    std::vector<rave::Keyboard::Event> vector;
    for (unsigned int i = 0; i < keyEventQueue.size(); i++)
    {
        vector.emplace_back(keyEventQueue.front());
        keyEventQueue.pop();
    }
    return vector;
}

const std::optional<wchar_t> rave::Keyboard::GetChar()
{
    if (charQueue.empty())
        return {};
    auto e = charQueue.front();
    charQueue.pop();
    return e;
}

const std::wstring rave::Keyboard::GetAllChars()
{
    std::wstring string;
    for (unsigned int i = 0; i < charQueue.size(); i++)
    {
        string.push_back(charQueue.front());
        charQueue.pop();
    }
    return string;
}
