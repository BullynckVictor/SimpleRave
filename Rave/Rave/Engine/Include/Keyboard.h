#pragma once
#include <bitset>
#include <queue>
#include <optional>

namespace rave
{
	class Keyboard
	{
	public:
		struct Event
		{
			Event(const unsigned char key, const bool pressed)
				:
				key(key),
				pressed(pressed)
			{}
			const unsigned char key;
			const bool pressed;
		};
		bool KeyIsPressed(const unsigned char key);
		const std::optional<Event> GetKeyEvent();
		const std::vector<Event> GetAllEvents();
		const std::optional<wchar_t>  GetChar();
		const std::wstring GetAllChars();

	private:
		std::bitset<256> pressedKeys;
		std::queue<Event> keyEventQueue;
		std::queue<wchar_t> charQueue;
		friend class Window;
	};
}