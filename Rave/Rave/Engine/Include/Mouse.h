#pragma once
#include <queue>
#include <optional>
#include "Engine/Include/Windows.h"

namespace rave
{
	class Mouse
	{
		Mouse(const bool useEvents, const bool useRawDeltas);

		struct RawDelta
		{
			int x;
			int y;
		};
		struct Event
		{
			enum class Type
			{
				None,
				LeftPressed,
				LeftReleased,
				MiddlePressed,
				MiddleReleased,
				RightPressed,
				RightReleased,
				WheelUp,
				WheelDown,
				Move
			};

			Event();

			operator bool() const { return type != Type::None; }

			Type type;
			int x = 0;
			int y = 0;
			bool leftPressed = false;
			bool rightPressed = false;
			bool middlePressed = false;
			bool ctrlPressed = false;
			bool shiftPressed = false;
		};

		const bool LeftIsPressed() const noexcept;
		const bool MiddleIsPressed() const noexcept;
		const bool RightIsPressed() const noexcept;
		const int  GetPosX() const noexcept;
		const int  GetPosY() const noexcept;
		const int  GetScrollDelta() noexcept;
		const bool InWindow() const noexcept;

		const Event GetEvent() noexcept;
		const std::optional<RawDelta> GetRawDelta() noexcept;
		void ClearEventQueue() noexcept;
		void ClearDeltaQueue() noexcept;

	public:
		const bool useEvents;
		const bool useRawDeltas;

	private:
		void AddEvent(const Event::Type type, const POINTS p, const WPARAM wParam);

		bool left = false;
		bool middle = false;
		bool right = false;
		int delta = 0;
		int x = 0;
		int y = 0;
		bool inWindow = false;

		std::queue<Event> events;
		std::queue<RawDelta> rawDeltas;

		friend class Window;
	};
}